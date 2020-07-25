#include "varuint.h"

#include <array>
#include <random>
#include <functional>

// Scratch pad type for encoding VarUInt.
typedef std::array<uint8_t, 10> varuint_scratch;

size_t encode_varuint(buffer &dest, uint64_t value) {
    varuint_scratch scratch = {0};
    size_t size = 0;

    // write the varuint in big-endian order
    for (auto cur = scratch.rbegin(); cur != scratch.rend(); cur++) {
        *cur = value & 0x7FU;
        value >>= 7U;
        size += 1;
        if (value == 0U) {
            break;
        }
    }
    // tag the least significant bit with the end-marker
    *scratch.rbegin() |= 0x80U;

    // get the starting position of the serialized value
    auto start = scratch.cbegin() + (scratch.size() - size);

    dest.insert(dest.cend(), start, scratch.cend());
    return size;
}

buffer random_varuints(uint_fast64_t seed, uint64_t max, size_t count) {
    buffer buf;

    // seed from a particular point for deterministic testing
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<uint64_t> dist(0ULL, max);
    // bind to a simple function
    auto rand = [&]() { return dist(gen); };

    for (int i = 0; i < count; i++) {
        encode_varuint(buf, rand());
    }

    return buf;
}