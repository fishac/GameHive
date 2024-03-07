#include "ChessEngine.h"

bool ChessEngine::provideMove(const ExtendedMove& m) {
	return internalState->makeMove(m);
}

