#include "ChessCore.h"
#include <iostream>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
bool BoardState::isMoveLegal(const Square_t& from, const Square_t& to) {
	// If game has not yet resulted in checkmate or stalemate and move is in legalMoves,
	// the move is legal
	if (!(checkmateStatus || stalemateStatus)) {
		return (legalMoves[Square::getIndex(from)] & to) != EMPTY_BOARD;
	} else {
		return false;
	}
}

bool BoardState::isMoveLegal(const Move& m) {
	return isMoveLegal(m.from, m.to);
}

bool BoardState::isMoveLegal(const ExtendedMove& m) {
	return isMoveLegal(m.from, m.to);
}

bool BoardState::isMoveLegal(const ExtendedMoveIdx& m) {
	return isMoveLegal(Square::getSquare(m.fromIdx), Square::getSquare(m.toIdx));
}
  
bool BoardState::isLegalFromSquare(const Square_t& sq) {
	int sq_idx = Square::getIndex(sq);
	return legalMoves[sq_idx] != NO_SQUARE;
}

bool BoardState::moveRequiresPromotion(const Square_t& from, const Square_t& to) {
	return getPieces(turnColor)[Square::getIndex(from)] == PAWN
	&& (
		(turnColor && Square::onSeventhRank(from) && Square::onEighthRank(to))
		|| (!turnColor && Square::onSecondRank(from) && Square::onFirstRank(to))
	);
}

bool BoardState::moveRequiresPromotion(const Move& m) {
	return moveRequiresPromotion(m.from,m.to);
}

bool BoardState::moveRequiresPromotion(const ExtendedMove& m) {
	return moveRequiresPromotion(m.from,m.to) && m.promotionPiece != NOPIECE;
}

bool BoardState::moveIsEnPassant(const Move& m) {
	return moveIsEnPassant(m.from,m.to);
}

bool BoardState::moveIsEnPassant(const ExtendedMove& m) {
	return moveIsEnPassant(m.from,m.to) && m.promotionPiece == NOPIECE;
}

bool BoardState::moveIsEnPassant(const Square_t& from, const Square_t& to) {
	return (
		turnColor 
		&& whitePieces[Square::getIndex(from)] == PAWN
		&& (to == Square::nw(from) || to == Square::ne(from)) 
		&& to == enPassantableSquare
	) || (
		!turnColor 
		&& blackPieces[Square::getIndex(from)] == PAWN
		&& (to == Square::sw(from) || to == Square::se(from)) 
		&& to == enPassantableSquare
	);
}

bool BoardState::moveIsCapture(const Square_t& from, const Square_t& to) {
	return (
		(to & getPiecesMask(!turnColor)) != NO_SQUARE
	) || moveIsEnPassant(from,to);
}

bool BoardState::moveIsCapture(const Move& m) {
	return moveIsCapture(m.from, m.to);
}

bool BoardState::moveIsCapture(const ExtendedMove& m) {
	return moveIsCapture(m.from, m.to);
}

bool BoardState::moveIsCastle(const Square_t& from, const Square_t& to) {
	return getPiece(from, turnColor) == KING 
	&& (
		(Square::ee(from) == to && kSideCastleRights[turnColor])
		|| (Square::ww(from) == to && qSideCastleRights[turnColor])
	);
}

bool BoardState::moveIsCastle(const Move& m) {
	return moveIsCastle(m.from, m.to);
}

bool BoardState::moveIsCastle(const ExtendedMove& m) {
	return moveIsCastle(m.from, m.to) && m.promotionPiece == NOPIECE;
}

bool BoardState::moveIsKSideCastle(const Square_t& from, const Square_t& to)  {
	return getPiece(from, turnColor) == KING 
	&& (Square::ee(from) == to && kSideCastleRights[turnColor]);
}

bool BoardState::moveIsKSideCastle(const Move& m) {
	return moveIsKSideCastle(m.from, m.to);
}

bool BoardState::moveIsKSideCastle(const ExtendedMove& m) {
	return moveIsKSideCastle(m.from, m.to) && m.promotionPiece == NOPIECE;
}

bool BoardState::moveIsQSideCastle(const Square_t& from, const Square_t& to) {
	return getPiece(from, turnColor) == KING 
	&& (Square::ww(from) == to && qSideCastleRights[turnColor]);
}

bool BoardState::moveIsQSideCastle(const Move& m) {
	return moveIsQSideCastle(m.from, m.to);
}

bool BoardState::moveIsQSideCastle(const ExtendedMove& m) {
	return moveIsQSideCastle(m.from, m.to) && m.promotionPiece == NOPIECE;
}

bool BoardState::moveCapturesPiece(const ExtendedMove& m, const Piece_t& p) {
	if (turnColor) {
		return blackPieces[Square::getIndex(m.to)] == p;
	} else {
		return whitePieces[Square::getIndex(m.to)] == p;
	}
}

bool BoardState::moveGivesCheck(const ExtendedMove& m) {
	if (m.promotionPiece == NOPIECE) {
		return moveGivesCheck_(m.from,m.to);
	} else if (moveRequiresPromotion(m) && isValidPromotionPiece(m.promotionPiece)) {
		return moveGivesCheck(m.to,m.promotionPiece,turnColor);
	} else {
		return false;
	} 
}

bool BoardState::moveGivesCheck(const Square_t& from, const Square_t& to) {
	if (!moveRequiresPromotion(from,to)) {
		return moveGivesCheck_(from, to);
	} else {
		return false;
	}
}

bool BoardState::moveGivesCheck_(const Square_t& from, const Square_t& to) {
	if (whitePieces[Square::getIndex(from)] != NOPIECE) {
		return moveGivesCheck(to,whitePieces[Square::getIndex(from)],WHITE);
	} else if (blackPieces[Square::getIndex(from)] != NOPIECE) {
		return moveGivesCheck(to,blackPieces[Square::getIndex(from)],BLACK);
	} else {
		return false;
	}
}

bool BoardState::moveGivesCheck(const Square_t& to, const Piece_t& p, const Color_t& c) {
	switch(p) {
		case NOPIECE:
			return false;
		case PAWN:
			if (c) {
				return whitePawnGivesCheck(to);
			} else {
				return blackPawnGivesCheck(to);
			}
		case KNIGHT:
			return knightGivesCheck(to,c);
		case BISHOP:
			return bishopGivesCheck(to,c);
		case ROOK:
			return rookGivesCheck(to,c);
		case QUEEN:
			return queenGivesCheck(to,c);
		case KING:
			return false;
		default: 
			return false;
	}
}

bool BoardState::whitePawnGivesCheck(const Square_t& sq) {
	BoardMask_t vis = Square::ne(sq) | Square::nw(sq);
	return (vis & getKingSquare(BLACK)) != NO_SQUARE;
}

bool BoardState::blackPawnGivesCheck(const Square_t& sq) {
	BoardMask_t vis = Square::se(sq) | Square::sw(sq);
	return (vis & getKingSquare(WHITE)) != NO_SQUARE;
}

bool BoardState::knightGivesCheck(const Square_t& sq, const Color_t& c) {
	BoardMask_t west, east, west2, east2;
	east = Square::e(sq);
	west = Square::w(sq);
	east2 = Square::ee(sq);
	west2 = Square::ww(sq);
	BoardMask_t vis = (Square::nn(east | west)
		| Square::ss(east | west)
		| Square::n(east2 | west2)
		| Square::s(east2 | west2));
	
	return (vis & getKingSquare(!c)) != NO_SQUARE;
}

bool BoardState::directionGivesCheck(const Square_t& to, const Color_t& c, Square_t (*direction)(const Square_t&)) {
	const Square_t kingSquare = getKingSquare(!c);
	BoardMask_t allPieces = whitePiecesMask | blackPiecesMask;
	Square_t target = to;
	while (target != NO_SQUARE) {
		target = direction(target);
		if (target == kingSquare) {
			return true;
		} else if ((target & allPieces) != NO_SQUARE) {
			return false;
		}
	}
	return false;
}

bool BoardState::bishopGivesCheck(const Square_t& sq, const Color_t& c) {
	if(directionGivesCheck(sq, c, &(Square::ne))){ 
		return true;
	}
	if(directionGivesCheck(sq, c, &(Square::se))){ 
		return true;
	}
	if(directionGivesCheck(sq, c, &(Square::sw))){ 
		return true;
	}
	if(directionGivesCheck(sq, c, &(Square::nw))){ 
		return true;
	}
	return false;
}

bool BoardState::rookGivesCheck(const Square_t& sq, const Color_t& c) {
	if (directionGivesCheck(sq, c, &(Square::n))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::e))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::s))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::w))) {
		return true;
	}
	return false;
}

bool BoardState::queenGivesCheck(const Square_t& sq, const Color_t& c) {
	if (directionGivesCheck(sq, c, &(Square::n))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::ne))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::e))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::se))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::s))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::sw))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::w))) {
		return true;
	}
	if (directionGivesCheck(sq, c, &(Square::nw))) {
		return true;
	}
	return false;
}

bool BoardState::moveIsNearPromotion(const Square_t& from, const Square_t& to) {
	return getPieces(turnColor)[Square::getIndex(from)] == PAWN
	&& (
		(turnColor && Square::onSeventhRank(to))
		|| (!turnColor && Square::onSecondRank(to))
	);
}

bool BoardState::moveIsNearPromotion(const ExtendedMove& m) {
	return getPieces(turnColor)[Square::getIndex(m.from)] == PAWN
	&& (
		(turnColor && Square::onSeventhRank(m.to))
		|| (!turnColor && Square::onSecondRank(m.to))
	) 
	&& m.promotionPiece == NOPIECE;
}
}