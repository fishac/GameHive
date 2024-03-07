#include "ChessCore.h"

#include <algorithm>
#include <iostream>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
bool BoardState::makeMove(const Square_t& from, const Square_t& to) {
	if (isMoveLegal(from,to) && !isRewound() && !moveRequiresPromotion(from,to)) {
	// If the move is legal 
		makeLegalMove(from,to);
		updateLegality();
		return true;
	} else {
		// If the move is not legal, return false;
		return false;
	}
}


void BoardState::makeLegalMove(const Square_t& from, const Square_t& to) {
	//std::cout << "Making legal move" << std::endl;
	// Set up a new MoveRecord
	MoveRecord mr;
	mr.from = from;
	mr.to = to;
	mr.capturedPiece = NOPIECE;
	mr.capturedPieceSquare = NO_SQUARE;
	mr.promotionPiece = NOPIECE;
	mr.priorHalfmoveClock = halfmoveClock;
	mr.priorEnPassantableSquare = enPassantableSquare;
	mr.lostKSideCastleRights = {false, false};
	mr.lostQSideCastleRights = {false, false};
	mr.moveWasKSideCastle = false;
	mr.moveWasQSideCastle = false;
	mr.moveWasNullMove = false;
	// Set up new enPassantableSquare
	Square_t tempEnPassantableSquare = NO_SQUARE;
	// Get the piece being moved
	Piece_t movingPiece = getPiece(from, turnColor);
	mr.movingPiece = movingPiece;
	if (movingPiece == PAWN && turnColor && (Square::nn(from) == to)) {
	// If moving the White pawn two squares
		// Mark the square between from and two as capturable via en passant
		tempEnPassantableSquare = Square::n(from);
	} else if (movingPiece == PAWN && !turnColor && (Square::ss(from) == to)) {
	// If moving the Black pawn two squares
		// Mark the square between from and two as capturable via en passant
		tempEnPassantableSquare = Square::s(from);
	} else if (movingPiece == KING && (Square::ee(from) == to)) {
	// If moving king two squares east (castling short, kingside)
		// Move rook as well
		movePieceForce(Square::hRookStartingSquare(turnColor), Square::hRookCastleTarget(turnColor), ROOK);
		// Lose castle rights after this
		revokeKSideCastleRights(turnColor, &mr);
		if (qSideCastleRights[turnColor]) {
			revokeQSideCastleRights(turnColor, &mr);
		}
		// Record the castle move
		mr.moveWasKSideCastle = true;
	} else if (movingPiece == KING && (Square::ww(from) == to)) {
	// If moving king two squares west (castling long, queenside)
		// Move rook as well
		movePieceForce(Square::aRookStartingSquare(turnColor), Square::aRookCastleTarget(turnColor), ROOK);
		// Lose castle rights after this
		if (kSideCastleRights[turnColor]) {
			revokeKSideCastleRights(turnColor, &mr);
		}
		revokeQSideCastleRights(turnColor, &mr);
		// Record the castle move
		mr.moveWasQSideCastle = true;
	} else if (movingPiece == ROOK && Square::aRookStartingSquare(turnColor) == from && qSideCastleRights[turnColor]) {
		revokeQSideCastleRights(turnColor, &mr);
	} else if (movingPiece == ROOK && Square::hRookStartingSquare(turnColor) == from && kSideCastleRights[turnColor]) {
		revokeKSideCastleRights(turnColor, &mr);
	} else if (movingPiece == KING) {
		if (kSideCastleRights[turnColor]) {
			revokeKSideCastleRights(turnColor, &mr);
		}
		if (qSideCastleRights[turnColor]) {
			revokeQSideCastleRights(turnColor, &mr);
		}
	}
	
	setEnPassantableSquare(tempEnPassantableSquare);
	movePiece(from, to, movingPiece, &mr);
	toggleTurnColor();
	if (turnColor) {
		moveNumber++;
	}
	activePly++;
	totalPlies++;
	moveHistory.push_back(mr);
	appendBoardStateHistory();
}

bool BoardState::makeMoveAndPromote(const Square_t& from, const Square_t& to, const Piece_t& promotionPiece) {
	if (isMoveLegal(from,to) && getPiece(from, turnColor) == PAWN && Piece::isValidPromotionPiece(promotionPiece)) {	
		makeLegalMoveAndPromote(from,to,promotionPiece);
		updateLegality();
		return true;
	} else {
		return false;
	}
}

void BoardState::makeLegalMoveAndPromote(const Square_t& from, const Square_t& to, const Piece_t& promotionPiece) {
	// Set up a new MoveRecord
	MoveRecord mr;
	mr.from = from;
	mr.to = to;
	mr.movingPiece = PAWN;
	mr.capturedPiece = NOPIECE;
	mr.capturedPieceSquare = NO_SQUARE;
	mr.promotionPiece = promotionPiece;
	mr.priorHalfmoveClock = halfmoveClock;
	mr.priorEnPassantableSquare = enPassantableSquare;
	mr.lostKSideCastleRights = {false, false};
	mr.lostQSideCastleRights = {false, false};
	mr.moveWasKSideCastle = false;
	mr.moveWasQSideCastle = false;
	mr.moveWasNullMove = false;

	promotePawn(from, to, promotionPiece, &mr);
	
	moveHistory.push_back(mr);
	setEnPassantableSquare(NO_SQUARE);
	toggleTurnColor();
	if (turnColor) {
		moveNumber++;
	}
	activePly++;
	totalPlies++;
	halfmoveClock = 0;
	appendBoardStateHistory();
}

bool BoardState::makeMove(const ExtendedMove& m) {
	if (m.promotionPiece == NOPIECE) {
		return makeMove(m.from,m.to);
	} else {
		return makeMoveAndPromote(m.from,m.to,m.promotionPiece);
	}
}

void BoardState::makeLegalExtendedMove(const ExtendedMove& m) {
	if (m.promotionPiece == NOPIECE) {
		return makeLegalMove(m.from,m.to);
	} else {
		return makeLegalMoveAndPromote(m.from,m.to,m.promotionPiece);
	}
}

void BoardState::movePieceForce(const Square_t& from, const Square_t& to, const Piece_t& p) {
	addPiece(turnColor, to, p);
	removePiece(turnColor, from);
}

void BoardState::movePiece(const Square_t& from, const Square_t& to, const Piece_t& p, MoveRecord* mr) {
	halfmoveClock = halfmoveClock+1;
	if ((to & getPiecesMask(!turnColor)) != NO_SQUARE) {
		halfmoveClock = 0;
		removePiece(!turnColor, to, mr);
	} else if (p == PAWN && (to & getPiecesMask(!turnColor)) == NO_SQUARE && turnColor && (Square::s(to) & getPiecesMask(!turnColor)) != NO_SQUARE) {
		removePiece(!turnColor, Square::s(to), mr);
	} else if (p == PAWN && (to & getPiecesMask(!turnColor)) == NO_SQUARE && !turnColor && (Square::n(to) & getPiecesMask(!turnColor)) != NO_SQUARE) {
		removePiece(!turnColor, Square::n(to), mr);
	} 
	if (p == PAWN) {
		halfmoveClock = 0;
	}
	removePiece(turnColor, from);
	addPiece(turnColor, to, p);
}

void BoardState::promotePawn(const Square_t& from, const Square_t& to, const Piece_t& promotionPiece, MoveRecord* mr) {
	if ((to & getPiecesMask(!turnColor)) != EMPTY_BOARD) {
		removePiece(!turnColor, to, mr);
	}
	removePiece(turnColor, from);
	addPiece(turnColor, to, promotionPiece);
}

void BoardState::removePiece(const Color_t& c, const Square_t& sq, MoveRecord* mr) { 
	int sq_idx = Square::getIndex(sq);
	std::array<Piece_t,64>& pieces = getPieces(c);
	const Piece_t p = pieces[sq_idx];
	if (p != NOPIECE) {
		removePiece(c, sq);
		mr->capturedPiece = p;
		mr->capturedPieceSquare = sq;
	}
	if (p == ROOK) {
		// If a rook is being taken and is on a starting square, 
		// set that side's castle rights to false.
		if (sq == Square::aRookStartingSquare(c) && qSideCastleRights[c]) {
			revokeQSideCastleRights(c, mr);
		} else if (sq == Square::hRookStartingSquare(c) && kSideCastleRights[c]) {
			revokeKSideCastleRights(c, mr);
		}
	} 
}

void BoardState::revokeKSideCastleRights(const Color_t& c, MoveRecord* mr) {
	kSideCastleRights[c] = false;
	zobristBoardHash ^= Zobrist::zobristKSideCastleHashes[c];
	mr->lostKSideCastleRights[c] = true;
}

void BoardState::revokeQSideCastleRights(const Color_t& c, MoveRecord* mr) {
	qSideCastleRights[c] = false;
	zobristBoardHash ^= Zobrist::zobristQSideCastleHashes[c];
	mr->lostQSideCastleRights[c] = true;
}

void BoardState::appendBoardStateHistory() {	
	BoardStateRecord bsr  = {
		whitePieces,
		blackPieces,
		whitePieceMasks,
		blackPieceMasks,
		whiteKingSquare,
		blackKingSquare,
		kSideCastleRights,
		qSideCastleRights,
		enPassantableSquare,
		turnColor
	};
	boardStateHistory.push_back(bsr);
}

MoveRecord BoardState::getLastMoveRecord() {
	return moveHistory.back();
}

void BoardState::makeNullMove() {
	// Set up a new MoveRecord
	MoveRecord mr;
	mr.from = NO_SQUARE;
	mr.to = NO_SQUARE;
	mr.movingPiece = PAWN;
	mr.capturedPiece = NOPIECE;
	mr.capturedPieceSquare = NO_SQUARE;
	mr.promotionPiece = NOPIECE;
	mr.priorHalfmoveClock = halfmoveClock;
	mr.priorEnPassantableSquare = enPassantableSquare;
	mr.lostKSideCastleRights = {false, false};
	mr.lostQSideCastleRights = {false, false};
	mr.moveWasKSideCastle = false;
	mr.moveWasQSideCastle = false;
	// This is a null move
	mr.moveWasNullMove = true;
	moveHistory.push_back(mr);
	// Don't move any pieces, just set up next move
	setEnPassantableSquare(NO_SQUARE);
	toggleTurnColor();
	if (turnColor) {
		moveNumber++;
	}
	activePly++;
	totalPlies++;
	appendBoardStateHistory();
}
}