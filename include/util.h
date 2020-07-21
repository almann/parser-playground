#ifndef PARSER_PLAYGROUND_UTIL_H
#define PARSER_PLAYGROUND_UTIL_H

#include "types.h"

// Encodes an unsigned integer as VarUInt formatted data.
size_t encode_varuint(buffer &dest, uint64_t value);

// Generates a random VarUInt data stream.
buffer generate_varuints(int seed, size_t size);

#endif //PARSER_PLAYGROUND_UTIL_H
