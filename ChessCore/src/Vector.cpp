#include "ChessCore.h"

#include <algorithm>
#include <iostream>

namespace ChessCore {
namespace Vector {
	bool squareInVector(const std::vector<Square_t>& v, const Square_t& sq) {
		return std::find(v.begin(), v.end(), sq) != v.end();
	}
	
	void printSquareVector(const std::vector<Square_t>& v) {
		for(auto iter = v.begin(); iter != v.end(); iter++) {
			std::cout << Square::getString(*iter) << ", ";
		}
		std::cout << std::endl;
	}
	
	void printMoveVector(const std::vector<Move>& v) {
		for(auto iter = v.begin(); iter != v.end(); iter++) {
			std::cout << "(" << Square::getString(iter->from) << Square::getString(iter->to) << ") ";
		}
		std::cout << std::endl;
	}
	
	void printExtendedMoveVector(const std::vector<ExtendedMove>& v, const Color_t& c) {
		for(auto iter = v.begin(); iter != v.end(); iter++) {
			std::cout << Square::getString(iter->from) << Square::getString(iter->to);
			if (iter->promotionPiece != Piece::NOPIECE) {
				std::cout << "=" << FEN::getFENPieceLabel(iter->promotionPiece,c);
			}
			std::cout << ", ";
		}
		std::cout << std::endl;
	}
	
	BoardMask_t getVectorMask(const std::vector<Square_t>& v) {
		BoardMask_t bm = NO_SQUARE;
		for(auto iter = v.begin(); iter != v.end(); iter++) {
			bm |= *iter;
		}
		return bm;
	}
}
}