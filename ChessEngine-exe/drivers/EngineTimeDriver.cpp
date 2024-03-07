#include "ChessCore.h"
#include "ChessEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

int main(int argc, char *argv[]) {
	if (argc != 9) {
		std::cout << "Usage: EngineTimeDriver <millisRemaining:int> <incrementMillis:int> <FEN:str:board turn castleRights enPassantSquare halfmoveClock moveNumber>" << std::endl;
		std::cout << "Ex: EngineTimeDriver 180000 200 rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" << std::endl;
		return 1;
	}
	int millisRemaining = atoi(argv[1]);
	int incrementMillis = atoi(argv[2]);
	std::string FEN = std::string(argv[3]) + " " 
		+ std::string(argv[4]) + " " 
		+ std::string(argv[5]) + " " 
		+ std::string(argv[6]) + " " 
		+ std::string(argv[7]) + " " 
		+ std::string(argv[8]);
	ChessEngine eng;
	eng.setFEN(FEN);
	std::cout << "FEN: (" << FEN << ")" << std::endl;
	auto start = high_resolution_clock::now();
	ExtendedMove m = eng.suggestMove(millisRemaining,incrementMillis);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	
	std::cout << "--------------------" << std::endl;
	std::cout << "Time: " << duration.count() << "ms" << std::endl;
	std::cout << "Depth: " << eng.getLastSearchedDepth() << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Stats" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Best Move: " << MoveUtils::getString(m) << std::endl;
	std::cout << "Evaluation: " << eng.getEvaluation() << std::endl;
	std::cout << "Nodes: " << eng.getNumScannedNodes() << std::endl;
	std::cout << "--------------------" << std::endl;	
}