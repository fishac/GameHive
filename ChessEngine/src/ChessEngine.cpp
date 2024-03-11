#include "ChessEngine.h"
#include <limits>

ChessEngine::ChessEngine() {
	internalState = new EngineBoardState(false);
	tTable = new TranspositionTable();
}

ExtendedMove ChessEngine::nullMove() {
	ExtendedMove m = { NO_SQUARE, NO_SQUARE, NOPIECE };
	return m;
}

void ChessEngine::setMaxDepth(int depth) {
	maxDepth = depth;
}

void ChessEngine::setMinDepth(int depth) {
	minDepth = depth;
}

int ChessEngine::getMaxDepth() {
	return maxDepth;
}

int ChessEngine::getMinDepth() {
	return minDepth;
}

int ChessEngine::getMoveSearchDepth() {
	return moveSearchDepth;
}

int ChessEngine::getMoveSearchTime() {
	return moveSearchTime;
}

bool ChessEngine::searchWasHardTimeCutoff() {
	return hardTimeCutoff;
}

int ChessEngine::getMoveSearchTimeLimit() {
	return searchTimeLimit;
}

void ChessEngine::setFEN(std::string FEN) {
	internalState->setFEN(FEN);
}

std::string ChessEngine::getFEN() {
	return internalState->toFEN();
}

int ChessEngine::getNumScannedNodes() {
	return numScannedNodes;
}

int ChessEngine::getEvaluation() {
	return evaluation;
}

void ChessEngine::reportTTStats() {
	tTable->reportStats();
}

ChessEngine::~ChessEngine() {
	delete internalState;
}