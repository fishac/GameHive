#include "ChessCore.h"

#include <iostream>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
bool BoardState::undoMove() {
	// If there is a history
	if (!moveHistory.empty()) {
		//std::cout << "Undoing move" << std::endl;
		// Undoing any move which may have just led to check, checkmate, or stalemate
		// This helps the updateLegalMovesFunction know its not an ended game
		// before the updateLegality updates these to the correct values.
		checkStatus = false;
		checkmateStatus = false;
		stalemateStatus = false;
		// Flip turn color back to other player
		toggleTurnColor();
		if (!turnColor) {
		// If turn is now black
			// Undo the recent full move increment.
			moveNumber--;
		}
		// Grab move record from end
		MoveRecord mr = moveHistory.back();
		
		/*
		std::cout << "Move Record to undo: " 
			<< "from: " << Square::getString(mr.from)
			<< ", to: " << Square::getString(mr.to)
			<< ", movingPiece: " << (int) mr.movingPiece
			<< ", capturedPiece: " << (int) mr.capturedPiece
			<< ", promotionPiece: " << (int) mr.promotionPiece
			<< ", capturedPieceSquare: " << Square::getString(mr.capturedPieceSquare)
			<< ", priorEnPassantableSquare: " << Square::getString(mr.priorEnPassantableSquare)
			<< ", priorHalfmoveClock: " << mr.priorHalfmoveClock
			<< ", whiteLostKSideCastleRights: " << mr.whiteLostKSideCastleRights
			<< ", whiteLostQSideCastleRights: " << mr.whiteLostQSideCastleRights
			<< ", blackLostKSideCastleRights: " << mr.blackLostKSideCastleRights
			<< ", blackLostQSideCastleRights: " << mr.blackLostQSideCastleRights
			<< ", moveWasKSideCastle: " << mr.moveWasKSideCastle
			<< ", moveWasQSideCastle: " << mr.moveWasQSideCastle
			<< std::endl;
		*/
		
		setEnPassantableSquare(mr.priorEnPassantableSquare);
		// Set half move clock to what it was before last
		halfmoveClock = mr.priorHalfmoveClock;
		
		if (!mr.moveWasNullMove) {
		// If the move was not a null move, restore pieces
			// Restore castle rights to what they were before last move
			if (mr.lostKSideCastleRights[WHITE]) {
				restoreKSideCastleRights(WHITE);
			} 
			if (mr.lostQSideCastleRights[WHITE]) {
				restoreQSideCastleRights(WHITE);
			} 
			if (mr.lostKSideCastleRights[BLACK]) {
				restoreKSideCastleRights(BLACK);
			} 
			if (mr.lostQSideCastleRights[BLACK]) {
				restoreQSideCastleRights(BLACK);
			} 
			// Add origin square to piece square list
			addPiece(turnColor, mr.from, mr.movingPiece);
			removePiece(turnColor, mr.to);
			
			if (mr.capturedPiece != NOPIECE) {
			// If a piece was captured
				// Add it back to the list of squares of that piece
				addPiece(!turnColor, mr.capturedPieceSquare, mr.capturedPiece);
			} 
			if (mr.moveWasKSideCastle) {
			// If the last move was a kingside castle
				// King already moved back, reset the rook to h file as well
				movePieceForce(Square::hRookCastleTarget(turnColor), Square::hRookStartingSquare(turnColor), ROOK);
			} else if (mr.moveWasQSideCastle) {
			// Else if the last move was a queenside castle
				// King already moved back, reset the rook to a file as well
				movePieceForce(Square::aRookCastleTarget(turnColor), Square::aRookStartingSquare(turnColor), ROOK);
			}
		}

		activePly--;
		totalPlies--;
		// Remove move record from history.
		moveHistory.pop_back();
		if (!boardStateHistory.empty()) {
			boardStateHistory.pop_back();
		}
		
		//std::cout << "Finished undoing move. Piece squares:" << std::endl;
		//reportPieceSquares();
		
		return true;
	} else {
		return false;
	}
}

void BoardState::restoreKSideCastleRights(const Color_t& c) {
	kSideCastleRights[c] = true;
	zobristBoardHash ^= Zobrist::zobristKSideCastleHashes[c];
}

void BoardState::restoreQSideCastleRights(const Color_t& c) {
	qSideCastleRights[c] = true;
	zobristBoardHash ^= Zobrist::zobristQSideCastleHashes[c];
}

bool BoardState::isRewound() {
	return activePly != totalPlies;
}

void BoardState::rewindToStart() {
	if (activePly > 0) {
		setViewingPly(0);
	}
}

void BoardState::rewindOneMove() {
	if (activePly > 0) {
		setViewingPly(activePly-1);
	}
}

void BoardState::fastForwardOneMove() {
	if (activePly < totalPlies) {
		setViewingPly(activePly+1);
	}
}

void BoardState::setViewingPly(const int& plyNumber) {
	if (plyNumber != activePly) {
		if (plyNumber >= 0 && plyNumber <= totalPlies) {
			activePly = plyNumber;
		} else if (plyNumber < 0) {
			activePly = 0;
		} else if (plyNumber > totalPlies) {
			activePly = totalPlies;
		}
		BoardStateRecord bsr = boardStateHistory.at(activePly);
		whitePieces = bsr.whitePieces;
		blackPieces = bsr.blackPieces;
		kSideCastleRights = bsr.kSideCastleRights;
		qSideCastleRights = bsr.qSideCastleRights;
		enPassantableSquare = bsr.enPassantableSquare;
		if (turnColor != bsr.turnColor) {
			toggleTurnColor();
		}
		
		updateLegality();
		clearLegalMoves();
	}
}

void BoardState::fastForwardToPresent() {
	setViewingPly(totalPlies);
}
}