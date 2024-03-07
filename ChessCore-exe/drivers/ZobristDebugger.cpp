#include "ChessCore.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

//#define LOG

using namespace std::chrono;
using namespace ChessCore;

void checkZobrist(BoardState* bs, int depth, const std::vector<ExtendedMove> moves, int* numFailedHashMatches, int* numSuccessfulHashMatches) {
	if (depth > 0) {
		uint64_t zobristBase = bs->getZobristBoardHash();
		for (auto iter = moves.begin(); iter != moves.end(); ++iter) {
			ExtendedMove move = *iter;
			bs->makeMove(move);
			checkZobrist(bs,depth-1,bs->getLegalExtendedMoves(),numFailedHashMatches,numSuccessfulHashMatches);
			bs->undoMove();
			bs->updateLegality();
			if (bs->getZobristBoardHash() == zobristBase) {
				(*numSuccessfulHashMatches)++;
			} else {
				(*numFailedHashMatches)++;
			}
#ifdef LOG
			std::cout << "Base Zobrist: " << std::hex << zobristBase << ", reversion Zobrist: " << bs->getZobristBoardHash() << std::endl;
#endif
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 8) {
		std::cout << "Usage: ZobristDebugger <depth:int> <FEN:str:board turn castleRights enPassantSquare halfmoveClock moveNumber>" << std::endl;
		std::cout << "Ex: ZobristDebugger 1 rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" << std::endl;
		return 1;
	}
	int depth = atoi(argv[1]);
	std::string FEN = std::string(argv[2]) + " " 
		+ std::string(argv[3]) + " " 
		+ std::string(argv[4]) + " " 
		+ std::string(argv[5]) + " " 
		+ std::string(argv[6]) + " " 
		+ std::string(argv[7]);
	std::cout << "Depth: (" << depth << "), FEN: (" << FEN << ")" << std::endl;
	BoardState bs(FEN);
	int numFailedHashMatches = 0;
	int numSuccessfulHashMatches = 0;
	auto start = high_resolution_clock::now();
	checkZobrist(
		&bs,
		depth,
		bs.getLegalExtendedMoves(),
		&numFailedHashMatches,
		&numSuccessfulHashMatches
	);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	
	std::cout << "--------------------" << std::endl;
	std::cout << "Time: " << duration.count() << "ms" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Stats" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Failed Matches:     " << numFailedHashMatches << std::endl;
	std::cout << "Successful Matches: " << numSuccessfulHashMatches << std::endl;
	std::cout << "--------------------" << std::endl;	
}