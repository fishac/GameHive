#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef uint64_t BoardMask_t;
typedef uint64_t Square_t;
typedef int8_t Piece_t;
typedef bool Color_t;

const BoardMask_t EMPTY_BOARD = ((BoardMask_t) 0);
const Square_t NO_SQUARE = ((Square_t) 0);

#endif // TYPES_H 