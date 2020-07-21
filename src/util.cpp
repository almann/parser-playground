#include "util.h"

#include <array>
#include <random>

// Scratch pad type for encoding VarUInt.
typedef std::array<uint8_t, 10> varuint_scratch;

size_t encode_varuint(buffer &dest, uint64_t value)
{
    varuint_scratch scratch = {0};
    size_t size = 0;

    // write the varuint in big-endian order
    for (auto cur = scratch.rbegin(); cur != scratch.rend(); cur++)
    {
        *cur = value & 0x7F;
        value >>= 7;
        size += 1;
        if (value == 0)
        {
            break;
        }
    }
    // tag the least significant bit with the end-marker
    *scratch.rbegin() |= 0x80;

    // get the starting position of the serialized value
    auto start = scratch.cbegin() + (scratch.size() - size);

    dest.insert(dest.cend(), start, scratch.cend());
    return size;
}

buffer generate_varuints(int seed, size_t size)
{
    buffer buf;
    buf.reserve(size);

    // TODO Implement me

    return buf;
}