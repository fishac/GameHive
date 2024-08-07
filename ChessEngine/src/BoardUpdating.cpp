#include "ChessEngine.h"

bool ChessEngine::provideMove(const ExtendedMove& m) {
	return internalState->makeMove(m);
}

bool ChessEngine::provideMoveIdx(const ExtendedMoveIdx& m) {
	return internalState->makeMove(m);
}