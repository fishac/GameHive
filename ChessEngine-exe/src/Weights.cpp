#include "Weights.h"

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
	
const int passedPawnScore = 50;
const int isolatedPawnPenalty = 50;
const int doubledPawnPenalty = 50;

const int kingDistanceToEdgePenalty = -30;

const std::array<int,20> kingSafetyPenalties = {{
	0, 0, 1, 1, 2, 5, 10, 17, 27, 40, 
	52, 65, 75, 84, 92, 100, 107, 112, 115, 117
}};

const std::array<int,20> mobilityScores = {{
	0, 0, 1, 1, 2, 4, 7, 10, 16, 22, 
	28, 35, 45, 55, 63, 70, 75, 78, 81, 82
}};

const std::array<int,7> baseScoresTable = {{0, 100, 300, 310, 500, 900, 0}};

const std::array<std::array<int,64>,7> earlygamePieceTables = {{
	{ // NOPIECE
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // PAWN
		0, 0, 0, 0, 0, 0, 0, 0, 
		10, 10, 10, -10, -10, 10, 10, 10, 
		-10, -10, -10, 20, 20, -10, -10, -10, 
		0, 0, 0, 30, 30, 0, 0, 0, 
		0, 0, 0, 40, 40, 0, 0, 0, 
		0, 0, 0, 50, 50, 0, 0, 0, 
		0, 0, 0, 75, 75, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // KNIGHT
		-75, -50, -25, -25, -25, -25, -50, -75, 
		-50, 10, 10, 10, 10, 10, 10, -50,
		-25, 10, 25, 25, 25, 25, 10, -25,
		-25, 10, 25, 50, 50, 25, 10, -25,
		-25, 10, 25, 50, 50, 25, 10, -25,
		-25, 10, 25, 25, 25, 25, 10, -25,
		-50, 10, 10, 10, 10, 10, 10, -50,
		-75, -50, -25, -25, -25, -25, -50, -75
	},
	{ // BISHOP
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 30, 30, 30, 30, 30, 30, 0, 
		0, 20, 20, 30, 30, 20, 20, 0, 
		0, 20, 20, 30, 30, 20, 20, 0, 
		0, 20, 20, 20, 20, 20, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // ROOK
		10, 10, 20, 30, 30, 20, 10, 10, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // QUEEN
		10, 10, 20, 20, 20, 20, 10, 10, 
		10, 10, 10, 10, 10, 10, 10, 10, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // KING
		75, 90, 40, 10, 10, 40, 90, 75, 
		-20, -20, -20, -20, -20, -20, -20, -20, 
		-30, -30, -40, -40, -40, -40, -30, -30, 
		-40, -40, -50, -60, -60, -50, -40, -40, 
		-40, -40, -50, -60, -60, -50, -40, -40, 
		-40, -40, -50, -50, -50, -50, -40, -40, 
		-40, -40, -50, -50, -50, -50, -40, -40, 
		-40, -40, -50, -50, -50, -50, -40, -40
	}
}};

const std::array<std::array<int,64>,7> endgamePieceTables = {{
	{ // NOPIECE
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // PAWN
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		10, 10, 10, 10, 10, 10, 10, 10, 
		30, 30, 30, 30, 30, 30, 30, 30, 
		40, 40, 40, 40, 40, 40, 40, 40, 
		50, 50, 50, 50, 50, 50, 50, 50, 
		75, 75, 75, 75, 75, 75, 75, 75, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // KNIGHT
		-75, -50, -25, -25, -25, -25, -50, -75, 
		-50, 10, 10, 10, 10, 10, 10, -50,
		-25, 10, 25, 25, 25, 25, 10, -25,
		-25, 10, 25, 50, 50, 25, 10, -25,
		-25, 10, 25, 50, 50, 25, 10, -25,
		-25, 10, 25, 25, 25, 25, 10, -25,
		-50, 10, 10, 10, 10, 10, 10, -50,
		-75, -50, -25, -25, -25, -25, -50, -75
	},
	{ // BISHOP
		0, -10, -10, -10, -10, -10, -10, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 30, 30, 30, 30, 30, 30, 0, 
		0, 20, 20, 30, 30, 20, 20, 0, 
		0, 20, 20, 30, 30, 20, 20, 0, 
		0, 20, 20, 20, 20, 20, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0
	},
	{ // ROOK
		0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 
		10, 10, 10, 10, 10, 10, 10, 10, 
		20, 20, 20, 20, 20, 20, 20, 20,
		20, 20, 20, 20, 20, 20, 20, 20,
		30, 30, 30, 30, 30, 30, 30, 30, 
		50, 50, 50, 50, 50, 50, 50, 50, 
		10, 10, 10, 10, 10, 10, 10, 10
	},
	{ // QUEEN
		0, 0, 0, 0, 0, 0, 0, 0, 
		20, 20, 20, 20, 20, 20, 20, 20, 
		30, 30, 40, 40, 40, 40, 30, 30, 
		40, 40, 60, 75, 75, 60, 40, 40, 
		40, 40, 60, 75, 75, 60, 40, 40, 
		40, 40, 60, 60, 60, 60, 40, 40, 
		40, 40, 50, 50, 50, 50, 40, 40, 
		40, 40, 50, 50, 50, 50, 40, 40
	},
	{ // KING
		0, 0, 0, 0, 0, 0, 0, 0, 
		10, 10, 10, 10, 10, 10, 10, 10, 
		10, 30, 50, 50, 50, 50, 30, 10, 
		10, 30, 50, 60, 60, 50, 30, 10, 
		10, 30, 50, 60, 60, 50, 30, 10, 
		10, 30, 50, 50, 50, 50, 30, 10, 
		10, 30, 30, 30, 30, 30, 30, 10, 
		10, 10, 10, 10, 10, 10, 10, 10
	}
}};