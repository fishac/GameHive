#ifndef ENGINEBOARDSTATE_H
#define ENGINEBOARDSTATE_H

#include "ChessCore.h"

using namespace ChessCore;

class EngineBoardState : public BoardState {
public:
	~EngineBoardState();
	EngineBoardState();
	EngineBoardState(const bool& setupDefaultStartingPosition);
	EngineBoardState(const std::string& FEN);
	EngineBoardState(const EngineBoardState& bs);
	void engineMakeLegalMove(const ExtendedMove& m);
	void engineMakeNullMove();
};

#endif // ENGINEBOARDSTATE_H 