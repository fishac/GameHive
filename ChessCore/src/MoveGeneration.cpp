#include "ChessCore.h"

#include <iostream>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {

void BoardState::updateLegality() {
	updateLegalMoves();
	updateCheckStatus();
	updateCheckmateStatus();
	updateStalemateStatus();
}

void BoardState::updateLegalMoves() {
	//std::cout << "Updating legal moves" << std::endl;
	//std::cout << "Updating legal moves" << std::endl;
	//std::cout << "Clearing entries" << std::endl;
	clearVisibility();
	clearXRayVisibility();
	clearLegalMoves();
	clearKingAttackers();
	clearPinningPieces();
	clearPossibleDefendedPieces();
	clearDefendedPiecesMask();
	clearKingPierceSquare();
	//std::cout << "Done clearing entries" << std::endl;

	if (!checkmateStatus && !stalemateStatus) {
		// unused/uncreated yet
		//attackedPiecesMask = 0;
		//defendedPiecesMask = 0;
		
		setPawnVisibilities();
		setNonPawnVisibilities();
		
		//std::cout << "Reduce 1" << std::endl;
		reduceKingVisibilityAttackedSquares();
		//std::cout << "Reduce 2" << std::endl;
		reduceVisibility(!turnColor);
		//std::cout << "Reduce 3" << std::endl;
		reduceVisibility(turnColor);
		//std::cout << "Reduce 4" << std::endl;
		checkForKingAttackers();
		
		//std::cout << "Legal 1" << std::endl;
		setLegalMoves();
	}
}

void BoardState::clearVisibility() {
	for (int i=0; i<64; i++) {
		visibility[i] = NO_SQUARE;
	}
}

void BoardState::clearXRayVisibility() {
	for (int i=0; i<64; i++) {
		xRayVisibility[i] = NO_SQUARE;
	}
}

void BoardState::clearLegalMoves() {
	for (int i=0; i<64; i++) {
		legalMoves[i] = NO_SQUARE;
	}
}

void BoardState::clearKingAttackers() {
	kingAttackers.clear();
}

void BoardState::clearPinningPieces() {
	for (int i=0; i<64; i++) {
		pinningPieces[i] = NO_SQUARE;
	}
}

void BoardState::clearPossibleDefendedPieces() {
	whitePossibleDefendedPiecesMask = EMPTY_BOARD;
	blackPossibleDefendedPiecesMask = EMPTY_BOARD;
	for (int i=0; i<64; i++) {
		possibleDefendedPieces[i] = NO_SQUARE;
	}
}

void BoardState::clearDefendedPiecesMask() {
	whiteDefendedPiecesMask = NO_SQUARE;
	blackDefendedPiecesMask = NO_SQUARE;
}

void BoardState::clearKingPierceSquare() {
	kingPierceSquare = NO_SQUARE;
}

void BoardState::setNonPawnVisibilities() {
	for(int i=0; i<64; i++) {
		const Piece_t& wp = whitePieces[i];
		switch(wp) {
			case KNIGHT:
				setKnightVisibility(WHITE, i);
				break;
			case BISHOP:
				setBishopVisibility(WHITE, i);
				break;
			case ROOK:
				setRookVisibility(WHITE, i);
				break;
			case QUEEN:
				setQueenVisibility(WHITE, i);
				break;
			case KING:
				setKingVisibility(WHITE, i);
				break;
		}
		const Piece_t& bp = blackPieces[i];
		switch(bp) {
			case KNIGHT:
				setKnightVisibility(BLACK, i);
				break;
			case BISHOP:
				setBishopVisibility(BLACK, i);
				break;
			case ROOK:
				setRookVisibility(BLACK, i);
				break;
			case QUEEN:
				setQueenVisibility(BLACK, i);
				break;
			case KING:
				setKingVisibility(BLACK, i);
				break;
		}
	}
}

void BoardState::setPawnVisibilities() {
	for(int i=0; i<64; i++) {
		const Piece_t& wp = whitePieces[i];
		const Piece_t& bp = blackPieces[i];
		if (wp == PAWN) {
			setWhitePawnVisibility(i);
		}
		if (bp == PAWN) {
			setBlackPawnVisibility(i);
		}
	}
}

void BoardState::setWhitePawnVisibility(const int& sq_idx) {
	Square_t sq = Square::getSquare(sq_idx);
	BoardMask_t allPieces = blackPiecesMask | whitePiecesMask;
	// white pawn can go northeast if there is a black piece there or
	// the square can be traveled to via en passant
	// and (implicitly) northeast square is actually on the board
	visibility[sq_idx] = Square::ne(sq)
	// white pawn can go northwest if there is a black piece there or
	// the square can be traveled to via en pessant
	// and (implicitly) northwest square is actually on the board
		| Square::nw(sq)
	// white pawn can move north one square if there is no white piece there
	// and (implicitly) north square is actually on the board
		| ((Square::n(sq) & ~allPieces) * turnColor)
	// white pawn can move north two squares if it is on the second rank (hasn't moved)
	// and there is no white piece one or two squares north
		| (Square::nn(sq) & ~allPieces) * (turnColor && Square::onSecondRank(sq) && ((Square::n(sq) & ~allPieces) != EMPTY_BOARD));
	
	possibleDefendedPieces[sq_idx] = visibility[sq_idx] & whitePiecesMask;
	whitePossibleDefendedPiecesMask |= visibility[sq_idx] & whitePiecesMask;
}

void BoardState::setBlackPawnVisibility(const int& sq_idx) {
	Square_t sq = Square::getSquare(sq_idx);
	BoardMask_t allPieces = blackPiecesMask | whitePiecesMask;
	// black pawn can go southeast if there is a white piece there or
	// the square can be traveled to via en passant
	// and (implicitly) southeast square is actually on the board
	visibility[sq_idx] = Square::se(sq)
	// black pawn can go southwest if there is a white piece there or
	// the square can be traveled to via en pessant
	// and (implicitly) southwest square is actually on the board
		| Square::sw(sq)
	// black pawn can move south one square if there is no black piece there
	// and (implicitly) south square is actually on the board
		| ((Square::s(sq) & ~allPieces) * !turnColor)
	// black pawn can move south two squares if it is on the second rank (hasn't moved)
	// and there is no black piece one or two squares south
		| (Square::ss(sq) & ~allPieces) * (!turnColor && Square::onSeventhRank(sq) && ((Square::s(sq) & ~allPieces) != EMPTY_BOARD));
	
	possibleDefendedPieces[sq_idx] = visibility[sq_idx] & blackPiecesMask;
	blackPossibleDefendedPiecesMask |= visibility[sq_idx] & blackPiecesMask;
}

void BoardState::setKnightVisibility(const Color_t& c, const int& sq_idx) {
	BoardMask_t west, east, west2, east2;
	Square_t sq = Square::getSquare(sq_idx);
	// Compute east and west squares from knight
	east = Square::e(sq);
	west = Square::w(sq);
	// Compute east and west two squares from knight
	east2 = Square::ee(sq);
	west2 = Square::ww(sq);
	// Compute two squares north of east and west, set as legal moves
	visibility[sq_idx] = (Square::nn(east | west)
	// Compute two squares south of east and west, add to legal moves
		| Square::ss(east | west)
	// Compute one square north of the two east and west squares, add to legal moves
		| Square::n(east2 | west2)
	// Compute one square south of the two east and west squares, add to legal moves
		| Square::s(east2 | west2));
	
	possibleDefendedPieces[sq_idx] = visibility[sq_idx] & getPiecesMask(c);
	getPossibleDefendedPiecesMask(c) |= visibility[sq_idx] & getPiecesMask(c);
	
	// Remove squares which contain color c pieces
	visibility[sq_idx] = visibility[sq_idx] & ~getPiecesMask(c);
}

void BoardState::scanDirection(const Color_t& perspectiveColor, const Square_t& from, const bool& scanningEastWest, Square_t (*direction)(const Square_t&)) {
	int from_idx = Square::getIndex(from);
	Square_t defendedPiece = NO_SQUARE;
	Square_t xRayDefendedPiece = NO_SQUARE;
	Square_t attackedPiece = NO_SQUARE;
	bool attackedPieceIsPinned = false;
	BoardMask_t visibilityMask = EMPTY_BOARD;
	BoardMask_t xRayVisibilityMask = EMPTY_BOARD;
	bool checkingPastAttackedPiece = false;
	bool squareContainsOpposingKing = false;
	bool squareContainsFriendlyPiece = false;
	bool squareContainsOpposingPiece = false;
	Square_t target = direction(from);
	// Check one square at a time 
	while (target != NO_SQUARE) {
		// Determine if square contains a same color piece
		squareContainsFriendlyPiece = ((target & getPiecesMask(perspectiveColor)) != NO_SQUARE);
		// Determine if square contains an opposing piece
		squareContainsOpposingPiece = ((target & getPiecesMask(!perspectiveColor)) != NO_SQUARE);
		// Determine if square contains opposing king 
		squareContainsOpposingKing = getKingSquare(!perspectiveColor) == target;
		// Add square to visibility if arent checking for pins
		// and square does not contain a friendly piece.
		visibilityMask |= (target * !(checkingPastAttackedPiece || squareContainsFriendlyPiece));
		// Add square to potential xRayVisibilityMask if have not reached a 
		// friendly piece or the opposing king
		xRayVisibilityMask |= (target * !(squareContainsFriendlyPiece || squareContainsOpposingKing)); 
		// Mark square as defended if havent seen a piece along direction 
		// and square contains a friendly piece.
		defendedPiece |= (target * (!checkingPastAttackedPiece && squareContainsFriendlyPiece));
		xRayDefendedPiece |= (target * (checkingPastAttackedPiece && squareContainsFriendlyPiece));
		// Mark square as having an attacked piece if havent seen piece along direction 
		// and square contains opposing piece.
		attackedPiece |= target * (!checkingPastAttackedPiece && squareContainsOpposingPiece);
		// Mark attacked piece as pinned if checking pas
		attackedPieceIsPinned = checkingPastAttackedPiece && squareContainsOpposingKing;
		// If square contains friendly piece 
		// or if square contains second piece along direction
		// of if square contains the opposing king
		if (
			squareContainsFriendlyPiece 
			|| (squareContainsOpposingPiece && checkingPastAttackedPiece) 
			|| squareContainsOpposingKing
		) {
			// Stop checking along direction
			break;
		}
		// Set flag to indicate we are continuing past an attacked piece
		// to check or pins if we have marked an attacked piece
		checkingPastAttackedPiece = (attackedPiece != NO_SQUARE);
		// Move target one square along direction
		target = direction(target);
	}
	if (defendedPiece != NO_SQUARE) {
		possibleDefendedPieces[from_idx] |= defendedPiece;
		getPossibleDefendedPiecesMask(perspectiveColor) |= defendedPiece;
	}
	if (squareContainsOpposingKing && defendedPiece == NO_SQUARE && !checkingPastAttackedPiece) {
		kingPierceSquare |= direction(target);
	}
	// if scanning east/west and en passant is an option and perspectiveColor is the one preventing en passant (is not turnColor)
	if (
		target != NO_SQUARE 
		&& scanningEastWest 
		&& enPassantableSquare != NO_SQUARE 
		&& perspectiveColor != turnColor 
		&& (
			(
				defendedPiece != NO_SQUARE
				&& ((
					turnColor
					&& (Square::n(defendedPiece) == enPassantableSquare)
				) || (
					!turnColor 
					&& (Square::s(defendedPiece) == enPassantableSquare)
				))
			) || (
				attackedPiece != NO_SQUARE 
				&& xRayDefendedPiece != NO_SQUARE
				&& ((
					turnColor
					&& (Square::n(xRayDefendedPiece) == enPassantableSquare)
				) || (
					!turnColor 
					&& (Square::s(xRayDefendedPiece) == enPassantableSquare)
				))
			)
		)
	) {		
		BoardMask_t opponentPawns = getPieceMask(!perspectiveColor,PAWN);
		
		BoardMask_t allPieces = whitePiecesMask | blackPiecesMask;
		Square_t trickyAttackedPawn = NO_SQUARE;
		
		// Determine if en passantable pawn and en passanting pawn next to each other
		if (defendedPiece != NO_SQUARE) {
			target = direction(target);
			if ((target & opponentPawns) != NO_SQUARE) {
				trickyAttackedPawn = target;
			} 
		} else if ((attackedPiece & opponentPawns) != NO_SQUARE && direction(attackedPiece) == xRayDefendedPiece) {
			trickyAttackedPawn = attackedPiece;
		}
		
		// If tricky pawns next to each other, look for king in danger along rank
		if (trickyAttackedPawn != NO_SQUARE) {
			while (target != NO_SQUARE) {
				target = direction(target);
				if (target == getKingSquare(!perspectiveColor)) {
					//Found king, tricky situation!
					int trickyAttackedPawn_idx = Square::getIndex(trickyAttackedPawn);
					visibility[trickyAttackedPawn_idx] &= ~enPassantableSquare;
				} else if ((target & allPieces) != EMPTY_BOARD) {
					// Found any other piece, not tricky situation
					break;
				}
			}
		}
	}
	// Add the calculated visible squares to the square's running mask
	visibility[from_idx] |= visibilityMask;
	if (attackedPieceIsPinned) {
	// If pinning a piece to the king
		// Store the pinning piece's square.
		// No need to worry about overwrite, pieces can only be pinned by 1 other piece
		// Retain if statement to save memory
		int attackedPiece_idx = Square::getIndex(attackedPiece);
		pinningPieces[attackedPiece_idx] = from;
	} 
	if (squareContainsOpposingKing) {
	// If found king along direction, even through (up to) one opposing piece
		// Store the whole ray of squares between from square and king 
		// as an xRayVisibility
		// Retain if statement to save memory
		xRayVisibility[from_idx] = xRayVisibilityMask;
	}
	
	// TODO : store defendedPiece somehow
	// TODO : store attackedPiece somehow
}

void BoardState::setBishopVisibility(const Color_t& c, const int& sq_idx) {
	Square_t sq = Square::getSquare(sq_idx);
	// Set up visibility for the square
	visibility[sq_idx] = EMPTY_BOARD;
	// Scan along each attacking direction
	scanDirection(c, sq, false, &(Square::ne));
	scanDirection(c, sq, false, &(Square::se));
	scanDirection(c, sq, false, &(Square::sw));
	scanDirection(c, sq, false, &(Square::nw));
}

void BoardState::setRookVisibility(const Color_t& c, const int& sq_idx) {
	Square_t sq = Square::getSquare(sq_idx);
	// Set up visibility for the square
	visibility[sq_idx] = EMPTY_BOARD;
	// Scan along each attacking direction
	scanDirection(c, sq, false, &(Square::n));
	scanDirection(c, sq, true, &(Square::e));
	scanDirection(c, sq, false, &(Square::s));
	scanDirection(c, sq, true, &(Square::w));
}

void BoardState::setQueenVisibility(const Color_t& c, const int& sq_idx) {
	Square_t sq = Square::getSquare(sq_idx);
	// Set up visibility for the square
	visibility[sq_idx] = EMPTY_BOARD;
	// Scan along each attacking direction
	scanDirection(c, sq, false, &(Square::n));
	scanDirection(c, sq, false, &(Square::ne));
	scanDirection(c, sq, true, &(Square::e));
	scanDirection(c, sq, false, &(Square::se));
	scanDirection(c, sq, false, &(Square::s));
	scanDirection(c, sq, false, &(Square::sw));
	scanDirection(c, sq, true, &(Square::w));
	scanDirection(c, sq, false, &(Square::nw));
}

void BoardState::setKingVisibility(const Color_t& c, const int& sq_idx) {
	// Using some time-saving tricks over computing all 8 directions separately.
	// Compute north and south attacked squares, save for later
	//Square_t sq = pieceSquares[c][KING].at(0);
	Square_t sq = Square::getSquare(sq_idx);
	BoardMask_t northsouth = Square::n(sq) | Square::s(sq);
	// Add north and south squares of king to visibility
	visibility[sq_idx] = (northsouth 
	// Compute east and west of the north and south squares (4 corners), add to visibility
		| Square::e(northsouth) 
		| Square::w(northsouth)
	// Compute east and west squares of king, add to visibility
		| Square::e(sq) 
		| Square::w(sq)
	// Add possible castle target squares to visibility
		| (Square::ee(sq)*(turnColor == c && kSideCastleRights[c] && (sq == Square::getDefaultStartingKingSquare(c))))
		| (Square::ww(sq)*(turnColor == c && qSideCastleRights[c] && (sq == Square::getDefaultStartingKingSquare(c)))))
	// Remove squares which contain friendly pieces
		& ~getPiecesMask(c);
}

void BoardState::reduceKingVisibilityAttackedSquares() {
	BoardMask_t opponentVisibilityMask = getVisibilityMask(!turnColor);
	BoardMask_t opponentDefendedPiecesMask = getPossibleDefendedPiecesMask(!turnColor);
	BoardMask_t allPieces = whitePiecesMask | blackPiecesMask;
	Square_t kingSquare = getKingSquare(turnColor);
	int kingSquare_idx = Square::getIndex(kingSquare);
	visibility[kingSquare_idx] = (visibility[kingSquare_idx] & ~(opponentVisibilityMask | kingPierceSquare | opponentDefendedPiecesMask));
	if (// No castle rights
		!kSideCastleRights[turnColor] 
		// Cant castle if in check
		|| !((opponentVisibilityMask & kingSquare) == EMPTY_BOARD)
		// Cant castle if blocked by own or opponent pieces, or into/across check
		|| !((Square::eCastleCrossingSquares(turnColor) & opponentVisibilityMask) == EMPTY_BOARD)
		|| !((Square::eCastleBetweenSquares(turnColor) & allPieces) == EMPTY_BOARD)
	) {
		visibility[kingSquare_idx] = (visibility[kingSquare_idx] & ~Square::ee(kingSquare));
	}
	if (// No castle rights
		!qSideCastleRights[turnColor] 
		// Cant castle if in check
		|| !((opponentVisibilityMask & kingSquare) == EMPTY_BOARD)
		// Cant castle if blocked by own or opponent pieces, or into/across check
		|| !((Square::wCastleCrossingSquares(turnColor) & opponentVisibilityMask) == EMPTY_BOARD)
		|| !((Square::wCastleBetweenSquares(turnColor) & allPieces) == EMPTY_BOARD)
	) {
		visibility[kingSquare_idx] = (visibility[kingSquare_idx] & ~Square::ww(kingSquare));
	}
}

void BoardState::reduceVisibility(const Color_t& c) {
	std::array<Piece_t,64>& pieces = getPieces(c);
	for (int i=0; i<64; i++) {
		if (pieces[i] != NOPIECE && pieces[i] != KING) {
			reduceVisibilityFromSquare(c, i);
		}
	}
}

void BoardState::reduceVisibilityFromSquare(const Color_t& c, const int& sq_idx) {
	Square_t sq = Square::getSquare(sq_idx);
	bool pieceIsPinned = pinningPieces[sq_idx] != NO_SQUARE;
	BoardMask_t& opposingPiecesMask = getPiecesMask(!c);
	Square_t& opposingKingSq = getKingSquare(!c);
	Square_t& friendlyKingSq = getKingSquare(c);
	bool opposingKingIsVisible = (visibility[sq_idx] & opposingKingSq) != NO_SQUARE;
	if ((visibility[sq_idx] & opposingKingSq) != NO_SQUARE) {
		kingAttackers.push_back(sq);
	} 
	if (getPieces(c)[sq_idx] == PAWN && turnColor == c) {
	// If piece is a pawn
		Square_t nswsq = NO_SQUARE;
		Square_t nsesq = NO_SQUARE;
		// Determine pawn attacking squares
		if (c) {
			nswsq = Square::nw(sq);
			nsesq = Square::ne(sq);
		} else {
			nswsq = Square::sw(sq);
			nsesq = Square::se(sq);
		}
		// Reduce their visibility if not attacking an opponent
		// And sq still in visibility.
		if (
			(nswsq & (opposingPiecesMask | enPassantableSquare)) == NO_SQUARE 
			&& (nswsq & visibility[sq_idx]) != NO_SQUARE
		) {
			visibility[sq_idx] = visibility[sq_idx] & ~nswsq;
		}
		if (
			(nsesq & (opposingPiecesMask | enPassantableSquare)) == NO_SQUARE 
			&& (nsesq & visibility[sq_idx]) != NO_SQUARE
		) {
			visibility[sq_idx] = visibility[sq_idx] & ~nsesq;
		}
	}
	if (pieceIsPinned) {
	// If this piece is pinned but opposing king is not visible
		// Get the square containing the pinning piece 
		Square_t pinningPiece = pinningPieces[sq_idx];
		int pinningPiece_idx = Square::getIndex(pinningPiece);
		// Reduce the visibility of the pinned piece to only include 
		// moves along the direction of the pin
		visibility[sq_idx] = visibility[sq_idx] & ((pinningPiece | xRayVisibility[pinningPiece_idx]) | opposingKingSq);
	} 
	if (!pieceIsPinned) {
		getDefendedPiecesMask(c) |= possibleDefendedPieces[sq_idx];
	}
}

void BoardState::checkForKingAttackers() {
	Square_t friendlyKingSq = getKingSquare(turnColor);
	if (kingAttackers.size() == 1) {
	// If one piece attacking the king 
		Square_t kingAttacker = kingAttackers.at(0);
		// Non-king pieces can only try to block the check or take the attacker.
		std::array<Piece_t,64>& pieces = getPieces(turnColor);
		for(int i=0; i<64; i++) {
			const Piece_t& p = pieces[i];
			if (p != NOPIECE && p != KING) {
				reduceVisibilityStopCheck(i, kingAttacker);
			}
		}
	} else if (kingAttackers.size() > 1) {
	// If multiple pieces attacking the king
		// Only king can move
		std::array<Piece_t,64>& pieces = getPieces(turnColor);
		for(int i=0; i<64; i++) {
			const Piece_t& p = pieces[i];
			if (p != NOPIECE && p != KING) {
				visibility[i] = EMPTY_BOARD;
			}
		}
	}
}

void BoardState::reduceVisibilityStopCheck(const int& sq_idx, const Square_t& kingAttacker) {
	int kingAttacker_idx = Square::getIndex(kingAttacker);
	visibility[sq_idx] = visibility[sq_idx] & (xRayVisibility[kingAttacker_idx] | kingAttacker);
}

void BoardState::setLegalMoves() {
	std::array<Piece_t,64>& pieces = getPieces(turnColor);
	for (int i=0; i<64; i++) {
		if (pieces[i] != NOPIECE) {
			legalMoves[i] = visibility[i];
		}
	}
}

bool BoardState::isPiecePinned(const Square_t& sq) {
	int sq_idx = Square::getIndex(sq);
	return pinningPieces[sq_idx] != NO_SQUARE;
}

std::vector<Move> BoardState::getLegalMoves() {
	if (!isRewound()) {
		std::vector<Move> moves;
		moves.reserve(50);
		std::array<Piece_t,64>& pieces = getPieces(turnColor);
		for (int i=0; i<64; i++) {
			if (pieces[i] != NOPIECE) {
				appendLegalMoves(i,moves);
			}
		}
		return moves;
	} else {
		std::vector<Move> moves;
		return moves;
	}
}

void BoardState::appendLegalMoves(const int& from_idx, std::vector<Move>& moves) {
	Square_t from = Square::getSquare(from_idx);
	std::vector<Square_t> toSquares = Square::getSquares(legalMoves[from_idx]);
	for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
		moves.push_back({from,*iter});
	}
}

std::vector<Square_t> BoardState::getLegalMovesFromSquare(const Square_t& s) {
	if (isLegalFromSquare(s) && !isRewound()) {
		int sq_idx = Square::getIndex(s);
		return Square::getSquares(legalMoves[sq_idx]);
	} else {
		std::vector<Square_t> ret;
		return ret;
	}
}

std::vector<ExtendedMove> BoardState::getLegalExtendedMoves() {
	std::vector<ExtendedMove> moves;
	moves.reserve(50);
	if (!isRewound()) {
		std::array<Piece_t,64>& pieces = getPieces(turnColor);
		for (int i=0; i<64; i++) {
			if (pieces[i] != NOPIECE) {
				appendLegalExtendedMoves(i,moves);
			}
		}
		return moves;
	} else {
		return moves;
	}
	
	return moves;
}

void BoardState::appendLegalExtendedMoves(const int& from_idx, std::vector<ExtendedMove>& moves) {
	std::vector<Square_t> toSquares = Square::getSquares(legalMoves[from_idx]);
	Square_t from = Square::getSquare(from_idx);
	// If square has pawn
	if (getPieces(turnColor)[from_idx] == PAWN
		&& ( // and is about to promote
			(turnColor && Square::onSeventhRank(from))
			|| (!turnColor && Square::onSecondRank(from))
		)
	) {
		// Add the different promotion options to its possible moves
		for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
			moves.push_back({from,*iter,QUEEN});
			moves.push_back({from,*iter,KNIGHT});
			moves.push_back({from,*iter,BISHOP});
			moves.push_back({from,*iter,ROOK});
		}
	} else {
		// Otherwise just proceed as normal
		for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
			moves.push_back({from,*iter,NOPIECE});
		}
	}
}

BoardMask_t BoardState::getVisibilityMask(const Color_t& c) {
	BoardMask_t visibilityMask = NO_SQUARE;
	std::array<Piece_t,64>& pieces = getPieces(c);
	for (int i=0; i<64; i++) {
		if (pieces[i] != NOPIECE) {
			visibilityMask |= visibility[i];
		}
	}
	return visibilityMask;
}

BoardMask_t BoardState::getLegalMovesMask() {
	BoardMask_t legalMovesMask = NO_SQUARE;
	std::array<Piece_t,64>& pieces = getPieces(turnColor);
	for (int i=0; i<64; i++) {
		if (pieces[i] != NOPIECE) {
			legalMovesMask |= legalMoves[i];
		}
	}
	return legalMovesMask;
}

Square_t BoardState::getPinningPiece(const Square_t& sq) {
	int sq_idx = Square::getIndex(sq);
	return pinningPieces[sq_idx];
}
}