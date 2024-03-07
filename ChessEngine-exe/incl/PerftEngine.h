#ifndef PERFTENGINE_H
#define PERFTENGINE_H

#include "EngineBoardState.h"

#include <unordered_map>
#include <string>
#include <fstream>

using namespace ChessCore;

class PerftEngine {
public:
	~PerftEngine();
	PerftEngine();
	void runPerft(int depthSetting);
	void runPerft(int depthSetting, std::string FEN);
	int getNumScannedNodes();
	int getNumScannedLeaves();
	int getNumScannedCaptures();
	int getNumScannedEnPassants();
	int getNumScannedCastles();
	int getNumScannedPromotions();
	int getNumScannedChecks();
	int getNumScannedCheckmates();
	void setLogging(bool logSetting);
	void setDivide(bool divideSetting);
	std::unordered_map<std::string,int> getDivideStats();
private:
	int numScannedNodes = 0;
	int numScannedLeaves = 0;
	int numScannedCaptures = 0;
	int numScannedEnPassants = 0;
	int numScannedCastles = 0;
	int numScannedPromotions = 0;
	int numScannedChecks = 0;
	int numScannedCheckmates = 0;
	bool log = false;
	bool archive = false;
	bool reportDivide = false;
	std::string currentDivideMove;
	int activeDepthSetting = 0;
	std::unordered_map<std::string,int> perftDivide;
	EngineBoardState* internalState = new EngineBoardState(false);
	void resetPerftStats();
	void perft(int depth, std::vector<ExtendedMove>& moves);
	std::string getSimpleMoveString(const ExtendedMove& m);
};

#endif // PERFTENGINE_H 