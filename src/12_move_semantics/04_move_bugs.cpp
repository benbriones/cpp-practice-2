// Challenge: Move bugs
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

// Add name to the roster and return a greeting for them: "Welcome, Ada!".
std::string enroll(std::vector<std::string>& roster, std::string name) {
    roster.push_back(std::move(name));
    return "Welcome, " + name + "!";
}

// A Track with the given title. Shouldn't copy or move anything.
Track make_track(const std::string& title) {
    Track track(title);
    return std::move(track);
}

// Move every track from `tracks` onto the end of `archive` without copying any,
// then leave `tracks` empty.
void archive_all(std::vector<Track>& tracks, std::vector<Track>& archive) {
    archive.reserve(archive.size() + tracks.size());
    for (const Track& track : tracks) {
        archive.push_back(std::move(track));
    }
    tracks.clear();
}

// `count` tracks titled "1: <title>", "2: <title>", ... based on base.
std::vector<Track> numbered(Track base, int count) {
    std::vector<Track> result;
    for (int i = 1; i <= count; ++i) {
        Track track = std::move(base);
        track.title = std::to_string(i) + ": " + track.title;
        result.push_back(std::move(track));
    }
    return result;
}
