#include "WeightEvaluationEngine.h"

WeightEvaluationEngine::WeightEvaluationEngine() {
	internalState = new BoardState();
}

WeightEvaluationEngine::~WeightEvaluationEngine() {
	delete internalState;
}

void WeightEvaluationEngine::setBaseWeights(std::array<int,7> baseWeights_) {
	baseWeights = baseWeights_;
}

void WeightEvaluationEngine::setEarlygameWeights(std::array<std::array<int,64>,7> earlygameWeights_) {
	earlygameWeights = earlygameWeights_;
}

void WeightEvaluationEngine::setEndgameWeights(std::array<std::array<int,64>,7> endgameWeights_) {
	endgameWeights = endgameWeights_;
}

void WeightEvaluationEngine::setFEN(std::string FEN) {
	internalState->setFEN(FEN);
}

int WeightEvaluationEngine::evaluatePosition() {
	if (internalState->getCheckmateStatus()) {
		return 100000;
	} else if (internalState->getStalemateStatus()) {
		return 0;
	}
	const std::array<Piece_t,64>& whitePieces = internalState->getWhitePieces();
	const std::array<Piece_t,64>& blackPieces = internalState->getBlackPieces();
	int whitePiecePoints = 0;
	int blackPiecePoints = 0;
	int currentPhase = getCurrentPhase();
	Piece_t wp = ChessCore::Piece::NOPIECE;
	Piece_t bp = ChessCore::Piece::NOPIECE;
	for(int i=0; i<64; i++) {
		wp = whitePieces[i];
		bp = blackPieces[i];
		whitePiecePoints += baseWeights[wp] + (
			earlygameWeights[wp][64]*std::max(maxPhase-currentPhase,0) 
			+ endgameWeights[wp][64]*std::min(currentPhase,maxPhase)
		) / maxPhase;
		blackPiecePoints += baseWeights[bp] + (
			earlygameWeights[bp][64-i]*std::max(maxPhase-currentPhase,0)
			+ endgameWeights[bp][64-i]*std::min(currentPhase,maxPhase)
		) / maxPhase;
	}

	int turnColorMultiplier = internalState->getTurnColor() ? 1 : -1;
	
	return turnColorMultiplier*(whitePiecePoints - blackPiecePoints);
}

int WeightEvaluationEngine::getCurrentPhase() {
	return (
		pawnPhaseContribution*(internalState->getNumWhitePawns() + internalState->getNumBlackPawns())
		+ knightPhaseContribution*(internalState->getNumWhiteKnights() + internalState->getNumBlackKnights())
		+ bishopPhaseContribution*(internalState->getNumWhiteBishops() + internalState->getNumBlackBishops())
		+ rookPhaseContribution*(internalState->getNumWhiteRooks() + internalState->getNumBlackRooks())
		+ queenPhaseContribution*(internalState->getNumWhiteQueens() + internalState->getNumBlackQueens())
	);
}