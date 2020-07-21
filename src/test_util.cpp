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
            make_tuple(0, buffer{0x80}),
            make_tuple(128, buffer{0x01, 0x80}),
            make_tuple(130, buffer{0x01, 0x82})
    );

    SECTION(std::to_string(value)) {
        auto size = encode_varuint(buf, value);
        REQUIRE(expected.size() == size);
        REQUIRE(expected == buf);
    }
}