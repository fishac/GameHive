#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include "ChessCore.h"
#include "EngineBoardState.h"
#include "TranspositionTable.h"
#include <array>

using namespace ChessCore;
using namespace ChessCore::Color;
using namespace ChessCore::Piece;

class ChessEngine {
public:
	~ChessEngine();
	ChessEngine();
	ExtendedMove makeMove(int millisRemaining, int millisIncrement);
	ExtendedMove suggestMove(int millisRemaining, int millisIncrement);
	bool provideMove(const ExtendedMove& m);
	void setMaxDepth(int depth);
	void setMinDepth(int depth);
	int getMaxDepth();
	int getMinDepth();
	int getLastSearchedDepth();
	void setFEN(std::string FEN);
	std::string getFEN();
	int getNumScannedNodes();
	int getEvaluation();
	void reportTTStats();
	int getLastSearchTimeLimit();
private:
	EngineBoardState* internalState;
	TranspositionTable* tTable;
	std::array<ExtendedMove,30> killerMoves;
	std::array<ExtendedMove,30> moveStack;
	Color_t pieceColor;
	int numScannedNodes = 0;
	int numScannedLeaves = 0;
	int minDepth = 3;
	int maxDepth = 12;
	int minSearchTimeMillis = 100;
	int evaluation = 0;
	int worstPossibleScore = -1e9;
	int bestPossibleScore = 1e9;
	int qDepthLimit = 10;
	int maxExtensions = 6;
	int lastSearchedDepth = 0;
	bool inNullMoveSearch = false;
	bool currentTurnColor;
	int getCurrentPhase();
	ExtendedMove computeBestMove(int millisRemaining, int millisIncrement);
	bool shouldComputeMove();
	bool shouldCheckNullMove(const int& beta);
	ExtendedMove nullMove();
	int evaluateInternalState();
	int getSearchTimeLimit(int millisRemaining, int millisIncrement);
	ExtendedMove search(int millisRemaining, int millisIncrement);
	int searchInternal(const int& currentDepthLimit, const int& depthRemaining, const int& currentDepthIdx, const int& totalExtensions, std::vector<ExtendedMove>& moves, int alpha, int beta);
	int zeroWindowSearch(const int& currentDepthLimit, const int& depthRemaining, const int& currentDepthIdx, std::vector<ExtendedMove>& moves, int beta);
	int quiesce(const int& currentDepthLimit, const int& qDepth, std::vector<ExtendedMove>& moves, int alpha, int beta);
	int staticExchangeEvaluation(const ExtendedMove& move);
	int staticExchangeEvaluationInternal(const Square_t& sq);
	ExtendedMove getLeastValueCapturerMoveToSquare(const Square_t& sq, const std::vector<ExtendedMove>& moves);
	static auto makeCompareFunction(EngineBoardState* state);
	bool compareFunction(const ExtendedMove& m1, const ExtendedMove& m2);
	std::vector<int> getMoveOrder(const int& currentDepthLimit, const int& depth, const std::vector<ExtendedMove>& moves);
	int getPriority(const ExtendedMove& m, const ExtendedMove& leastValuableCapturer, const int& currentDepthLimit, const int& currentDepthIdx);
	BoardMask_t getSensitiveKingRegion(const Color_t& c);
	void clearKillerMoves();
	void makeMove(const ExtendedMove& m, const int& currentDepthIdx);
	void unmakeMove(const int& currentDepthIdx);
};

#endif // CHESSENGINE_H 