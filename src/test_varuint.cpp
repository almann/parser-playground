#include <catch2/catch.hpp>

#include <tuple>
#include <string>
#include <algorithm>

#include "varuint.h"

using std::make_tuple;
using parse_func = std::function<varuint_result(uint8_t *, size_t)>;

typedef std::vector<std::tuple<uint64_t, buffer>> encode_cases;

TEST_CASE("Encode/Decode VarUInts", "[varuint]")
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

    auto [parse_name, parse] = GENERATE(
            make_tuple("simple", simple_varuint_parse),
            make_tuple("pext", pext_varuint_parse)
    );

    SECTION(std::to_string(value) + " - " + parse_name)
    {
        auto size = encode_varuint(buf, value);
        REQUIRE(expected.size() == size);
        REQUIRE(expected == buf);

        auto [ok, expected_value, read_len] = parse(buf.data(), buf.size());
        // 8-byte decode limitation
        if (value < 72057594037927936ULL)
        {
            REQUIRE(ok);
            REQUIRE(buf.size() == read_len);
            REQUIRE(value == expected_value);
        }
        else
        {
            REQUIRE(!ok);
        }
    }
}

TEST_CASE("Error Case VarUInt Parsing", "[varuint]")
{
    buffer buf;

    SECTION("Empty")
    {
        auto [ok, expected_value, read_len] = simple_varuint_parse(buf.data(), buf.size());
        REQUIRE(!ok);
        REQUIRE(0ULL == expected_value);
        REQUIRE(0U == read_len);
    }

    SECTION("End")
    {
        auto [ok, expected_value, read_len] = simple_varuint_parse(buf.data(), buf.size());
        REQUIRE(0ULL == expected_value);
        REQUIRE(0U == read_len);
    }
}

TEST_CASE("Random VarUInts", "[varuint]")
{
    // stable seed for deterministic results between test runs
    constexpr auto seed = 0x8BE54DD4F826ACD9ULL;

    constexpr size_t count = 5000000U;

    SECTION("Size 1 Generation")
    {
        auto buf = random_varuints(seed, 127ULL, count);

        CAPTURE(buf);
        REQUIRE(buf.size() == count);
        REQUIRE(std::all_of(buf.cbegin(), buf.cend(), [&](auto octet) { return (octet & 0x80U) != 0U; }));
    }

    SECTION("Size 8 Generation")
    {
        // [0, (2 ** 56) - 1] - up to eight byte range
        auto buf = random_varuints(seed, 72057594037927935ULL, count);

        REQUIRE(buf.size() >= count);

        size_t actual_count = 0U;
        size_t bytes_seen = 0U;
        size_t max_bytes_per_int = 0;
        for (auto octet : buf)
        {
            bytes_seen++;
            if ((octet & 0x80U) != 0U)
            {
                max_bytes_per_int = std::max(max_bytes_per_int, bytes_seen);
                actual_count++;
                bytes_seen = 0U;
            }
        }

        REQUIRE(max_bytes_per_int == 8);
        REQUIRE(count == actual_count);
    }
}