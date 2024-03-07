#ifndef WEIGHTEVALUATIONENGINE_H
#define WEIGHTEVALUATIONENGINE_H

#include "ChessCore.h"

using namespace ChessCore;

class WeightEvaluationEngine {
public:
	WeightEvaluationEngine();
	~WeightEvaluationEngine();
	void setBaseWeights(std::array<int,7> baseWeights_);
	void setEarlygameWeights(std::array<std::array<int,64>,7> earlygameWeights_);
	void setEndgameWeights(std::array<std::array<int,64>,7> endgameWeights_);
	void setFEN(std::string FEN);
	int evaluatePosition();
private:
	ChessCore::BoardState* internalState;
	int getCurrentPhase();
	std::array<int,7> baseWeights;
	std::array<std::array<int,64>,7> earlygameWeights;
	std::array<std::array<int,64>,7> endgameWeights;
	const int pawnPhaseContribution = 0;
	const int knightPhaseContribution = 1;
	const int bishopPhaseContribution = 1;
	const int rookPhaseContribution = 2;
	const int queenPhaseContribution = 4;
	const int maxPhase = pawnPhaseContribution*16 
		+ knightPhaseContribution*4
		+ bishopPhaseContribution*4
		+ rookPhaseContribution*4
		+ queenPhaseContribution*2;
};

#endif // PERFTENGINE_H 