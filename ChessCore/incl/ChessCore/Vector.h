#ifndef VECTOR_H
#define VECTOR_H

#include "Types.h"
#include "Move.h"
#include <vector>

namespace ChessCore {
namespace Vector {
	bool squareInVector(const std::vector<Square_t>& v, const Square_t& s);
	void printSquareVector(const std::vector<Square_t>& v);
	void printMoveVector(const std::vector<Move>& v);
	void printExtendedMoveVector(const std::vector<ExtendedMove>& v, const Color_t& c);
	BoardMask_t getVectorMask(const std::vector<Square_t>& v);
}
}


#endif // VECTOR_H 