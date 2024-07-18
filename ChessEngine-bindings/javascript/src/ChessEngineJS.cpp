#include "ChessCore.h"
#include "ChessEngine.h"
#include <emscripten/bind.h>

using namespace ChessCore;
using namespace emscripten;

EMSCRIPTEN_BINDINGS(ChessEngineJS) {
	value_object<ExtendedMoveIdx>("Move")
		.field("from",&ExtendedMoveIdx::fromIdx)
		.field("to",&ExtendedMoveIdx::toIdx)
		.field("promotionPiece",&ExtendedMoveIdx::promotionPiece);
	function("getMoveString",select_overload<std::string(ExtendedMoveIdx&)>(&MoveUtils::getString));
	class_<BoardState>("BoardState")
		.constructor<const bool&>()
		.function("setFEN", &BoardState::setFEN)
		.function("isLegalFromSquare", &BoardState::isLegalFromSquare)
		.function("getLegalMoves", &BoardState::getLegalExtendedMoveIdxs)
		.function("getLegalMovesFromSquare", &BoardState::getLegalMovesFromSquareIdx)
		.function("makeMove", select_overload<bool(const ExtendedMoveIdx&)>(&BoardState::makeMove))
		.function("isMoveLegal", select_overload<bool(const ExtendedMoveIdx&)>(&BoardState::isMoveLegal))
		.function("getCheckStatus", &BoardState::getCheckStatus)
		.function("getCheckmateStatus", &BoardState::getCheckmateStatus)
		.function("getStalemateStatus", &BoardState::getStalemateStatus)
		.function("isDrawByRepitition", &BoardState::isDrawByRepitition)
		.function("isDrawByInsufficientMaterial", &BoardState::isDrawByInsufficientMaterial)
		.function("getTurnColor", &BoardState::getTurnColor)
		.function("getWhiteKingSquare", &BoardState::getWhiteKingSquare)
		.function("getBlackKingSquare", &BoardState::getBlackKingSquare)
		.function("getPieceOnSquareIdx", &BoardState::getPieceOnSquareIdx)
		.function("getColorOnSquareIdx", &BoardState::getColorOnSquareIdx)
		.function("isSquareOccupied", &BoardState::isSquareIdxOccupied)
		;
	class_<ChessEngine>("ChessEngine")
		.constructor<>()
		.function("suggestMove", &ChessEngine::suggestMove)
		.function("provideMove", &ChessEngine::provideMove)
		.function("setFEN", &ChessEngine::setFEN)
		.function("getMoveSearchDepth", &ChessEngine::getMoveSearchDepth)
		.function("getMoveSearchTime", &ChessEngine::getMoveSearchTime)
		.function("getMoveSearchTimeLimit", &ChessEngine::getMoveSearchTimeLimit)
		.function("searchWasHardTimeCutoff", &ChessEngine::searchWasHardTimeCutoff)
		.function("getNumScannedNodes", &ChessEngine::getNumScannedNodes);
		;
}
