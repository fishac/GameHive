#ifndef BOARDSTATERECORD_H
#define BOARDSTATERECORD_H

#include "Types.h" 
#include <unordered_map>
#include <array>

struct BoardStateRecord {
	std::array<Piece_t,64> whitePieces;
	std::array<Piece_t,64> blackPieces;
	std::array<BoardMask_t,6> whitePieceMasks;
	std::array<BoardMask_t,6> blackPieceMasks;
	Square_t whiteKingSquare;
	Square_t blackKingSquare;
	std::array<bool,2> kSideCastleRights;
	std::array<bool,2> qSideCastleRights;
	Square_t enPassantableSquare;
	Color_t turnColor;
};

namespace ChessCore {
namespace BoardStateRecordUtils {
	bool equals(BoardStateRecord& bsr1, BoardStateRecord& bsr2);
}
}

#endif // BOARDSTATERECORD_H 