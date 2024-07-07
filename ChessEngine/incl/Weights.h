#ifndef WEIGHTS_H
#define WEIGHTS_H
#include "ChessCore.h"
#include <array>

using namespace ChessCore::Piece;

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
extern const std::array<int,7> earlygameMobilityWeights;
extern const std::array<int,7> endgameMobilityWeights;
extern const std::array<int,7> baseScoresTable;
extern const std::array<std::array<int,64>,7> earlygamePieceTables;
extern const std::array<std::array<int,64>,7> endgamePieceTables;

int getWhiteEarlygameWeight(const Piece_t& p, const int& sq_idx);
int getBlackEarlygameWeight(const Piece_t& p, const int& sq_idx);
int getWhiteEndgameWeight(const Piece_t& p, const int& sq_idx);
int getBlackEndgameWeight(const Piece_t& p, const int& sq_idx);

#endif // WEIGHTS_H