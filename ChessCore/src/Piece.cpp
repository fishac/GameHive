#include "ChessCore.h"

namespace ChessCore {
namespace Piece {
	bool isValidPiece(const Piece_t& p) {
		return p < 7 && p > 0; 
	}

	bool isValidPromotionPiece(const Piece_t& p) {
		return p < 6 && p > 1; 
	}
}
}