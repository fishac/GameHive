#include "ChessEngineManager.h"
#include <iostream>

ChessEngineManager::ChessEngineManager() {}

void ChessEngineManager::initialize() {
	initialized = true;
	eng = new ChessEngine();
	eng->setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void ChessEngineManager::deinitialize() {
	if (initialized) {
		initialized = false;
		delete eng;
	}
}

void ChessEngineManager::computeMove(int millisRemaining, int incrementMillis) {
	ExtendedMove m = eng->makeMove(millisRemaining,incrementMillis);
	emit engineComputedMove(m);
}

void ChessEngineManager::handleProvidedMove(const ExtendedMove& m) {	
	bool madeMove = eng->provideMove(m);
}

ChessEngineManager::~ChessEngineManager() {
	deinitialize();
} 
