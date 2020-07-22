#ifndef PARSER_PLAYGROUND_VARUINT_H
#define PARSER_PLAYGROUND_VARUINT_H

#include <tuple>
#include <algorithm>
#include <cstring>

#include <x86intrin.h>

#include "types.h"

// Encodes an unsigned integer as VarUInt formatted data.
size_t encode_varuint(buffer &dest, uint64_t value);

// Generates a random VarUInt data stream.
buffer random_varuints(uint_fast64_t seed, uint64_t max, size_t count);

using varuint_result = std::tuple<bool, uint64_t, size_t>;

// Simple VarUInt parser.  Returns the length parsed.
// This is not generic to make sure that we're operating on raw pointers.
// Limitation is 2**56 - 1 (8-byte VarUInt8)
inline varuint_result simple_varuint_parse(uint8_t *buf, size_t len) noexcept
{
    bool found_end = false;
    size_t read_len = 0U;
    uint64_t value = 0ULL;

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


// BMI PEXT VarUInt parser.  Technically scalar but can parse an 8-byte chunk.
// Returns the length parsed.
// This is not generic to make sure that we're operating on raw pointers.
// Limitation is 2**56 - 1 (8-byte VarUInt8).
//
// NB: not portable--requires x86-64 (BMI 1/2), specifically LZCNT/PEXT, also uses __builtin_bswap to get MOVBE
// https://www.felixcloutier.com/x86/lzcnt
// https://www.felixcloutier.com/x86/pext
inline varuint_result pext_varuint_parse(uint8_t *buf, size_t len) noexcept
{
    bool found_end = false;
    size_t read_len = 0UL;
    uint64_t value = 0ULL;
    uint64_t raw = 0ULL;

    constexpr uint64_t k_high_mask = 0x8080808080808080ULL;
    constexpr uint64_t k_content_mask =  0x7F7F7F7F7F7F7F7FULL;

    // unaligned load and byte swap to get endian right
    size_t raw_len = std::min(8UL, len);
    memcpy(&raw, buf, raw_len);
    raw = __builtin_bswap64(raw);

    uint64_t high_bits = raw & k_high_mask;

    // overflow and premature end of buffer case is no set bits
    if (high_bits != 0)
    {
        // count the leading zero bits to find the first set bit (of only the high bits), and then
        // add in the whole octet width--this is how many of the most significant bits are the VarUInt
        uint bit_len = _lzcnt_u64(high_bits) + 8U;

        // extract the content bits we care about (note that we zeroed out anything we don't care about first)
        value = _pext_u64((raw >> (64 - bit_len)), k_content_mask);
        found_end = true;
        read_len = bit_len >> 3U;
    }

    return std::make_tuple(found_end, value, read_len);
}

#endif //PARSER_PLAYGROUND_VARUINT_H
