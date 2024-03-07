#include "ChessCore.h"

#include <iostream>
#include <algorithm>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
std::array<Piece_t,64>& BoardState::getPieces(const Color_t& c) {
	if (c) {
		return whitePieces;
	} else {
		return blackPieces;
	}
}

BoardMask_t& BoardState::getPieceMask(const Color_t& c, const Piece_t& p) {
	if (c) {
		return whitePieceMasks[p];
	} else {
		return blackPieceMasks[p];
	}
}

std::array<int,6>& BoardState::getNumPieces(const Color_t& c) {
	if (c) {
		return numWhitePieces;
	} else {
		return numBlackPieces;
	}
}

Square_t& BoardState::getKingSquare(const Color_t& c) {
	if (c) {
		return whiteKingSquare;
	} else {
		return blackKingSquare;
	}
}

BoardMask_t& BoardState::getPiecesMask(const Color_t& c) {
	if (c) {
		return whitePiecesMask;
	} else {
		return blackPiecesMask;
	}
}

BoardMask_t& BoardState::getDefendedPiecesMask(const Color_t& c) {
	if (c) {
		return whiteDefendedPiecesMask;
	} else {
		return blackDefendedPiecesMask;
	}
}

BoardMask_t& BoardState::getPossibleDefendedPiecesMask(const Color_t& c) {
	if (c) {
		return whitePossibleDefendedPiecesMask;
	} else {
		return blackPossibleDefendedPiecesMask;
	}
}

bool BoardState::getKingsideCastleRights(const Color_t& c) {
	return kSideCastleRights[c];
}

bool BoardState::getQueensideCastleRights(const Color_t& c) {
	return qSideCastleRights[c];
}

uint64_t BoardState::getZobristBoardHash() {
	return zobristBoardHash;
}

void BoardState::removePiece(const Color_t& c, const Square_t& sq) {
	//std::cout << "Removing piece. c: " << c << ", sq: " << Square::getString(sq) << ", p: " << (int) p << std::endl;
	int sq_idx = Square::getIndex(sq);
	Piece_t removalPiece = getPieces(c)[sq_idx];
	if (removalPiece != KING) {
		getPieceMask(c,removalPiece) &= ~sq;
		getNumPieces(c)[removalPiece]--;
	}
	getPieces(c)[sq_idx] = NOPIECE;
	getPiecesMask(c) &= ~sq;
	zobristBoardHash ^= Zobrist::zobristPieceHashes[c][removalPiece-1][sq_idx];
	//std::cout << "Done removing piece." << std::endl;
}

void BoardState::addPiece(const Color_t& c, const Square_t& sq, const Piece_t& p) {
	//std::cout << "Adding piece. c: " << c << ", sq: " << Square::getString(sq) << ", p: " << (int) p << std::endl;
	int sq_idx = Square::getIndex(sq);
	if (p != KING) {
		getPieceMask(c,p) |= sq;
		getNumPieces(c)[p]++;
	}
	getPieces(c)[sq_idx] = p;
	getPiecesMask(c) |= sq;
	if (p == KING) {
		getKingSquare(c) = NO_SQUARE | sq;
	}
	zobristBoardHash ^= Zobrist::zobristPieceHashes[c][p-1][sq_idx];
	//std::cout << "Done adding piece." << std::endl;
}

void BoardState::setEnPassantableSquare(const Square_t& sq) {
	if (enPassantableSquare != NO_SQUARE) {
		int file = Square::getFile(enPassantableSquare);
		zobristBoardHash ^= Zobrist::zobristEnPassantFileHashes[file];
	}
	enPassantableSquare = sq;
	if (enPassantableSquare != NO_SQUARE) {
		int file = Square::getFile(enPassantableSquare);
		zobristBoardHash ^= Zobrist::zobristEnPassantFileHashes[file];
	}
}

void BoardState::toggleTurnColor() {
	turnColor = !turnColor;
	zobristBoardHash ^= Zobrist::zobristBlackTurnHash;
}

void BoardState::initializeMoveGenerationArrays() {
	//std::cout << "Initializing arrays" << std::endl;
	for (int i=0; i<64; i++) {
		visibility[i] = NO_SQUARE;
		legalMoves[i] = NO_SQUARE;
		possibleDefendedPieces[i] = NO_SQUARE;
		pinningPieces[i] = NO_SQUARE;
		xRayVisibility[i] = NO_SQUARE;
	}
	//std::cout << "Done initializing arrays" << std::endl;
}

void BoardState::initializeDefaultWhitePieces() {
	whitePieces[0] = ROOK;
	whitePieces[1] = KNIGHT;
	whitePieces[2] = BISHOP;
	whitePieces[3] = QUEEN;
	whitePieces[4] = KING;
	whitePieces[5] = BISHOP;
	whitePieces[6] = KNIGHT;
	whitePieces[7] = ROOK;
	for (int i=8; i<16; i++) {
		whitePieces[i] = PAWN;
	}
	for (int i=16; i<64; i++) {
		whitePieces[i] = NOPIECE;
	}
}

void BoardState::initializeDefaultBlackPieces() {
	blackPieces[56] = ROOK;
	blackPieces[57] = KNIGHT;
	blackPieces[58] = BISHOP;
	blackPieces[59] = QUEEN;
	blackPieces[60] = KING;
	blackPieces[61] = BISHOP;
	blackPieces[62] = KNIGHT;
	blackPieces[63] = ROOK;
	for (int i=48; i<56; i++) {
		blackPieces[i] = PAWN;
	}
	for (int i=0; i<48; i++) {
		blackPieces[i] = NOPIECE;
	}
}

void BoardState::initializeDerivativeData() {
	numWhitePieces[NOPIECE] = 0;
	numBlackPieces[NOPIECE] = 0;
	numWhitePieces[PAWN] = 0;
	numBlackPieces[PAWN] = 0;
	numWhitePieces[KNIGHT] = 0;
	numBlackPieces[KNIGHT] = 0;
	numWhitePieces[BISHOP] = 0;
	numBlackPieces[BISHOP] = 0;
	numWhitePieces[ROOK] = 0;
	numBlackPieces[ROOK] = 0;
	numWhitePieces[QUEEN] = 0;
	numBlackPieces[QUEEN] = 0;
	whitePieceMasks[NOPIECE] = EMPTY_BOARD;
	blackPieceMasks[NOPIECE] = EMPTY_BOARD;
	whitePieceMasks[PAWN] = EMPTY_BOARD;
	blackPieceMasks[PAWN] = EMPTY_BOARD;
	whitePieceMasks[KNIGHT] = EMPTY_BOARD;
	blackPieceMasks[KNIGHT] = EMPTY_BOARD;
	whitePieceMasks[BISHOP] = EMPTY_BOARD;
	blackPieceMasks[BISHOP] = EMPTY_BOARD;
	whitePieceMasks[ROOK] = EMPTY_BOARD;
	blackPieceMasks[ROOK] = EMPTY_BOARD;
	whitePieceMasks[QUEEN] = EMPTY_BOARD;
	blackPieceMasks[QUEEN] = EMPTY_BOARD;
	whitePiecesMask = EMPTY_BOARD;
	blackPiecesMask = EMPTY_BOARD;
	for (int i=0; i<64; i++) {
		Square_t sq = Square::getSquare(i);
		if (whitePieces[i] == KING) {
			whiteKingSquare = sq;
		} else {
			numWhitePieces[whitePieces[i]]++;
			whitePieceMasks[whitePieces[i]] |= sq;
		}
		if (whitePieces[i] != NOPIECE) {
			whitePiecesMask |= sq;
		}
		if (blackPieces[i] == KING) {
			blackKingSquare = sq;
		} else {
			numBlackPieces[blackPieces[i]]++;
			blackPieceMasks[blackPieces[i]] |= sq;
		}
		if (blackPieces[i] != NOPIECE) {
			blackPiecesMask |= sq;
		}
	}
}

void BoardState::clearAllPieces() {
	for (int i=0; i<64; i++) {
		whitePieces[i] = NOPIECE;
		blackPieces[i] = NOPIECE;
	}
	initializeDerivativeData();
}

void BoardState::initializeZobristBoardHash() {
	zobristBoardHash = (uint64_t) 0;
	if (!turnColor) {
		zobristBoardHash ^= Zobrist::zobristBlackTurnHash;
	}
	if (enPassantableSquare != NO_SQUARE) {
		int file = Square::getFile(enPassantableSquare);
		zobristBoardHash ^= Zobrist::zobristEnPassantFileHashes[file];
	}
	if (kSideCastleRights[WHITE]) {
		zobristBoardHash ^= Zobrist::zobristKSideCastleHashes[WHITE];
	}
	if (kSideCastleRights[BLACK]) {
		zobristBoardHash ^= Zobrist::zobristKSideCastleHashes[BLACK];
	}
	if (qSideCastleRights[WHITE]) {
		zobristBoardHash ^= Zobrist::zobristQSideCastleHashes[WHITE];
	}
	if (qSideCastleRights[BLACK]) {
		zobristBoardHash ^= Zobrist::zobristQSideCastleHashes[BLACK];
	}
	for (int i=0; i<64; i++) {
		Piece_t wp = whitePieces[i];
		Piece_t bp = blackPieces[i];
		if (wp != NOPIECE) {
			zobristBoardHash ^= Zobrist::zobristPieceHashes[WHITE][wp-1][i];
		}
		if (bp != NOPIECE) {
			zobristBoardHash ^= Zobrist::zobristPieceHashes[BLACK][bp-1][i];
		}
	}
}

}