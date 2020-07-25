#include <catch2/catch.hpp>

#include <functional>
#include <tuple>
#include <array>

#include "varuint.h"

using std::make_tuple;

template<auto parse>
inline varuint_result parse_all(buffer &buf) {
    uint8_t *curr = buf.data();
    size_t rem = buf.size();
    bool all_ok = true;
    uint64_t sum = 0;
    size_t total_len = 0;

    while (rem > 0) {
        auto[ok, value, read_len] = parse(curr, rem);
        rem -= read_len;
        curr += read_len;

        // make sure the results of parsing are observable to avoid optimization
        all_ok = all_ok || ok;
        sum += value;
        total_len += read_len;
    }
    return make_tuple(all_ok, sum, total_len);
}

TEST_CASE("Benchmark VarUInt Parsing", "[!benchmark][varuint]") {
    // stable seed for deterministic results between benchmark runs
    constexpr auto seed = 0x2507A7AC9E29907BULL;
    constexpr size_t count = 1000000U;

    constexpr auto maximums = std::array{
        make_tuple("2 Byte ", 16383ULL),
        make_tuple("3 Byte ", 2097151ULL),
        make_tuple("4 Byte ", 268435455ULL),
        make_tuple("8 Byte ", 72057594037927935ULL)
    };

    for (auto[size_name, maximum] : maximums) {
        buffer buf = random_varuints(seed, maximum, count);

        BENCHMARK("Simple " + std::string(size_name) + std::to_string(count)) {
            return parse_all<simple_varuint_parse>(buf);
        };

        BENCHMARK("PEXT " + std::string(size_name) + std::to_string(count)) {
            return parse_all<pext_varuint_parse>(buf);
        };
    }
}