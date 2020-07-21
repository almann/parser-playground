#ifndef PARSER_PLAYGROUND_VARUINT_H
#define PARSER_PLAYGROUND_VARUINT_H

#include "types.h"

// Encodes an unsigned integer as VarUInt formatted data.
size_t encode_varuint(buffer &dest, uint64_t value);

// Generates a random VarUInt data stream.
buffer random_varuints(uint_fast64_t seed, uint64_t max, size_t count);

#endif //PARSER_PLAYGROUND_VARUINT_H
