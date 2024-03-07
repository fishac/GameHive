#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

int main(int argc, char *argv[]) {
	if (argc != 8) {
		std::cout << "Usage: PerftCustomDriver <depth:int> <FEN:str:board turn castleRights enPassantSquare halfmoveClock moveNumber>" << std::endl;
		std::cout << "Ex: PerftCustomDriver 1 rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" << std::endl;
		return 1;
	}
	int depth = atoi(argv[1]);
	std::string FEN = std::string(argv[2]) + " " 
		+ std::string(argv[3]) + " " 
		+ std::string(argv[4]) + " " 
		+ std::string(argv[5]) + " " 
		+ std::string(argv[6]) + " " 
		+ std::string(argv[7]);
	PerftEngine eng;
	//eng.setLogging(true);
	bool reportDivide = true;
	eng.setDivide(reportDivide);
	std::cout << "Depth: (" << depth << "), FEN: (" << FEN << ")" << std::endl;
	auto start = high_resolution_clock::now();
	eng.runPerft(depth,FEN);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::unordered_map<std::string,int> divideStats = eng.getDivideStats();
	
	std::cout << "--------------------" << std::endl;
	std::cout << "FEN: " << FEN << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Time: " << duration.count() << "ms" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Stats" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Nodes: " << eng.getNumScannedNodes() << std::endl;
	std::cout << "Leaves: " << eng.getNumScannedLeaves() << std::endl;
	std::cout << "Captures:  " << eng.getNumScannedCaptures() << std::endl;
	std::cout << "En Passants: " << eng.getNumScannedEnPassants() << std::endl;
	std::cout << "Castles: " << eng.getNumScannedCastles() << std::endl;
	std::cout << "Promotions: " << eng.getNumScannedPromotions() << std::endl;
	std::cout << "Checks: " << eng.getNumScannedChecks() << std::endl;
	std::cout << "Checkmates: " << eng.getNumScannedCheckmates() << std::endl;
	std::cout << "--------------------" << std::endl;
	if (reportDivide) {
		std::cout << "Divide" << std::endl;
		std::cout << "--------------------" << std::endl;

		std::vector<std::string> keys;
		for (auto iter = divideStats.begin(); iter != divideStats.end(); ++iter) {
			keys.push_back(iter->first);
		}
		std::sort(keys.begin(),keys.end());
		for (auto iter = keys.begin(); iter != keys.end(); ++iter) {
			std::cout << *iter << ": " << divideStats[*iter] << std::endl;
		}
	}
	
}