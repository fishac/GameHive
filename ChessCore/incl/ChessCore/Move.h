#ifndef MOVE_H
#define MOVE_H

#include "Types.h" 
#include <string> 
#include <array>

struct Move {
	Square_t from;
	Square_t to;
};

struct ExtendedMove {
	Square_t from;
	Square_t to;
	Piece_t promotionPiece;
};

struct MoveRecord {
	Square_t from;
	Square_t to;
	Piece_t movingPiece;
	Piece_t capturedPiece;
	Piece_t promotionPiece;
	Square_t capturedPieceSquare;
	Square_t priorEnPassantableSquare;
	int priorHalfmoveClock;
	std::array<bool,2> lostKSideCastleRights;
	std::array<bool,2> lostQSideCastleRights;
	bool moveWasKSideCastle;
	bool moveWasQSideCastle;
	bool moveWasNullMove;
};

namespace ChessCore {
namespace MoveUtils {
	std::string getString(Move& m);
	std::string getString(ExtendedMove& m);
	std::string getString(ExtendedMove& m, const Color_t& turnColor);
	bool extendedMoveEquals(const ExtendedMove& m1, const ExtendedMove& m2);
	ExtendedMove getExtendedMove(std::string moveString);
}
}

#endif // MOVE_H 