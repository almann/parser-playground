#include <catch2/catch.hpp>

#include <functional>
#include <tuple>

#include "varuint.h"

using std::make_tuple;

TEST_CASE("Benchmark VarUInt Parsing", "[!benchmark][varuint]")
{
    // stable seed for deterministic results between benchmark runs
    constexpr auto seed = 0x2507A7AC9E29907BULL;
    constexpr size_t count = 100000U;

    auto [size_name, max] = GENERATE(
            make_tuple("2 Byte ", 16383ULL),
            make_tuple("3 Byte ", 2097151ULL),
            make_tuple("4 Byte ", 268435455ULL),
            make_tuple("8 Byte ", 72057594037927935ULL)
    );

    buffer buf = random_varuints(seed, 2097151ULL, count);

    BENCHMARK("Simple " + std::string(size_name) + std::to_string(count))
    {
        uint8_t *curr = buf.data();
        size_t rem = buf.size();
        while (rem > 0)
        {
            auto [ok, value, read_len] = simple_varuint_parse(curr, rem);
            rem -= read_len;
            curr += read_len;
        }
    };

    BENCHMARK("PEXT " + std::string(size_name) + std::to_string(count))
    {
        uint8_t *curr = buf.data();
        size_t rem = buf.size();
        while (rem > 0)
        {
            auto [ok, value, read_len] = pext_varuint_parse(curr, rem);
            rem -= read_len;
            curr += read_len;
        }
    };
}