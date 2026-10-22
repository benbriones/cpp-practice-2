// === Lesson: Move pitfalls ===================================================
//
// std::move only casts. Whether anything is actually moved, and what's left
// behind, depends on the code around it, and the compiler rarely complains.
// The common mistakes:
//
// Using an object after moving from it. A moved-from std::string or std::vector
// is valid but unspecified, and in practice usually empty. Reading it gives
// wrong data rather than a crash:
//
//     std::string key = make_key(user);
//     cache.emplace(std::move(key), value);
//     log("cached " + key);          // key was moved from: probably logs "cached "
//
// Moving from something const. std::move on a const object gives a const T&&,
// which can't bind to T&&, so overload resolution picks the copy constructor
// instead. No error and no warning, just a silent copy:
//
//     const std::string greeting = "hello";
//     words.push_back(std::move(greeting));   // copies
//
// The same goes for anything you only reach through a const reference.
//
// Returning std::move(local). `return local;` lets the compiler build the result
// in the caller's variable; wrapping it in std::move forces a real move instead.
// Clang warns about this one (-Wpessimizing-move). Return locals by name.
//
// Moving the same object more than once. The first move takes the contents; the
// later ones take whatever was left:
//
//     std::string banner = "SALE";
//     for (Shop& shop : shops) {
//         shop.sign = std::move(banner);   // only the first shop gets "SALE"
//     }
//
// Move from an object only at its last use. If you still need it afterwards,
// copy it, or read what you need before the move.
//
// Read more: https://www.learncpp.com/cpp-tutorial/stdmove/
//            https://www.learncpp.com/cpp-tutorial/class-initialization-and-copy-elision/
//
// === Challenge: Move bugs ====================================================
// This code compiles, but it has four move-related bugs. Each one either loses
// data or quietly costs extra copies or moves. Run grade to see them (the
// compiler warns about one), then fix them without changing any signatures.
//
// Track counts its copies and moves so the tests can see what really happened.
//
// ./grade 12_move_semantics/04_move_bugs

#include <string>
#include <utility>
#include <vector>

inline int track_copies = 0;
inline int track_moves = 0;

struct Track {
    explicit Track(std::string track_title) : title(std::move(track_title)) {}
    Track(const Track& other) : title(other.title) { ++track_copies; }
    Track(Track&& other) noexcept : title(std::move(other.title)) { ++track_moves; }
    Track& operator=(const Track& other) {
        title = other.title;
        ++track_copies;
        return *this;
    }
    Track& operator=(Track&& other) noexcept {
        title = std::move(other.title);
        ++track_moves;
        return *this;
    }

    std::string title;
};

// Add name to the end of roster and return a greeting for them.
// The greeting has the form "Welcome, <name>!".
//
// Example:
//   roster = {"Grace"}
//   enroll(roster, "Ada") returns "Welcome, Ada!"
//   roster is now {"Grace", "Ada"}
std::string enroll(std::vector<std::string>& roster, std::string name) {
    roster.push_back(std::move(name));
    return "Welcome, " + name + "!";
}

// Return a new Track with the given title.
// It shouldn't copy or move anything.
//
// Example:
//   Track track = make_track("Intro");
//   // track.title is "Intro"; track_copies is 0, track_moves is 0.
Track make_track(const std::string& title) {
    Track track(title);
    return std::move(track);
}

// Move every track from `tracks` onto the end of `archive`, in order.
// No track should be copied.
// Leave `tracks` empty afterwards.
//
// Example:
//   tracks = {"A", "B"}, archive = {"Old"}
//   archive_all(tracks, archive);
//   // archive is {"Old", "A", "B"}, tracks is empty, track_copies is 0.
void archive_all(std::vector<Track>& tracks, std::vector<Track>& archive) {
    archive.reserve(archive.size() + tracks.size());
    for (const Track& track : tracks) {
        archive.push_back(std::move(track));
    }
    tracks.clear();
}

// Return `count` tracks titled "1: <title>", "2: <title>", ... based on base.
// <title> is base's title. count == 0 returns an empty vector.
//
// Example:
//   numbered(Track("Remix"), 3) returns tracks titled
//   "1: Remix", "2: Remix", "3: Remix"
std::vector<Track> numbered(Track base, int count) {
    std::vector<Track> result;
    for (int i = 1; i <= count; ++i) {
        Track track = std::move(base);
        track.title = std::to_string(i) + ": " + track.title;
        result.push_back(std::move(track));
    }
    return result;
}
