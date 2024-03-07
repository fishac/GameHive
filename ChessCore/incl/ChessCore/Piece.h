#ifndef PIECE_H
#define PIECE_H

#include "Types.h" 

namespace ChessCore {
namespace Piece {
	const Piece_t NOPIECE = 0;
	const Piece_t PAWN = 1;
	const Piece_t KNIGHT = 2;
	const Piece_t BISHOP = 3;
	const Piece_t ROOK = 4;
	const Piece_t QUEEN = 5;
	const Piece_t KING = 6;
	bool isValidPiece(const Piece_t& p);
	bool isValidPromotionPiece(const Piece_t& p);
}
}

#endif // PIECE_H 