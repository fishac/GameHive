#include "ChessEngine.h"
#include "ChessCore.h"
#include "Weights.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std::chrono;

ExtendedMove ChessEngine::makeMove(int millisRemaining, int millisIncrement) {
	ExtendedMove ret = computeBestMove(millisRemaining,millisIncrement);
	bool madeMove = internalState->makeMove(ret);
	return ret;
}

ExtendedMove ChessEngine::suggestMove(int millisRemaining, int millisIncrement) {
	ExtendedMove ret = computeBestMove(millisRemaining,millisIncrement);
	return ret;
}

ExtendedMove ChessEngine::computeBestMove(int millisRemaining, int millisIncrement) {
	numScannedNodes = 1;
	numScannedLeaves = 0;
	currentTurnColor = internalState->getTurnColor();
	inNullMoveSearch = false;
	tTable->clear();
	clearKillerMoves();
	if (internalState->getCheckmateStatus() || internalState->getStalemateStatus()) {
		return nullMove();
	} else {
		return search(millisRemaining,millisIncrement);
	}
}

int ChessEngine::getSearchTimeLimit(int millisRemaining, int millisIncrement) {
	if (millisRemaining > 0) {
		int moveNumber = internalState->getMoveNumber();
		int estimatedTurnsLeft = std::max(60-moveNumber,20);
		int estimatedTotalTurns = moveNumber + estimatedTurnsLeft;
		int estimatedTimeLeft = millisRemaining;
		if (millisIncrement > 0) {
			estimatedTimeLeft += estimatedTurnsLeft*millisIncrement;
		}
		int estimatedTotalTime = estimatedTimeLeft * (estimatedTotalTurns) / estimatedTurnsLeft;
		int searchTimeLimit = 0;
		if (moveNumber < 7) {
			searchTimeLimit = estimatedTotalTime/100;
		} else if (moveNumber < 18) {
			searchTimeLimit = estimatedTotalTime/30;
		} else if (moveNumber < 26) { 
			searchTimeLimit = estimatedTotalTime/50;
		} else {
			searchTimeLimit = estimatedTotalTime/100;
		}
		searchTimeLimit = std::max(searchTimeLimit,100);
		/*
		std::cout 
			<< "moveNumber: " << moveNumber << std::endl
			<< "estimatedTurnsLeft: " << estimatedTurnsLeft << std::endl
			<< "estimatedTotalTurns: " << estimatedTotalTurns << std::endl
			<< "estimatedTimeLeft: " << estimatedTimeLeft << std::endl
			<< "estimatedTotalTime: " << estimatedTotalTime << std::endl
			<< "searchTimeLimit: " << searchTimeLimit << std::endl
			<< std::endl;
		*/
		return searchTimeLimit;
	} else {
		return -1;
	}
}

ExtendedMove ChessEngine::search(int millisRemaining, int millisIncrement) {
	auto startSearchTime = high_resolution_clock::now();
	auto currentTime = high_resolution_clock::now();
	int cumulativeSearchTime = duration_cast<milliseconds>(currentTime - startSearchTime).count();
	int searchTimeLimit = getSearchTimeLimit(millisRemaining, millisIncrement);
	int bestScore = worstPossibleScore;
	std::vector<ExtendedMove> moves = internalState->getLegalExtendedMoves();
	if (moves.size() == 1) {
		return moves[0];
	}
	int moveScore;
	ExtendedMove bestMove;
	bool inCheck = internalState->getCheckStatus();
	for (int currentDepthLimit = 1; currentDepthLimit <= maxDepth; currentDepthLimit++) {
		lastSearchedDepth = currentDepthLimit;
		clearKillerMoves();
		int currentBestScore = worstPossibleScore;
		int beta = bestPossibleScore;
		ExtendedMove currentBestMove;
		int nextDepthRemaining = currentDepthLimit-1;
		int extension = 0;
		bool moveIsCapture = false;
		bool moveGivesCheck = false;
		bool moveIsNearPromotion = false;
		bool moveIsPromotion = false;
		int moveIdx = 0;
		std::vector<int> moveOrder = getMoveOrder(currentDepthLimit,0,moves);

		for (auto iter = moveOrder.begin(); iter != moveOrder.end(); ++iter) {
			ExtendedMove move = moves[*iter];
			moveIsCapture = internalState->moveIsCapture(move);
			moveGivesCheck = internalState->moveGivesCheck(move);
			moveIsNearPromotion = internalState->moveIsNearPromotion(move);
			moveIsPromotion = internalState->moveRequiresPromotion(move);
			if (internalState->moveGivesCheck(move) || internalState->moveIsNearPromotion(move)) {
				extension = 1;
			} else {
				extension = 0;
			}
			makeMove(move,0);
			std::vector<ExtendedMove> nextMoves = internalState->getLegalExtendedMoves();
			
			if (moveIdx > 3 && extension == 0 && nextDepthRemaining > 2 && 
				!inCheck && !moveIsCapture && !moveGivesCheck && !moveIsNearPromotion && !moveIsPromotion
			) {
				moveScore = -searchInternal(currentDepthLimit,nextDepthRemaining-1,1,0,nextMoves,-beta,-currentBestScore);
				if (moveScore > currentBestScore) {
					moveScore = -searchInternal(currentDepthLimit,nextDepthRemaining,1,0,nextMoves,-beta,-currentBestScore);
				}
			} else {
				moveScore = -searchInternal(currentDepthLimit,nextDepthRemaining+extension,1,1,nextMoves,-beta,-currentBestScore);
			}
			unmakeMove(0);
			// Set possible alpha improvement
			if (moveScore > currentBestScore) {
				currentBestMove = move;
				currentBestScore = moveScore;
			}
			moveIdx++;
		}
		// Update stored best move after completing a depth
		bestMove = currentBestMove;
		bestScore = currentBestScore;
		
		// Check if we need to stop the search
		currentTime = high_resolution_clock::now();
		cumulativeSearchTime = duration_cast<milliseconds>(currentTime - startSearchTime).count();
		if (currentDepthLimit > minDepth && searchTimeLimit > 0 && cumulativeSearchTime > searchTimeLimit*50/100) {
			break;
		}
	}
	// Re-set legal moves for future move-making
	internalState->updateLegality();
	evaluation = bestScore;
	return bestMove;
}

int ChessEngine::searchInternal(const int& currentDepthLimit, const int& depthRemaining, const int& currentDepthIdx, const int& totalExtensions, std::vector<ExtendedMove>& moves, int alpha, int beta) {
	numScannedNodes++;
	if (moves.empty()) {
		numScannedLeaves++;
		return evaluateInternalState();
	} else if (depthRemaining <= 0) {
		numScannedLeaves++;
		return quiesce(currentDepthLimit,qDepthLimit,moves,alpha,beta);
	} else if (
		tTable->hasExistingUsableEntry(internalState->getZobristBoardHash(),currentDepthIdx,currentDepthLimit)
		&& internalState->isMoveLegal(tTable->getEntry(internalState->getZobristBoardHash()).bestMove)
	) {
	// if valid evaluation exists in the table
		// return the already-computed evaluation 
		return tTable->getEntry(internalState->getZobristBoardHash()).evaluation;
	} 
	
	int nextDepthRemaining = depthRemaining-1;
	if (shouldCheckNullMove(beta) && depthRemaining > 2) {
		int R = depthRemaining > 6 ? 4 : 3;
		inNullMoveSearch = true;
		internalState->engineMakeNullMove();
		internalState->updateLegality();
		std::vector<ExtendedMove> nextMoves = internalState->getLegalExtendedMoves();
		int moveScore = -zeroWindowSearch(currentDepthLimit,nextDepthRemaining-R,currentDepthIdx+1,nextMoves,-alpha);
		internalState->undoMove();
		inNullMoveSearch = false;
		
		if (moveScore >= beta) {
			nextDepthRemaining -= 4;
			if (nextDepthRemaining <= 0) {
				numScannedLeaves++;
				return quiesce(currentDepthLimit,qDepthLimit,moves,alpha,beta);
			}
		}
	} 
	ExtendedMove bestMove;
	int bestScore = worstPossibleScore;
	int moveScore = worstPossibleScore;
	
	int extension = 0;
	int moveIdx = 0;
	bool inCheck = internalState->getCheckStatus();
	bool moveIsCapture;
	bool moveGivesCheck;
	bool moveIsNearPromotion;
	bool moveIsPromotion;
	std::vector<int> moveOrder = getMoveOrder(currentDepthLimit,currentDepthIdx,moves);
	
	for (auto iter = moveOrder.begin(); iter != moveOrder.end(); ++iter) {
		ExtendedMove move = moves[*iter];
		moveIsCapture = internalState->moveIsCapture(move);
		moveGivesCheck = internalState->moveGivesCheck(move);
		moveIsNearPromotion = internalState->moveIsNearPromotion(move);
		moveIsPromotion = internalState->moveRequiresPromotion(move);
		if ((totalExtensions < maxExtensions)
			&& (internalState->moveGivesCheck(move) || internalState->moveIsNearPromotion(move))
		) {
			extension = 1;
		} else {
			extension = 0;
		}
		
		makeMove(move,currentDepthIdx);

		std::vector<ExtendedMove> nextMoves = internalState->getLegalExtendedMoves();
		if (moveIdx > 3 && extension == 0 && nextDepthRemaining > 2 && 
			!inCheck && !moveIsCapture && !moveGivesCheck && !moveIsNearPromotion && !moveIsPromotion
		) {
			moveScore = -searchInternal(currentDepthLimit,nextDepthRemaining-1,currentDepthIdx+1,totalExtensions,nextMoves,-beta,-alpha);
			if (moveScore > alpha) {
				moveScore = -searchInternal(currentDepthLimit,nextDepthRemaining,currentDepthIdx+1,totalExtensions,nextMoves,-beta,-alpha);
			}
		} else {
			moveScore = -searchInternal(currentDepthLimit,nextDepthRemaining+extension,currentDepthIdx+1,totalExtensions+extension,nextMoves,-beta,-alpha);
		}
		
		unmakeMove(currentDepthIdx);
		
		if (moveScore > bestScore) {
			bestMove = move;
			bestScore = moveScore;
		}
		if (moveScore >= beta) {
			alpha = moveScore;
			//killerMoves[currentDepthIdx] = move;
			break;
		}
		if (moveScore > alpha) {
			alpha = moveScore;
		}
		moveIdx++;
	}
	
	tTable->provideEntry({
		internalState->getZobristBoardHash(),
		currentDepthIdx,
		bestMove,
		bestScore,
		currentDepthLimit
	});
	return alpha;
}

int ChessEngine::zeroWindowSearch(const int& currentDepthLimit, const int& depthRemaining, const int& currentDepthIdx, std::vector<ExtendedMove>& moves, int beta) {
	numScannedNodes++;
	if (moves.empty()) {
		numScannedLeaves++;
		return evaluateInternalState();
	} else if (depthRemaining <= 0) {
		numScannedLeaves++;
		return quiesce(currentDepthLimit,qDepthLimit,moves,beta-1,beta);
	} 
	
	int nextDepthRemaining = depthRemaining-1;
	int moveScore = worstPossibleScore;
	
	std::vector<int> moveOrder = getMoveOrder(currentDepthLimit,currentDepthIdx,moves);
	
	for (auto iter = moveOrder.begin(); iter != moveOrder.end(); ++iter) {
		ExtendedMove move = moves[*iter];
		makeMove(move,currentDepthIdx);
		
		std::vector<ExtendedMove> nextMoves = internalState->getLegalExtendedMoves();
		moveScore = -zeroWindowSearch(currentDepthLimit,nextDepthRemaining,currentDepthIdx+1,nextMoves,1-beta);
			
		unmakeMove(currentDepthIdx);

		if (moveScore >= beta) {
			return beta;
		}
	}
	return 1-beta;
}

int ChessEngine::quiesce(const int& currentDepthLimit, const int& qDepth, std::vector<ExtendedMove>& moves, int alpha, int beta) {
	numScannedNodes++;
	int baselineScore = evaluateInternalState();
	if (moves.empty() || qDepth == 0) {
		return baselineScore;
	}
	if (baselineScore >= beta) {
		return baselineScore;
	}
	// Delta pruning. 
	// If capturing a free queen (naively scoring the position) wouldn't raise alpha,
	// don't bother searching and just return alpha
	if (baselineScore + baseScoresTable[QUEEN] < alpha) {
		return alpha;
	}
	if (baselineScore > alpha) {
		alpha = baselineScore;
	}

	std::vector<ExtendedMove> movesToCheck;
	for (auto iter = moves.begin(); iter != moves.end(); ++iter) {
		ExtendedMove move = *iter;
		bool shouldCheckMove = internalState->getCheckStatus();
		if (internalState->moveIsCapture(move)) {
			shouldCheckMove = shouldCheckMove || (staticExchangeEvaluation(move) >= 0);
		}
		if (shouldCheckMove) {
			movesToCheck.push_back(move);
		}
	}
	int moveScore;
	bool inCheck = internalState->getCheckStatus();
	for (auto iter = movesToCheck.begin(); iter != movesToCheck.end(); ++iter) {
		ExtendedMove move = *iter;
		internalState->engineMakeLegalMove(move);
		internalState->updateLegality();

		std::vector<ExtendedMove> nextMoves = internalState->getLegalExtendedMoves();
		moveScore = -quiesce(currentDepthLimit,qDepth-1,nextMoves,-beta,-alpha);
		
		internalState->undoMove();
		if (moveScore >= beta) {
			alpha = moveScore;
			break;
		}
		if (moveScore > alpha) {
			alpha = moveScore;
		}
	}
	return alpha;
}

// Evaluate a sequence of captures on a single square, starting from a given move 
int ChessEngine::staticExchangeEvaluation(const ExtendedMove& move) {
	// Get captured piece value
	Piece_t capturedPiece = internalState->getPieceOnSquare(move.to);
	// Make the move
	internalState->engineMakeLegalMove(move);
	internalState->updateLegality();
	// Evaluate the trade value recursively
	// If no recaptures, this is just the captured piece value 
	// If something recaptures, it evaluates the trade, and so on.
	int seeScore = baseScoresTable[capturedPiece] - staticExchangeEvaluationInternal(move.to);
	// Undo the move, make everything honky dory
	internalState->undoMove();
	//internalState->updateLegality();
	return seeScore;
}

// Evaluate a sequence of captures on a single square, prioritizing least valuable capturer
int ChessEngine::staticExchangeEvaluationInternal(const Square_t& sq) {
	int value = 0;
	// Get moves
	std::vector<ExtendedMove> moves = internalState->getLegalExtendedMoves();
	if (!moves.empty()) {
		// Get least valuable capturing move, if any moves exist toward given square 
		ExtendedMove leastValueCapturerMove = getLeastValueCapturerMoveToSquare(sq,moves);
		// If move to target square exists 
		if (!MoveUtils::extendedMoveEquals(leastValueCapturerMove,nullMove())) {
			// Get moving piece 
			Piece_t capturedPiece = internalState->getPieceOnSquare(leastValueCapturerMove.to);
			// Make the move 
			internalState->engineMakeLegalMove(leastValueCapturerMove);
			internalState->updateLegality();
			// Evaluate the trade value recursively
			// If no recaptures, this is just the captured piece value 
			// If something recaptures, it evaluates the trade, and so on.
			value = baseScoresTable[capturedPiece] - staticExchangeEvaluationInternal(leastValueCapturerMove.to);
			// Undo 
			internalState->undoMove();
		}
	}
	return value;
}

ExtendedMove ChessEngine::getLeastValueCapturerMoveToSquare(const Square_t& sq, const std::vector<ExtendedMove>& moves) {
	Piece_t lowestValue = 30;
	ExtendedMove bestMove = nullMove();
	for (auto iter = moves.begin(); iter != moves.end(); ++iter) {
		ExtendedMove m = *iter;
		Piece_t movingPiece = internalState->getPieceOnSquare(m.from);
		if (m.to == sq && movingPiece < lowestValue) {
			bestMove = m;
			lowestValue = movingPiece;
		}
		if (lowestValue == PAWN) {
			break;
		}
	}
	return bestMove;
}

bool ChessEngine::shouldCheckNullMove(const int& beta) {
	int numPieces = 0;
	if (internalState->getTurnColor()) {
		numPieces = internalState->getNumWhiteKnights()
						+ internalState->getNumWhiteBishops()
						+ internalState->getNumWhiteRooks() 
						+ internalState->getNumWhiteQueens();
	} else {
		numPieces = internalState->getNumBlackKnights()
						+ internalState->getNumBlackBishops()
						+ internalState->getNumBlackRooks() 
						+ internalState->getNumBlackQueens();
	}
	if (!inNullMoveSearch && !internalState->getCheckStatus() && numPieces > 0) {
		return evaluateInternalState() > beta;
	} else {
		return false;
	}
}

std::vector<int> ChessEngine::getMoveOrder(const int& currentDepthLimit, const int& depthIdx, const std::vector<ExtendedMove>& moves) {
	ExtendedMove bestMove = nullMove();
	std::vector<int> priorities;
	ExtendedMove leastValuableCapturer = nullMove();
	if (depthIdx > 0) {
		leastValuableCapturer = getLeastValueCapturerMoveToSquare(moveStack[depthIdx-1].to, moves);
	}
	for (auto iter = moves.begin(); iter != moves.end(); ++iter) {
		priorities.push_back(getPriority(*iter,leastValuableCapturer,currentDepthLimit,depthIdx));
	}
	std::vector<int> indices(moves.size());
	std::iota(indices.begin(),indices.end(),0);
	std::sort(indices.begin(),indices.end(),
		[&](int i1, int i2) {
			return priorities[i1] > priorities[i2];
		}
	);
	return indices;
}

int ChessEngine::getPriority(const ExtendedMove& m, const ExtendedMove& leastValuableCapturer, const int& currentDepthLimit, const int& currentDepthIdx) {
	if (
		tTable->hasExistingReferencableEntry(internalState->getZobristBoardHash(),currentDepthIdx,currentDepthLimit)
		&& internalState->isMoveLegal(tTable->getEntry(internalState->getZobristBoardHash()).bestMove)
		&& MoveUtils::extendedMoveEquals(m, tTable->getEntry(internalState->getZobristBoardHash()).bestMove)
	) {
		return 10000;
	} else if (MoveUtils::extendedMoveEquals(m,leastValuableCapturer)) {
		return 9000;
	} else {
		int priority = 0;
		if (internalState->moveIsCapture(m)) {
			Piece_t movingPiece = internalState->getPieceOnSquare(m.from);
			Piece_t capturedPiece = internalState->getPieceOnSquare(m.to);
			int materialDifference = capturedPiece - movingPiece;
			priority += 2000 + (10*capturedPiece - (10-movingPiece));
		} else {
			Piece_t movingPiece = internalState->getPieceOnSquare(m.from);
			priority += (10-movingPiece);
		}
		return priority;
	}
}

void ChessEngine::clearKillerMoves() {
	for (int i=0; i<killerMoves.size(); i++) {
		killerMoves[i] = nullMove();
	}
}

void ChessEngine::makeMove(const ExtendedMove& move, const int& currentDepthIdx) {
	internalState->engineMakeLegalMove(move);
	internalState->updateLegality();
	moveStack[currentDepthIdx] = move;
}

void ChessEngine::unmakeMove(const int& currentDepthIdx) {
	internalState->undoMove();
	moveStack[currentDepthIdx] = nullMove();
}