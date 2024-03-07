#include "EngineBoardState.h"

EngineBoardState::EngineBoardState() : BoardState() {
}

EngineBoardState::EngineBoardState(const bool& setupDefaultStartingPosition) : BoardState(setupDefaultStartingPosition) {
}

EngineBoardState::EngineBoardState(const std::string& FEN) : BoardState(FEN) {
}

void EngineBoardState::engineMakeLegalMove(const ExtendedMove& m) {
	makeLegalExtendedMove(m);
}

void EngineBoardState::engineMakeNullMove() {
	makeNullMove();
}

EngineBoardState::~EngineBoardState() {
	
}
