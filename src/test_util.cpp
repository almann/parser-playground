#include <catch2/catch.hpp>

#include <array>
#include <tuple>
#include <string>

#include "util.h"

using std::make_tuple;

typedef std::vector<std::tuple<uint64_t, buffer>> encode_cases;

TEST_CASE("Encode VarUInts", "[varuint]")
{
    buffer buf;

    auto [value, expected] = GENERATE(
            make_tuple(0ULL, buffer{0x80}),
            make_tuple(128ULL, buffer{0x01, 0x80}),
            make_tuple(45499ULL, buffer{0x02, 0x63, 0xbb}),
            make_tuple(2140414ULL, buffer{0x01, 0x02, 0x51, 0xfe}),
            make_tuple(5106961722ULL, buffer{0x13, 0x03, 0x18, 0x1a, 0xba}),
            make_tuple(9007199254741015ULL, buffer{0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97}),
            make_tuple(12784104213654456832ULL, buffer{0x01, 0x31, 0x35, 0x10, 0x61, 0x49, 0x53, 0x4b, 0x14, 0x80})
    );

    SECTION(std::to_string(value)) {
        auto size = encode_varuint(buf, value);
        REQUIRE(expected.size() == size);
        REQUIRE(expected == buf);
    }
}