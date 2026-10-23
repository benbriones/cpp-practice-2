#!/usr/bin/env python3
"""Goal: compile each exercise against its tests, run every test in its own process, report results."""
# Usage: grade <exercise|module> · grade --all · grade --run <exercise> [args...]

from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import os
import re
import shutil
import signal
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional, Tuple

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "src"
TESTS = ROOT / "tests"
GRADER = ROOT / "grader"

CXX = os.environ.get("CXX", "c++")
CXXFLAGS = [
    "-std=c++20",
    "-g",
    "-O0",
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Wshadow",
    "-Wno-unused-parameter",  # TODO stubs don't use their parameters yet
    "-fsanitize=address,undefined",
    "-fno-sanitize-recover=undefined",
    "-fno-omit-frame-pointer",
    "-fdiagnostics-absolute-paths",
]
TEST_TIMEOUT = float(os.environ.get("GRADE_TIMEOUT", "5"))  # seconds per test; sanitizers slow code down
COMPILE_TIMEOUT = 120
TODO_EXIT = 77  # runner.cpp exits with this when a program hits throw "TODO"
RUN_ENV = {
    **os.environ,
    "MallocNanoZone": "0",  # silences a harmless macOS malloc warning under ASan
    "ASAN_OPTIONS": "detect_leaks=0:detect_stack_use_after_return=1",
    "UBSAN_OPTIONS": "print_stacktrace=1",
}
for _var in ("GRADER_OUT", "GRADER_MODE", "GRADER_INDEX"):
    RUN_ENV.pop(_var, None)

USE_COLOR = sys.stdout.isatty() and "NO_COLOR" not in os.environ
ANSI = re.compile(r"\x1b\[[0-9;]*m")
NUMBERED = re.compile(r"^\d+[a-z]?_")  # a letter suffix (03b_) slots an extra module in after 03_
DIAGNOSTIC = re.compile(
    r"^(?P<file>[^\s:][^:]*):(?P<line>\d+):(?P<col>\d+): "
    r"(?P<kind>fatal error|error|warning|note): (?P<message>.*)$"
)
SUMMARY_LINE = re.compile(r"^\d+ (errors?|warnings?)( and \d+ \w+)? generated\.$")
FRAME = re.compile(r"#(?P<num>\d+) 0x[0-9a-f]+ in (?P<func>.+?) (?P<file>\S+?):(?P<line>\d+)")
UBSAN = re.compile(r"(?P<file>\S+?):(?P<line>\d+):(?P<col>\d+): runtime error: (?P<message>.*)")

ASAN_HINTS = {
    "heap-use-after-free": "used memory after it was freed (a dangling pointer or reference)",
    "heap-buffer-overflow": "read or wrote past the end of a heap array or vector",
    "stack-buffer-overflow": "read or wrote past the end of a local array",
    "global-buffer-overflow": "read or wrote past the end of a global array",
    "stack-use-after-return": "used a pointer or reference to a local variable after its function returned",
    "stack-use-after-scope": "used a pointer or reference to a variable that went out of scope",
    "stack-overflow": "stack overflow (infinite recursion?)",
    "double-free": "deleted the same memory twice",
    "new-delete-type-mismatch": "deleted an object through a pointer to the wrong type (missing virtual destructor?)",
    "alloc-dealloc-mismatch": "mismatched new/delete (new[] needs delete[], new needs delete)",
    "container-overflow": "accessed a container element beyond its size()",
    "bad-free": "deleted a pointer that was never allocated with new",
    "SEGV": "invalid memory access",
}
SIGNAL_HINTS = {
    "SIGSEGV": "segmentation fault: invalid memory access",
    "SIGBUS": "bus error: invalid memory access",
    "SIGFPE": "arithmetic error, e.g. integer division by zero",
    "SIGILL": "illegal instruction",
    "SIGTRAP": "trap",
    "SIGABRT": "aborted",
    "SIGKILL": "killed",
}


class UsageError(Exception):
    pass


def paint(text: str, code: str) -> str:
    return f"\033[{code}m{text}\033[0m" if USE_COLOR else text


def green(text: str) -> str:
    return paint(text, "32")


def red(text: str) -> str:
    return paint(text, "31")


def yellow(text: str) -> str:
    return paint(text, "33")


def dim(text: str) -> str:
    return paint(text, "2")


def bold(text: str) -> str:
    return paint(text, "1")


def indent(text: str, spaces: int) -> str:
    pad = " " * spaces
    return "\n".join(pad + line if line.strip() else "" for line in text.splitlines())


def truncate_lines(text: str, limit: int) -> str:
    lines = text.rstrip("\n").splitlines()
    if len(lines) <= limit:
        return "\n".join(lines)
    return "\n".join(lines[:limit] + [f"... ({len(lines) - limit} more lines)"])


def decode(data: Optional[bytes]) -> str:
    return (data or b"").decode("utf-8", errors="replace")


def relative(text: str) -> str:
    return text.replace(f"{ROOT}/", "")


def unescape(text: str) -> str:
    table = {"n": "\n", "t": "\t", "r": "\r", "0": "\0", '"': '"', "\\": "\\"}
    out, i = [], 0
    while i < len(text):
        if text[i] == "\\" and i + 1 < len(text):
            out.append(table.get(text[i + 1], text[i + 1]))
            i += 2
        else:
            out.append(text[i])
            i += 1
    return "".join(out)


# ---- Exercises ----


@dataclass
class Exercise:
    module: str
    name: str

    @property
    def id(self) -> str:
        return f"{self.module}/{self.name}"

    def source(self, src_root: Path) -> Path:
        folder = src_root / self.module / self.name
        return folder if folder.is_dir() else src_root / self.module / f"{self.name}.cpp"

    @property
    def test_file(self) -> Path:
        return TESTS / self.module / f"{self.name}.cpp"


def discover() -> List[Exercise]:
    exercises = []
    for module in sorted(p for p in SRC.iterdir() if p.is_dir() and NUMBERED.match(p.name)):
        for entry in sorted(module.iterdir()):
            if not NUMBERED.match(entry.name):
                continue
            if entry.is_dir():
                exercises.append(Exercise(module.name, entry.name))
            elif entry.suffix == ".cpp":
                exercises.append(Exercise(module.name, entry.stem))
    return exercises


def matches(part: str, name: str) -> bool:
    number, _, label = name.partition("_")
    if part == name or part == label:
        return True
    # Leading zeros are optional: 3 and 03 name module 03, and 3b and 03b name module 03b.
    return bool(re.fullmatch(r"\d+[a-z]?", part)) and part.lstrip("0") == number.lstrip("0")


def pick(part: str, names: List[str], what: str) -> str:
    found = [n for n in names if matches(part, n)]
    if len(found) == 1:
        return found[0]
    if not found:
        raise UsageError(f"No {what} matches '{part}'. Options:\n" + indent("\n".join(names), 2))
    raise UsageError(f"'{part}' is ambiguous: " + ", ".join(found))


def resolve(target: str, exercises: List[Exercise]) -> List[Exercise]:
    path = Path(target)
    if path.exists():
        resolved = path.resolve()
        for base in (SRC, TESTS):
            try:
                target = resolved.relative_to(base).as_posix()
                break
            except ValueError:
                continue
        else:
            raise UsageError(f"{target} is not inside {relative(str(SRC))}/")
    for prefix in ("./", "src/", "tests/"):
        if target.startswith(prefix):
            target = target[len(prefix) :]
    if target.endswith(".cpp"):
        target = target[: -len(".cpp")]
    parts = [p for p in target.split("/") if p]
    if not parts:
        raise UsageError("Name an exercise, e.g. grade 01_basics/01_arithmetic")
    module = pick(parts[0], sorted({e.module for e in exercises}), "module")
    in_module = [e for e in exercises if e.module == module]
    if len(parts) == 1:
        return in_module
    name = pick(parts[1], [e.name for e in in_module], f"exercise in {module}")
    return [e for e in in_module if e.name == name]


# ---- Building ----


@dataclass
class Diagnostic:
    kind: str
    file: str
    line: str
    message: str
    lines: List[str] = field(default_factory=list)


def parse_diagnostics(output: str) -> List[Diagnostic]:
    diagnostics: List[Diagnostic] = []
    for raw in output.splitlines():
        plain = ANSI.sub("", raw)
        if plain.startswith("In file included from") or SUMMARY_LINE.match(plain):
            continue
        match = DIAGNOSTIC.match(plain)
        if match and match["kind"] != "note":
            diagnostics.append(
                Diagnostic(match["kind"], match["file"], match["line"], match["message"], [raw])
            )
        elif diagnostics:
            diagnostics[-1].lines.append(raw)
    return diagnostics


def is_inside(file: str, folder: Path) -> bool:
    try:
        Path(file).resolve().relative_to(folder.resolve())
        return True
    except ValueError:
        return False


def compile_command(sources: List[Path], src_root: Path, runner: Path, binary: Path) -> List[str]:
    color = "-fcolor-diagnostics" if USE_COLOR else "-fno-color-diagnostics"
    return [
        CXX,
        *CXXFLAGS,
        color,
        f"-I{src_root}",
        f"-I{GRADER}",
        *(str(s) for s in sources),
        str(runner),  # last, so its static initializer runs after the tests register
        "-o",
        str(binary),
    ]


def compile_runner(workdir: Path) -> Path:
    """runner.o, cached in the OS temp dir (not the project) since it rarely changes."""
    key = hashlib.sha256()
    for part in (GRADER / "runner.cpp", GRADER / "grader.hpp"):
        key.update(part.read_bytes())
    version = subprocess.run([CXX, "--version"], capture_output=True, text=True).stdout
    key.update((" ".join([CXX, *CXXFLAGS]) + version).encode())
    cached = Path(tempfile.gettempdir()) / f"cpp-practice-runner-{key.hexdigest()[:16]}.o"
    if cached.exists():
        return cached
    runner = workdir / "runner.o"
    cmd = [CXX, *CXXFLAGS, "-c", str(GRADER / "runner.cpp"), "-o", str(runner)]
    proc = subprocess.run(cmd, capture_output=True, text=True, timeout=COMPILE_TIMEOUT)
    if proc.returncode != 0:
        raise UsageError("Couldn't compile grader/runner.cpp:\n" + proc.stderr)
    try:
        os.replace(runner, cached)
        return cached
    except OSError:
        return runner


def student_sources(source: Path) -> List[Path]:
    """Extra translation units: the .cpp files of a multi-file exercise folder."""
    return sorted(source.glob("*.cpp")) if source.is_dir() else []


def student_files(source: Path) -> List[Path]:
    return sorted(source.glob("*.[ch]pp")) if source.is_dir() else [source]


# ---- Running ----


@dataclass
class TestResult:
    name: str
    status: str  # pass | fail | todo
    message: str = ""
    output: str = ""


@dataclass
class ProgramCase:
    name: str
    input: str
    output: str
    args: List[str]
    exit_code: int


def describe_exit(code: int) -> str:
    if code < 0:
        try:
            name = signal.Signals(-code).name
        except ValueError:
            name = f"signal {-code}"
        hint = SIGNAL_HINTS.get(name)
        return f"Crashed with {name}" + (f" ({hint})" if hint else "")
    return f"Exited with code {code} in the middle of the test (does your code call exit()?)"


def short_name(func: str) -> str:
    """'Buffer::push(std::__1::vector<int> const&)' -> 'Buffer::push'."""
    return func.replace("std::__1::", "std::").split("(")[0]


def find_frame(plain: str, mine: List[Path], test_file: Optional[Path]) -> Optional[str]:
    """Where the crash happened in the exercise's files (or the test), plus its caller."""
    by_name = {p.name: p for p in mine}
    found: List[str] = []
    started = False
    for frame in FRAME.finditer(plain):
        if frame["num"] == "0":
            if started:
                break  # only the first stack trace; later ones say where memory was freed etc.
            started = True
        name, line, func = Path(frame["file"]).name, frame["line"], frame["func"]
        # Frames only carry a basename, and a test file shares its exercise's name.
        if "grader_test_" in func or func.startswith("grader::"):
            if not found and test_file is not None and name == test_file.name:
                return f"{relative(str(test_file))}:{line}, in the test (using a value your code returned?)"
            break
        if name in by_name:
            found.append(f"{relative(str(by_name[name]))}:{line}, in {short_name(func)}")
            if len(found) == 2:
                break
    if not found:
        return None
    return found[0] + (f"\n   called from {found[1]}" if len(found) > 1 else "")


def diagnose(returncode: int, stderr: str, mine: List[Path], test_file: Optional[Path] = None) -> str:
    plain = ANSI.sub("", stderr)
    asan = re.search(r"ERROR: AddressSanitizer: (.+)", plain)
    if asan:
        detail = asan.group(1)
        kind = next((k for k in ASAN_HINTS if k in detail), detail.split(" on ")[0])
        hint = ASAN_HINTS.get(kind, kind)
        if kind == "SEGV" and "zero page" in plain:
            hint = "dereferenced a null pointer"
        where = find_frame(plain, mine, test_file)
        return f"Memory error: {hint} [{kind}]" + (f"\nAt {where}" if where else "")
    ubsan = UBSAN.search(plain)
    if ubsan:
        where = None
        if Path(ubsan["file"]).name not in {p.name for p in mine}:
            # The bad operation happened inside the standard library; point at the caller instead.
            where = find_frame(plain, mine, test_file)
        location = where or f"{relative(ubsan['file'])}:{ubsan['line']}"
        return f"Undefined behavior: {ubsan['message']}\nAt {location}"
    for pattern in (
        r"(Unhandled exception.*)",
        r"terminating due to (uncaught exception.*)",
        r"(Assertion failed:.*)",
    ):
        found = re.search(pattern, plain)
        if found:
            return relative(found.group(1)[0].upper() + found.group(1)[1:])
    return describe_exit(returncode)


def list_tests(binary: Path, workdir: Path, mine: List[Path], test_file: Path) -> Tuple[Optional[list], str]:
    out = workdir / f"{binary.name}.list"
    env = {**RUN_ENV, "GRADER_MODE": "list", "GRADER_OUT": str(out)}
    try:
        proc = subprocess.run(
            [str(binary)], cwd=workdir, env=env, stdin=subprocess.DEVNULL, capture_output=True,
            timeout=TEST_TIMEOUT,
        )
    except subprocess.TimeoutExpired:
        return None, "Timed out while starting up (an infinite loop in a global variable's initializer?)"
    if not out.exists():
        return None, "Crashed before any test ran: " + diagnose(proc.returncode, decode(proc.stderr), mine, test_file)
    entries: list = []
    for line in out.read_text(errors="replace").splitlines():
        fields = line.split("\t")
        if fields[0] == "U":
            entries.append(unescape(fields[1]))
        elif fields[0] == "P":
            args = [unescape(a) for a in fields[4].split("\x1f")] if fields[4] else []
            entries.append(
                ProgramCase(unescape(fields[1]), unescape(fields[2]), unescape(fields[3]), args, int(fields[5]))
            )
    return entries, ""


def run_unit(binary: Path, index: int, name: str, workdir: Path, mine: List[Path], test_file: Path) -> TestResult:
    out = workdir / f"{binary.name}.{index}.result"
    env = {**RUN_ENV, "GRADER_MODE": "test", "GRADER_INDEX": str(index), "GRADER_OUT": str(out)}
    with tempfile.TemporaryDirectory(dir=workdir) as cwd:
        try:
            proc = subprocess.run(
                [str(binary)], cwd=cwd, env=env, stdin=subprocess.DEVNULL, capture_output=True,
                timeout=TEST_TIMEOUT,
            )
        except subprocess.TimeoutExpired as timeout:
            return TestResult(
                name, "fail", f"Timed out after {TEST_TIMEOUT:g}s: an infinite loop, or an approach too slow for this input?",
                decode(timeout.stdout),
            )
    printed = decode(proc.stdout)
    if out.exists():
        status, _, message = out.read_text(errors="replace").partition("\n")
        kind = {"PASS": "pass", "TODO": "todo"}.get(status, "fail")
        return TestResult(name, kind, message.rstrip("\n"), printed)
    return TestResult(name, "fail", diagnose(proc.returncode, decode(proc.stderr), mine, test_file), printed)


def normalize(text: str) -> List[str]:
    lines = [line.rstrip() for line in text.splitlines()]
    while lines and not lines[-1]:
        lines.pop()
    return lines


def show_block(lines: List[str]) -> str:
    if not lines:
        return "    (nothing)"
    return "\n".join("    " + (line if line else "") for line in lines[:15]) + (
        f"\n    ... ({len(lines) - 15} more lines)" if len(lines) > 15 else ""
    )


def output_mismatch(case: ProgramCase, expected: List[str], actual: List[str]) -> str:
    parts = []
    if case.args:
        parts.append("Arguments: " + " ".join(case.args))
    input_lines = case.input.splitlines()
    if len(input_lines) <= 8:
        parts.append("Input:\n" + show_block(input_lines))
    else:
        parts.append(f"Input: ({len(input_lines)} lines, see the test file)")
    parts.append("Expected output:\n" + show_block(expected))
    parts.append("Your output:\n" + show_block(actual))
    for number, (want, got) in enumerate(zip(expected + [""], actual + [""]), start=1):
        if want != got:
            parts.append(f"First difference on line {number}:\n    expected {want!r}\n    received {got!r}")
            break
    return "\n".join(parts)


def run_program(binary: Path, case: ProgramCase, workdir: Path, mine: List[Path], test_file: Path) -> TestResult:
    with tempfile.TemporaryDirectory(dir=workdir) as cwd:
        try:
            proc = subprocess.run(
                [str(binary), *case.args], cwd=cwd, env=RUN_ENV, input=case.input.encode(),
                capture_output=True, timeout=TEST_TIMEOUT,
            )
        except subprocess.TimeoutExpired as timeout:
            return TestResult(
                case.name, "fail",
                f"Timed out after {TEST_TIMEOUT:g}s. An infinite loop, or a loop that never sees end of input?",
                decode(timeout.stdout),
            )
    stdout, stderr = decode(proc.stdout), decode(proc.stderr)
    if proc.returncode == TODO_EXIT and 'reached a `throw "TODO"`' in stderr:
        return TestResult(case.name, "todo")
    crashed = proc.returncode < 0 or re.search(r"Sanitizer|runtime error|Unhandled exception", stderr)
    if crashed:
        return TestResult(case.name, "fail", diagnose(proc.returncode, stderr, mine, test_file), stdout)
    expected, actual = normalize(case.output), normalize(stdout)
    if expected != actual:
        return TestResult(case.name, "fail", output_mismatch(case, expected, actual))
    if proc.returncode != case.exit_code:
        return TestResult(
            case.name, "fail",
            f"Output matched, but main() returned {proc.returncode} (expected {case.exit_code})",
        )
    return TestResult(case.name, "pass")


# ---- Grading ----


@dataclass
class Report:
    exercise: Exercise
    state: str  # complete | started | not_started | compile_error | no_tests | missing
    tests: List[TestResult] = field(default_factory=list)
    detail: str = ""
    warnings: List[str] = field(default_factory=list)
    compiler_output: str = ""

    @property
    def passed(self) -> int:
        return sum(t.status == "pass" for t in self.tests)

    @property
    def total(self) -> int:
        return len(self.tests)


def compile_error_detail(diagnostics: List[Diagnostic], raw: str, src_root: Path) -> str:
    errors = [d for d in diagnostics if d.kind in ("error", "fatal error")]
    if not errors:
        text = relative(truncate_lines(raw, 25))
        if "duplicate symbol" in raw:
            text += "\n\n" + yellow(
                "Linker error: something is defined in more than one .cpp file. A function defined\n"
                "in a header gets compiled into every file that includes it: mark it `inline`, or\n"
                "keep only the declaration in the header and move the body into one .cpp. A helper\n"
                "meant for one .cpp only should be internal: an anonymous namespace or `static`."
            )
        elif "Undefined symbols" in raw:
            text += "\n\n" + yellow(
                "Linker error: something is declared but never defined: a missing function body,\n"
                "a static member never defined, or a template whose body lives in a .cpp file."
            )
        return text
    # Errors in your own file come first; test-file errors are usually just the fallout.
    yours = [e for e in errors if is_inside(e.file, src_root)]
    shown = (yours or errors)[:2]
    # Overload-resolution errors can carry dozens of notes; the first lines say what matters.
    text = "\n".join(truncate_lines("\n".join(e.lines), 14) for e in shown)
    if len(errors) > len(shown):
        text += f"\n... and {len(errors) - len(shown)} more errors (grade -v shows everything)"
    text = relative(text)
    if not yours:
        text += "\n\n" + yellow(
            "The first error is in the test file, which usually means a name or signature in your\n"
            "code doesn't match the instructions (return type, parameter types, const, spelling)."
        )
    return text


def grade(exercise: Exercise, src_root: Path, workdir: Path, runner: Path, parallel: bool) -> Report:
    source = exercise.source(src_root)
    if not source.exists():
        return Report(exercise, "missing", detail=f"Can't find {relative(str(source))}")
    if not exercise.test_file.exists():
        return Report(exercise, "no_tests", detail=f"No tests yet ({relative(str(exercise.test_file))})")

    binary = workdir / exercise.id.replace("/", "__")
    sources = [exercise.test_file, *student_sources(source)]
    cmd = compile_command(sources, src_root, runner, binary)
    proc = subprocess.run(cmd, capture_output=True, text=True, timeout=COMPILE_TIMEOUT)
    diagnostics = parse_diagnostics(proc.stderr)
    if proc.returncode != 0:
        return Report(
            exercise, "compile_error", detail=compile_error_detail(diagnostics, proc.stderr, src_root),
            compiler_output=relative(proc.stderr),
        )
    warnings = []
    for d in diagnostics:
        line = f"{relative(d.file)}:{d.line}: {d.message}"
        if d.kind == "warning" and is_inside(d.file, src_root) and line not in warnings:
            warnings.append(line)

    mine = student_files(source)
    entries, problem = list_tests(binary, workdir, mine, exercise.test_file)
    if entries is None:
        return Report(exercise, "started", [TestResult("Program startup", "fail", problem)], warnings=warnings)

    def run(item: Tuple[int, object]) -> TestResult:
        index, entry = item
        if isinstance(entry, ProgramCase):
            return run_program(binary, entry, workdir, mine, exercise.test_file)
        return run_unit(binary, index, str(entry), workdir, mine, exercise.test_file)

    if parallel:
        with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as pool:
            tests = list(pool.map(run, enumerate(entries)))
    else:
        tests = [run(item) for item in enumerate(entries)]

    if not tests:
        state = "no_tests"
    elif all(t.status == "todo" for t in tests):
        state = "not_started"
    elif all(t.status == "pass" for t in tests):
        state = "complete"
    else:
        state = "started"
    return Report(exercise, state, tests, warnings=warnings, compiler_output=relative(proc.stderr))


# ---- Output ----


def print_detailed(report: Report, src_root: Path, verbose: bool, next_up: Optional[Exercise]) -> None:
    exercise = report.exercise
    print(bold(exercise.id) + "  " + dim(relative(str(exercise.source(src_root)))))
    print()
    if report.state == "compile_error":
        print(red("  ✗ Compile error") + "\n")
        print(indent(report.compiler_output if verbose else report.detail, 4))
        print()
        return
    if report.state in ("missing", "no_tests") and not report.tests:
        print("  " + yellow(report.detail) + "\n")
        return

    for test in report.tests:
        if test.status == "pass":
            print(f"  {green('✓')} {test.name}")
        elif test.status == "todo":
            print(dim(f"  ○ {test.name}  (not implemented)"))
        else:
            print(f"  {red('✗')} {test.name}")
            if test.message:
                print(indent(test.message, 6))
        if test.output.strip() and (verbose or test.status == "fail"):
            print(dim("      Your code printed:"))
            print(dim(indent(truncate_lines(test.output, 12), 8)))
    print()

    if report.warnings:
        for warning in report.warnings[:6]:
            print(yellow(f"  ⚠ {warning}"))
        if len(report.warnings) > 6:
            print(yellow(f"  ⚠ ... {len(report.warnings) - 6} more (grade -v shows the full compiler output)"))
        print()
    if verbose and report.compiler_output.strip():
        print(dim(indent(report.compiler_output, 4)) + "\n")

    failing = sum(t.status == "fail" for t in report.tests)
    todo = sum(t.status == "todo" for t in report.tests)
    if report.state == "complete":
        print(green("  ✓ Passed!" if report.total == 1 else f"  ✓ All {report.total} tests passed!"))
        if next_up:
            print(f"  Next: grade {next_up.id}   " + dim(relative(str(next_up.source(SRC)))))
    elif report.state == "not_started":
        waiting = "1 test" if report.total == 1 else f"{report.total} tests"
        print(dim(f"  ○ Not started: {waiting} waiting. Replace each `throw \"TODO\";` with your code."))
    else:
        summary = [f"{report.passed}/{report.total} passed"]
        if failing:
            summary.append(red(f"{failing} failing"))
        if todo:
            summary.append(dim(f"{todo} not implemented"))
        print("  " + " · ".join(summary))
    print()


STATE_ICONS = {
    "complete": "✓",
    "started": "◐",
    "not_started": "○",
    "compile_error": "✗",
    "no_tests": "–",
    "missing": "?",
}


def compact_line(report: Report, width: int) -> str:
    icon = STATE_ICONS[report.state]
    label = {
        "complete": f"{report.passed}/{report.total}",
        "started": f"{report.passed}/{report.total}",
        "not_started": "not started",
        "compile_error": "compile error",
        "no_tests": "no tests",
        "missing": "missing",
    }[report.state]
    color = {"complete": green, "compile_error": red, "started": yellow}.get(report.state, dim)
    return f"  {color(icon)} {report.exercise.name:<{width}} {color(label)}"


def print_compact(reports: List[Report], collapse_untouched: bool) -> None:
    modules: dict = {}
    for report in reports:
        modules.setdefault(report.exercise.module, []).append(report)
    width = max([len(r.exercise.name) for r in reports] + [30]) + 2
    for module, items in modules.items():
        done = sum(r.state == "complete" for r in items)
        untouched = all(r.state == "not_started" for r in items)
        heading = f"{module:<{width + 4}} {done}/{len(items)}"
        if untouched and collapse_untouched:
            print(dim(f"{heading}  ○ not started"))
            continue
        print(bold(heading))
        for report in items:
            print(compact_line(report, width))
    print()
    complete = sum(r.state == "complete" for r in reports)
    passed = sum(r.passed for r in reports)
    total = sum(r.total for r in reports)
    print(f"Exercises complete: {complete}/{len(reports)}   Tests passing: {passed}/{total}")


def first_incomplete(reports: List[Report]) -> Optional[Exercise]:
    return next((r.exercise for r in reports if r.state != "complete"), None)


# ---- Commands ----


def grade_many(exercises: List[Exercise], src_root: Path, workdir: Path) -> List[Report]:
    runner = compile_runner(workdir)
    show_progress = sys.stderr.isatty() and len(exercises) > 1
    reports: List[Optional[Report]] = [None] * len(exercises)
    with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as pool:
        futures = {
            pool.submit(grade, ex, src_root, workdir, runner, len(exercises) == 1): i
            for i, ex in enumerate(exercises)
        }
        for done, future in enumerate(concurrent.futures.as_completed(futures), start=1):
            reports[futures[future]] = future.result()
            if show_progress:
                sys.stderr.write(f"\rGrading {done}/{len(exercises)}...")
                sys.stderr.flush()
    if show_progress:
        sys.stderr.write("\r" + " " * 30 + "\r")
    return [r for r in reports if r is not None]


def run_interactive(exercise: Exercise, src_root: Path, args: List[str], workdir: Path) -> int:
    source = exercise.source(src_root)
    if not source.exists():
        raise UsageError(f"Can't find {relative(str(source))}")
    runner = compile_runner(workdir)
    binary = workdir / "program"
    sources = student_sources(source) if source.is_dir() else [source]
    proc = subprocess.run(compile_command(sources, src_root, runner, binary), capture_output=True, text=True)
    diagnostics = parse_diagnostics(proc.stderr)
    if proc.returncode != 0:
        print(red("✗ Compile error") + "\n")
        print(indent(compile_error_detail(diagnostics, proc.stderr, src_root), 2))
        return 1
    for d in diagnostics:
        if d.kind == "warning":
            print(yellow(f"⚠ {relative(d.file)}:{d.line}: {d.message}"))
    print(dim(f"── running {exercise.id} (Ctrl-D ends input, Ctrl-C quits) ──"))
    sys.stdout.flush()
    proc = subprocess.run([str(binary), *args], env=RUN_ENV)
    if proc.returncode == TODO_EXIT:
        return 1
    if proc.returncode < 0:
        print(red(describe_exit(proc.returncode)))
    return proc.returncode


def main() -> int:
    parser = argparse.ArgumentParser(
        prog="grade",
        description="Compile an exercise, run its tests, and report what passes.",
        epilog="examples:\n"
        "  grade 01_basics/01_arithmetic   one exercise (also: grade 1/1, or a path to the .cpp)\n"
        "  grade 03                        every exercise in module 03, as a summary\n"
        "  grade --all                     your progress through the whole course\n"
        "  grade --run 01/05               compile and run the exercise's own main()\n"
        "  grade --run 09/04 < data.csv    ...with a file as its input\n"
        "  grade --run 01/05 -- a b        ...with command-line arguments",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument("target", nargs="?", help="exercise or module")
    parser.add_argument("program_args", nargs="*", help=argparse.SUPPRESS)
    parser.add_argument("--all", action="store_true", help="grade everything and show progress")
    parser.add_argument("--run", action="store_true", help="compile and run the exercise's main() yourself")
    parser.add_argument("-v", "--verbose", action="store_true", help="full compiler output and program output")
    parser.add_argument("--src", type=Path, default=SRC, help="grade another copy of src/ (to check reference solutions)")
    options = parser.parse_args()

    if shutil.which(CXX) is None:
        raise UsageError(f"No C++ compiler '{CXX}' found. On macOS run: xcode-select --install")
    src_root = options.src.resolve()
    exercises = discover()

    with tempfile.TemporaryDirectory(prefix="grade-") as tmp:
        workdir = Path(tmp)
        if options.run:
            if not options.target:
                raise UsageError("Usage: grade --run <exercise> [program arguments...]")
            chosen = resolve(options.target, exercises)
            if len(chosen) != 1:
                raise UsageError("--run needs a single exercise, not a module")
            return run_interactive(chosen[0], src_root, options.program_args, workdir)

        if options.program_args:
            raise UsageError(f"Unexpected arguments: {' '.join(options.program_args)}")
        if options.all:
            reports = grade_many(exercises, src_root, workdir)
            print_compact(reports, collapse_untouched=True)
            upcoming = first_incomplete(reports)
            if upcoming:
                print(f"Next up: grade {upcoming.id}   " + dim(relative(str(upcoming.source(SRC)))))
            return 0 if upcoming is None else 1
        if not options.target:
            parser.print_help()
            return 2

        chosen = resolve(options.target, exercises)
        reports = grade_many(chosen, src_root, workdir)
        if len(chosen) == 1:
            index = exercises.index(chosen[0])
            next_up = exercises[index + 1] if index + 1 < len(exercises) else None
            print_detailed(reports[0], src_root, options.verbose, next_up)
        else:
            print_compact(reports, collapse_untouched=False)
            upcoming = first_incomplete(reports)
            if upcoming:
                print(f"Next up: grade {upcoming.id}   " + dim(relative(str(upcoming.source(SRC)))))
        return 0 if all(r.state == "complete" for r in reports) else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except UsageError as error:
        print(red(str(error)), file=sys.stderr)
        sys.exit(2)
    except KeyboardInterrupt:
        sys.exit(130)
