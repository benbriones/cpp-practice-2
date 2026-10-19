#include "grader.hpp"
#include "12_move_semantics/04_move_bugs.cpp"

TEST("enroll: greets the student by name") {
    std::vector<std::string> roster;
    CHECK_EQ(enroll(roster, "Ada"), "Welcome, Ada!");
}

TEST("enroll: adds them to the roster") {
    std::vector<std::string> roster{"Grace"};
    enroll(roster, "Alan Mathison Turing");
    CHECK_EQ(roster, {"Grace", "Alan Mathison Turing"});
}

TEST("make_track: no copies or moves") {
    Track track = make_track("Intro");
    CHECK_EQ(track.title, "Intro");
    CHECK_EQ(track_copies, 0);
    CHECK_EQ(track_moves, 0);
}

TEST("archive_all: moves every track across") {
    std::vector<Track> tracks;
    tracks.emplace_back("A");
    tracks.emplace_back("B");
    std::vector<Track> archive;
    archive.emplace_back("Old");
    archive_all(tracks, archive);
    CHECK_EQ(archive.size(), 3u);
    CHECK_EQ(archive[1].title, "A");
    CHECK_EQ(archive[2].title, "B");
    CHECK(tracks.empty(), "tracks should be empty afterwards");
}

TEST("archive_all: never copies a track") {
    std::vector<Track> tracks;
    tracks.reserve(3);
    tracks.emplace_back("A");
    tracks.emplace_back("B");
    tracks.emplace_back("C");
    std::vector<Track> archive;
    track_copies = 0;
    track_moves = 0;
    archive_all(tracks, archive);
    CHECK_EQ(track_copies, 0);
    CHECK_EQ(track_moves, 3);
}

TEST("numbered: every track keeps the base title") {
    std::vector<Track> tracks = numbered(Track("Remix"), 3);
    CHECK_EQ(tracks.size(), 3u);
    CHECK_EQ(tracks[0].title, "1: Remix");
    CHECK_EQ(tracks[1].title, "2: Remix");
    CHECK_EQ(tracks[2].title, "3: Remix");
}

TEST("numbered: zero tracks") {
    CHECK_EQ(numbered(Track("Remix"), 0).size(), 0u);
}
