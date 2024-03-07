#include "ChessCore.h"

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
namespace BoardStateRecordUtils {
	bool equals(BoardStateRecord& bsr1, BoardStateRecord& bsr2) {
		return (
			bsr1.whitePieceMasks[PAWN] == bsr2.whitePieceMasks[PAWN]
			&& bsr1.whitePieceMasks[KNIGHT] == bsr2.whitePieceMasks[KNIGHT]
			&& bsr1.whitePieceMasks[BISHOP] == bsr2.whitePieceMasks[BISHOP]
			&& bsr1.whitePieceMasks[ROOK] == bsr2.whitePieceMasks[ROOK]
			&& bsr1.whitePieceMasks[QUEEN] == bsr2.whitePieceMasks[QUEEN]
			&& bsr1.blackPieceMasks[PAWN] == bsr2.blackPieceMasks[PAWN]
			&& bsr1.blackPieceMasks[KNIGHT] == bsr2.blackPieceMasks[KNIGHT]
			&& bsr1.blackPieceMasks[BISHOP] == bsr2.blackPieceMasks[BISHOP]
			&& bsr1.blackPieceMasks[ROOK] == bsr2.blackPieceMasks[ROOK]
			&& bsr1.blackPieceMasks[QUEEN] == bsr2.blackPieceMasks[QUEEN]
			&& bsr1.whiteKingSquare == bsr2.whiteKingSquare 
			&& bsr1.blackKingSquare == bsr2.blackKingSquare			
			&& bsr1.kSideCastleRights[WHITE] == bsr2.kSideCastleRights[WHITE]
			&& bsr1.qSideCastleRights[WHITE] == bsr2.qSideCastleRights[WHITE]
			&& bsr1.kSideCastleRights[BLACK] == bsr2.kSideCastleRights[BLACK]
			&& bsr1.qSideCastleRights[BLACK] == bsr2.qSideCastleRights[BLACK]
			&& bsr1.enPassantableSquare == bsr2.enPassantableSquare
			&& bsr1.turnColor == bsr2.turnColor
		);
	}
}
}