#include "ChessEngine.h"

bool ChessEngine::provideMove(const ExtendedMove& m) {
	return internalState->makeMove(m);
}

bool ChessEngine::provideMove(const Square_t& from, const Square_t& to, const Piece_t& promotionPiece) {
	return internalState->makeMoveAndPromote(from, to, promotionPiece);
}

