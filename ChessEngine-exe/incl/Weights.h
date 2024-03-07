#ifndef WEIGHTS_H
#define WEIGHTS_H

#include <array>

extern const int pawnPhaseContribution;
extern const int knightPhaseContribution;
extern const int bishopPhaseContribution;
extern const int rookPhaseContribution;
extern const int queenPhaseContribution;
extern const int maxPhase;

extern const int passedPawnScore;
extern const int isolatedPawnPenalty;
extern const int doubledPawnPenalty;
extern const int kingDistanceToEdgePenalty;

extern const std::array<int,20> kingSafetyPenalties;
extern const std::array<int,20> mobilityScores;
extern const std::array<int,7> baseScoresTable;
extern const std::array<std::array<int,64>,7> earlygamePieceTables;
extern const std::array<std::array<int,64>,7> endgamePieceTables;


#endif // WEIGHTS_H