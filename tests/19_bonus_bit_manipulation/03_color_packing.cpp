#include "grader.hpp"
#include "19_bonus_bit_manipulation/03_color_packing.cpp"

TEST("pack: channel order is RRGGBBAA") {
    CHECK_EQ(pack(Color{0x12, 0x34, 0x56, 0x78}), 0x12345678u);
    CHECK_EQ(pack(Color{255, 0, 0, 255}), 0xFF0000FFu);
    CHECK_EQ(pack(Color{0, 0, 0, 0}), 0u);
    CHECK_EQ(pack(Color{255, 255, 255, 255}), 0xFFFFFFFFu);
}

TEST("unpack") {
    CHECK_EQ(unpack(0x12345678u), Color{0x12, 0x34, 0x56, 0x78});
    CHECK_EQ(unpack(0x00FF0080u), Color{0, 255, 0, 128});
    CHECK_EQ(unpack(0xFFFFFFFFu), Color{255, 255, 255, 255});
}

TEST("pack and unpack round-trip") {
    Color orange{255, 128, 0, 200};
    CHECK_EQ(unpack(pack(orange)), orange);
    CHECK_EQ(pack(unpack(0xDEADBEEFu)), 0xDEADBEEFu);
}

TEST("to_hex") {
    CHECK_EQ(to_hex(Color{255, 128, 0, 255}), "#FF8000FF");
    CHECK_EQ(to_hex(Color{0, 0, 0, 0}), "#00000000");
    CHECK_EQ(to_hex(Color{0x0A, 0xBC, 0x01, 0x7F}), "#0ABC017F");
}

TEST("from_hex") {
    CHECK_EQ(from_hex("#FF8000FF"), Color{255, 128, 0, 255});
    CHECK_EQ(from_hex("#0abc017f"), Color{0x0A, 0xBC, 0x01, 0x7F});
    CHECK_EQ(from_hex(to_hex(Color{1, 2, 3, 4})), Color{1, 2, 3, 4});
}

TEST("from_hex: rejects malformed text") {
    CHECK_THROWS(std::invalid_argument, from_hex(""));
    CHECK_THROWS(std::invalid_argument, from_hex("FF8000FF"));
    CHECK_THROWS(std::invalid_argument, from_hex("#FF8000"));
    CHECK_THROWS(std::invalid_argument, from_hex("#FF8000FF0"));
    CHECK_THROWS(std::invalid_argument, from_hex("#FF80G0FF"));
}

TEST("blend: averages each channel, rounding down") {
    CHECK_EQ(blend(Color{0, 0, 0, 0}, Color{255, 255, 255, 255}), Color{127, 127, 127, 127});
    CHECK_EQ(blend(Color{10, 20, 30, 40}, Color{20, 40, 60, 80}), Color{15, 30, 45, 60});
    CHECK_EQ(blend(Color{1, 3, 200, 255}, Color{2, 4, 100, 255}), Color{1, 3, 150, 255});
}

TEST("blend: channels don't leak into each other") {
    CHECK_EQ(blend(Color{255, 0, 255, 0}, Color{255, 1, 255, 1}), Color{255, 0, 255, 0});
}

TEST("to_binary") {
    CHECK_EQ(to_binary(Color{255, 128, 0, 255}), "11111111 10000000 00000000 11111111");
    CHECK_EQ(to_binary(Color{1, 2, 4, 8}), "00000001 00000010 00000100 00001000");
}
