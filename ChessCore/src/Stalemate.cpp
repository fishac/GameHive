#include "ChessCore.h"

#include <iostream>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
void BoardState::updateStalemateStatus() {
	Square_t kSquare = getKingSquare(turnColor);
	stalemateStatus = ( // If the king is NOT attacked and turnColor has no legal moves
		(getVisibilityMask(!turnColor) & kSquare) == NO_SQUARE
		&& getLegalMovesMask() == EMPTY_BOARD
	) // Or halfmove clock reached 50
	|| halfmoveClock >= 50
	// Or draw by repitition
	|| isDrawByRepitition()
	|| isDrawByInsufficientMaterial();
	if (stalemateStatus) {
		clearLegalMoves();
	}
}

bool BoardState::isDrawByInsufficientMaterial() {
	bool noWhitePawns = numWhitePieces[PAWN] == 0;
	bool noWhiteKnights = numWhitePieces[KNIGHT] == 0;
	bool noWhiteBishops = numWhitePieces[BISHOP] == 0;
	bool noWhiteRooks = numWhitePieces[ROOK] == 0;
	bool noWhiteQueens = numWhitePieces[QUEEN] == 0;
	bool oneWhiteKnight = numWhitePieces[KNIGHT] == 1;
	bool oneWhiteBishop = numWhitePieces[BISHOP] == 1;
	bool noBlackPawns = numBlackPieces[PAWN] == 0;
	bool noBlackKnights = numBlackPieces[KNIGHT] == 0;
	bool noBlackBishops = numBlackPieces[BISHOP] == 0;
	bool noBlackRooks = numBlackPieces[ROOK] == 0;
	bool noBlackQueens = numBlackPieces[QUEEN] == 0;
	bool oneBlackKnight = numBlackPieces[KNIGHT] == 1;
	bool oneBlackBishop = numBlackPieces[BISHOP] == 1;
	
	//std::cout << "numWhitePieces[PAWN] " << numWhitePieces[PAWN] << std::endl;
	//std::cout << "numWhitePieces[KNIGHT] " << numWhitePieces[KNIGHT] << std::endl;
	//std::cout << "numWhitePieces[BISHOP] " << numWhitePieces[BISHOP] << std::endl;
	//std::cout << "numWhitePieces[ROOK] " << numWhitePieces[ROOK] << std::endl;
	//std::cout << "numWhitePieces[QUEEN] " << numWhitePieces[QUEEN] << std::endl;
	//std::cout << "numWhitePieces[KNIGHT] " << numWhitePieces[KNIGHT] << std::endl;
	//std::cout << "numWhitePieces[BISHOP] " << numWhitePieces[BISHOP] << std::endl;
	//std::cout << "numBlackPieces[PAWN] " << numBlackPieces[PAWN] << std::endl;
	//std::cout << "numBlackPieces[KNIGHT] " << numBlackPieces[KNIGHT] << std::endl;
	//std::cout << "numBlackPieces[BISHOP] " << numBlackPieces[BISHOP] << std::endl;
	//std::cout << "numBlackPieces[ROOK] " << numBlackPieces[ROOK] << std::endl;
	//std::cout << "numBlackPieces[QUEEN] " << numBlackPieces[QUEEN] << std::endl;
	//std::cout << "numBlackPieces[KNIGHT] " << numBlackPieces[KNIGHT] << std::endl;
	//std::cout << "numBlackPieces[BISHOP] " << numBlackPieces[BISHOP] << std::endl;
	
	return (
		noWhitePawns 
		&& noWhiteRooks 
		&& noWhiteQueens 
		&& noBlackPawns
		&& noBlackRooks 
		&& noBlackQueens 
	) && ( // K+B vs K
		(noWhiteKnights && oneWhiteBishop)
		|| (oneWhiteKnight && noWhiteBishops)
		|| (noWhiteKnights && noWhiteBishops)
	) && (
		(noBlackKnights && oneBlackBishop)
		|| (oneBlackKnight && noBlackBishops)
		|| (noBlackKnights && noBlackBishops)
	);
}

bool BoardState::isDrawByRepitition() {
	if (boardStateHistory.size() >= 8) {
		int bsrToMatchIdx = boardStateHistory.size()-1;
		BoardStateRecord bsrToMatch = boardStateHistory.at(bsrToMatchIdx);
		int matchedBoardStates = 0;
		for (int j=4; j < boardStateHistory.size(); j += 4) {
			int bsrToCheckIdx = bsrToMatchIdx - j;
			BoardStateRecord bsrToCheck = boardStateHistory.at(bsrToCheckIdx);
			if (BoardStateRecordUtils::equals(bsrToMatch,bsrToCheck)) {
				matchedBoardStates++;
			}
		}
		return matchedBoardStates >= 2;
	} else { 
		return false;
	}
}
}