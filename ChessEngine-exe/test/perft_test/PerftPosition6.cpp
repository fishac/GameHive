#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

#define TEST_FEN "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-Position6]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 46);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-Position6]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 2079);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-Position6]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 89890);
}

