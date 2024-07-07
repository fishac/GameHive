#include "TranspositionTable.h"
#include <iostream>

TranspositionTable::TranspositionTable() {
	clear();
}

void TranspositionTable::clear() {
	for (int i=0; i<=MAX_ENTRIES_MASK; i++) {
		entries[i] = {
			(uint64_t) 0,
			0,
			{
				NO_SQUARE,
				NO_SQUARE,
				ChessCore::Piece::NOPIECE
			},
			0,
			0
		};
	}
	numIndexCollisions = 0;
	numZobristKeyCollisions = 0;
	numNewEntries = 0;
	numReplacements = 0;
	numAccesses = 0;
	numProvidedEntries = 0;
}

bool TranspositionTable::hasExistingUsableEntry(const uint64_t& zobristKey, const int& depthIdx, const int& maxDepth) {
	const TTEntry& entry = getEntry(zobristKey);
	return (entry.zobristKey == zobristKey && entry.depthIdx <= depthIdx && entry.maxDepth == maxDepth);
}

bool TranspositionTable::hasExistingReferencableEntry(const uint64_t& zobristKey, const int& depthIdx, const int& maxDepth) {
	const TTEntry& entry = getEntry(zobristKey);
	return (entry.zobristKey == zobristKey && entry.depthIdx <= depthIdx && entry.maxDepth <= maxDepth);
}

const TTEntry& TranspositionTable::getEntry(const uint64_t& zobristKey) {
	numAccesses++;
	return entries[zobristKey & MAX_ENTRIES_MASK];
}

void TranspositionTable::provideEntry(const TTEntry& providedEntry) {
	numProvidedEntries++;
	
	const TTEntry& currentEntry = getEntry(providedEntry.zobristKey);
	
	if ((currentEntry.zobristKey & MAX_ENTRIES_MASK) 
		== (providedEntry.zobristKey & MAX_ENTRIES_MASK)) {
		numIndexCollisions++;
	}
	
	if (currentEntry.zobristKey == providedEntry.zobristKey) {
		numZobristKeyCollisions++;
	}
	
	if (// Replace same-position lower depth entry with higher depth 
		currentEntry.maxDepth > providedEntry.maxDepth 
		|| (
			currentEntry.zobristKey == providedEntry.zobristKey 
			&& providedEntry.depthIdx <= currentEntry.depthIdx
		) || ( // Replace different-position entry 
			currentEntry.zobristKey != providedEntry.zobristKey
#ifdef DEPTH_PRIORITY
			// ... if depth is greater
			&& providedEntry.depthIdx <= currentEntry.depthIdx
#endif
		)
	) {
		numReplacements++;
		entries[providedEntry.zobristKey & MAX_ENTRIES_MASK] = {
			providedEntry.zobristKey,
			providedEntry.depthIdx,
			providedEntry.bestMove,
			providedEntry.evaluation,
			providedEntry.maxDepth
		};
	}
}
	
void TranspositionTable::reportStats() {
	std::cout << "Transposition Table stats: " << std::endl;
	std::cout << "\tMax entries: " << MAX_ENTRIES_MASK << ", Max entries mask: " << std::hex << MAX_ENTRIES_MASK << std::endl;
	std::cout << std::dec;
	std::cout << "\tTotal accesses:               " << numAccesses << std::endl;
	std::cout << "\tTotal provided entries:       " << numProvidedEntries << std::endl;
	std::cout << "\tTotal index collisions:       " << numIndexCollisions << std::endl;
	std::cout << "\tTotal zobrist key collisions: " << numZobristKeyCollisions << std::endl;
	std::cout << "\tTotal replacements:           " << numReplacements << std::endl;
}