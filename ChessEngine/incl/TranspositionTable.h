#ifndef TRANSPOSITIONTABLE_H
#define TRANSPOSITIONTABLE_H

#include "ChessCore.h"
#include <array>

#define MAX_ENTRIES_MASK 0xFFFFF
#define DEPTH_PRIORITY

using namespace ChessCore;

struct TTEntry {
	uint64_t zobristKey;
	int depthIdx;
	ExtendedMove bestMove;
	int evaluation;
	int maxDepth;
};

class TranspositionTable {
public:
	TranspositionTable();
	void clear();
	bool hasExistingUsableEntry(const uint64_t& zobristKey, const int& depthIdx, const int& maxDepth);
	bool hasExistingReferencableEntry(const uint64_t& zobristKey, const int& depthIdx, const int& maxDepth);
	const TTEntry& getEntry(const uint64_t& zobristKey);
	void provideEntry(const TTEntry& entry);
	void reportStats();
private:
	std::array<TTEntry,MAX_ENTRIES_MASK+1> entries;
	int numIndexCollisions = 0;
	int numZobristKeyCollisions = 0;
	int numNewEntries = 0;
	int numReplacements = 0;
	int numAccesses = 0;
	int numProvidedEntries = 0;
};

#endif // TRANSPOSITIONTABLE_H 