#include "PerftEngine.h"
#include <cassert>
#include <iostream>
#include <string>

PerftEngine::PerftEngine() {
}

PerftEngine::~PerftEngine() {
	delete internalState;
}

void PerftEngine::setLogging(bool logSetting) {
	log = logSetting;
}

void PerftEngine::setDivide(bool divideSetting) {
	reportDivide = divideSetting;
}

void PerftEngine::resetPerftStats() {
	numScannedNodes = 0;
	numScannedLeaves = 0;
	numScannedCaptures = 0;
	numScannedEnPassants = 0;
	numScannedCastles = 0;
	numScannedPromotions = 0;
	numScannedChecks = 0;
	numScannedCheckmates = 0;
	perftDivide.clear();
}

void PerftEngine::runPerft(int depthSetting) {
	internalState->setDefaultStartingState();
	if (depthSetting > 0 && !internalState->getCheckmateStatus() && !internalState->getStalemateStatus()) {
		currentDivideMove = "";
		activeDepthSetting = depthSetting;
		resetPerftStats();
		std::vector<ExtendedMove> initialMoves = internalState->getLegalExtendedMoves();
		perft(depthSetting,initialMoves);
	}
}

void PerftEngine::runPerft(int depthSetting, std::string FEN) {
	internalState->setFEN(FEN);
	if (depthSetting > 0 && !internalState->getCheckmateStatus() && !internalState->getStalemateStatus()) {
		currentDivideMove = "";
		activeDepthSetting = depthSetting;
		resetPerftStats();
		std::vector<ExtendedMove> initialMoves = internalState->getLegalExtendedMoves();
		perft(depthSetting,initialMoves);
	}
}

void PerftEngine::perft(int depth, std::vector<ExtendedMove>& moves) {
	numScannedNodes++;
	if (log) {
		std::cout << "Legal moves: " << std::endl;
		ChessCore::Vector::printExtendedMoveVector(moves,internalState->getTurnColor());
	}
	if (moves.empty() || depth == 0) {
		if (depth == 0) {
			numScannedLeaves++;
			if (reportDivide) {
				perftDivide[currentDivideMove]++;
			}
		}
	} else {
		for (auto iter = moves.begin(); iter != moves.end(); ++iter) {
			ExtendedMove move = *iter;
			if (depth == activeDepthSetting && reportDivide) {
				currentDivideMove = getSimpleMoveString(move);
				perftDivide[currentDivideMove] = 0;
			} 
			if (internalState->moveIsCapture(move)) {
				numScannedCaptures++;
			}
			if (internalState->moveIsEnPassant(move)) {
				numScannedEnPassants++;
			}
			if (internalState->moveIsCastle(move)) {
				numScannedCastles++;
			}
			if (internalState->moveRequiresPromotion(move)) {
				numScannedPromotions++;
			}
			if (log) {
				std::string moveString = getSimpleMoveString(move);
				std::cout << "Depth: " << depth << ", About to Move: " << moveString << std::endl;
				std::cout << "isMoveLegal: " << internalState->isMoveLegal(move.from,move.to) << ", isRewound: " << internalState->isRewound() << ", moveRequiresPromotion: " << internalState->moveRequiresPromotion(move.from,move.to) << std::endl;
				std::cout << "getCheckmateStatus: " << internalState->getCheckmateStatus() << std::endl;
				std::cout << "isLegalFromSquare: " << internalState->isLegalFromSquare(move.from) << std::endl;
				std::cout << "Legal moves from square: ";
				Vector::printSquareVector(internalState->getLegalMovesFromSquare(move.from));
				internalState->reportPieceSquares();
				internalState->reportCastleRights();
			}
			internalState->engineMakeLegalMove(move);
			internalState->updateLegality();
			if (internalState->getCheckStatus()) {
				numScannedChecks++;
			}
			if (internalState->getCheckmateStatus()) {
				numScannedCheckmates++;
			}
			if (depth > 1) {
				std::vector<ExtendedMove> nextMoves = internalState->getLegalExtendedMoves();
				perft(depth-1,nextMoves);
			} else {
				std::vector<ExtendedMove> nextMoves;
				perft(depth-1,nextMoves);
			}
			if (log) {
				std::string moveString = getSimpleMoveString(move);
				std::cout << "Depth: " << depth << ", Undoing Move: " << moveString << std::endl;
			}
			internalState->undoMove();
			if (log) {
				//internalState->reportPieceSquares();
			}
		}
	}
}

std::string PerftEngine::getSimpleMoveString(const ExtendedMove& m) {
	std::string ret = Square::getString(m.from) + Square::getString(m.to);
	if (m.promotionPiece != Piece::NOPIECE) {
		ret = ret + "=" + FEN::getFENPieceLabel(m.promotionPiece,internalState->getTurnColor());
	}
	return ret;
}

int PerftEngine::getNumScannedNodes() {
	return numScannedNodes;
}

int PerftEngine::getNumScannedLeaves() {
	return numScannedLeaves;
}

int PerftEngine::getNumScannedCaptures() {
	return numScannedCaptures;
}

int PerftEngine::getNumScannedEnPassants() {
	return numScannedEnPassants;
}

int PerftEngine::getNumScannedCastles() {
	return numScannedCastles;
}

int PerftEngine::getNumScannedPromotions() {
	return numScannedPromotions;
}

int PerftEngine::getNumScannedChecks() {
	return numScannedChecks;
}

int PerftEngine::getNumScannedCheckmates() {
	return numScannedCheckmates;
}

std::unordered_map<std::string,int> PerftEngine::getDivideStats() {
	return perftDivide;
}