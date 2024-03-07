#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

#define TEST_FEN "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1"

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-Promotions]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 24);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-Promotions]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 496);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-Promotions]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 9483);
}

// ------ Depth 4 ------ //

TEST_CASE("LEAVES", "[Perft-Depth4-Promotions]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 182838);
}