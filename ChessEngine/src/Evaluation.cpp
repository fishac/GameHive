#include "ChessEngine.h"
#include "ChessCore.h"
#include "Weights.h"
#include <algorithm>

int ChessEngine::getCurrentPhase() {
	return (
		pawnPhaseContribution*(internalState->getNumWhitePawns() + internalState->getNumBlackPawns())
		+ knightPhaseContribution*(internalState->getNumWhiteKnights() + internalState->getNumBlackKnights())
		+ bishopPhaseContribution*(internalState->getNumWhiteBishops() + internalState->getNumBlackBishops())
		+ rookPhaseContribution*(internalState->getNumWhiteRooks() + internalState->getNumBlackRooks())
		+ queenPhaseContribution*(internalState->getNumWhiteQueens() + internalState->getNumBlackQueens())
	);
}

int ChessEngine::evaluateInternalState() {
	if (internalState->getCheckmateStatus()) {
		return -(checkmatingScore);
	} else if (internalState->getStalemateStatus()) {
		return 0;
	}
	const std::array<Piece_t,64>& whitePieces = internalState->getWhitePieces();
	const std::array<Piece_t,64>& blackPieces = internalState->getBlackPieces();
	int whitePiecePoints = 0;
	int blackPiecePoints = 0;
	int whiteMobilityScore = 0;
	int blackMobilityScore = 0;
	int currentPhase = getCurrentPhase();
	Piece_t wp = NOPIECE;
	Piece_t bp = NOPIECE;
	int tempMobility = 0;
	for(int i=0; i<64; i++) {
		if (whitePieces[i] != NOPIECE && whitePieces[i] != KING) {
			wp = whitePieces.at(i);
			whitePiecePoints += baseScoresTable.at(wp) + (
				getWhiteEarlygameWeight(wp,i)*std::min(currentPhase,maxPhase) 
				+ getWhiteEndgameWeight(wp,i)*std::max(maxPhase-currentPhase,0)
			) / maxPhase;
			tempMobility = internalState->getTotalVisibilityFromIndex(i);
			whiteMobilityScore += (
				earlygameMobilityWeights[wp]*tempMobility*std::min(currentPhase,maxPhase) 
				+ endgameMobilityWeights[wp]*tempMobility*std::max(maxPhase-currentPhase,0)
			) / maxPhase;
		} else if (blackPieces[i] != NOPIECE && blackPieces[i] != KING) {
			bp = blackPieces.at(i);
			blackPiecePoints += baseScoresTable.at(bp) + (
				getBlackEarlygameWeight(bp,i)*std::min(currentPhase,maxPhase)
				+ getBlackEndgameWeight(bp,i)*std::max(maxPhase-currentPhase,0)
			) / maxPhase;
			tempMobility = internalState->getTotalVisibilityFromIndex(i);
			blackMobilityScore += (
				earlygameMobilityWeights[bp]*tempMobility*std::min(currentPhase,maxPhase) 
				+ endgameMobilityWeights[bp]*tempMobility*std::max(maxPhase-currentPhase,0)
			) / maxPhase;
		}
	}
	
	int whiteKingSafety = kingSafetyPenalties[
		std::max(
			internalState->getTotalAttacksOnRegionByBlack(getSensitiveKingRegion(WHITE)),
			(int) kingSafetyPenalties.size()
		)
	];
	int blackKingSafety = kingSafetyPenalties[
		std::max(
			internalState->getTotalAttacksOnRegionByWhite(getSensitiveKingRegion(BLACK)),
			(int) kingSafetyPenalties.size()
		)
	];
	
	int opposingKingDistanceToEdge = 0;
	if (internalState->getTurnColor()) {
		opposingKingDistanceToEdge = internalState->getBlackKingDistanceToEdge();
	} else {
		opposingKingDistanceToEdge = internalState->getWhiteKingDistanceToEdge();
	}
	int kingDistanceFactor = kingDistanceToEdgePenalty*opposingKingDistanceToEdge*std::max(maxPhase-currentPhase,0)/maxPhase;
	
	int numWhitePassedPawns = internalState->getNumWhitePassedPawns();
	int numBlackPassedPawns = internalState->getNumBlackPassedPawns();
	int numWhiteIsolatedPawns = internalState->getNumWhiteIsolatedPawns();
	int numBlackIsolatedPawns = internalState->getNumBlackIsolatedPawns();
	int numWhiteDoubledPawns = internalState->getNumWhiteDoubledPawns();
	int numBlackDoubledPawns = internalState->getNumBlackDoubledPawns();
	
	int turnColorMultiplier = internalState->getTurnColor() ? 1 : -1;
	
	return turnColorMultiplier*(
		(whitePiecePoints - blackPiecePoints)
		+ (whiteKingSafety - blackKingSafety)
		+ (whiteMobilityScore - blackMobilityScore)
		+ passedPawnScore*(numWhitePassedPawns - numBlackPassedPawns)
		+ isolatedPawnPenalty*(numWhiteIsolatedPawns - numBlackIsolatedPawns)
		+ doubledPawnPenalty*(numWhiteDoubledPawns - numBlackDoubledPawns)
		+ kingDistanceFactor
	);
}

BoardMask_t ChessEngine::getSensitiveKingRegion(const Color_t& c) {
	Square_t kingSquare = NO_SQUARE;
	if (internalState->getTurnColor()) {
		kingSquare = internalState->getWhiteKingSquare();
	} else {
		kingSquare = internalState->getBlackKingSquare();
	}
	BoardMask_t sensitiveRegion = (kingSquare | Square::e(kingSquare) | Square::w(kingSquare));
	sensitiveRegion |= (Square::n(sensitiveRegion) | Square::s(sensitiveRegion) | Square::nn(sensitiveRegion) | Square::ss(sensitiveRegion));
	return sensitiveRegion;
}