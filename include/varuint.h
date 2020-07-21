#ifndef PARSER_PLAYGROUND_VARUINT_H
#define PARSER_PLAYGROUND_VARUINT_H

#include <tuple>

#include "types.h"

// Encodes an unsigned integer as VarUInt formatted data.
size_t encode_varuint(buffer &dest, uint64_t value);

// Generates a random VarUInt data stream.
buffer random_varuints(uint_fast64_t seed, uint64_t max, size_t count);

using varuint_result = std::tuple<bool, uint64_t, size_t>;

// Simple VarUInt parser.  Returns the length parsed.
// This is not generic to make sure that we're operating on raw pointers.
// limitation is 2**56 - 1 (8-byte VarUInt8)
inline varuint_result simple_varuint_parse(uint8_t *buf, size_t len) noexcept
{
    size_t read_len = 0U;
    uint64_t value = 0ULL;
    bool found_end = false;

    while (read_len < len && read_len < 8)
    {
        uint8_t octet = *buf++;
        read_len++;

        value = (value << 7U) | (octet & 0x7FU);
        if ((octet & 0x80U) != 0)
        {
            found_end = true;
            break;
        }
    }

    return std::make_tuple(found_end, value, read_len);
}

#endif //PARSER_PLAYGROUND_VARUINT_H
