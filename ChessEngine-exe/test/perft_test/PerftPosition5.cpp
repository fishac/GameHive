#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

#define TEST_FEN "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-Position5]") {
	PerftEngine eng;
	//eng.setLogging(true);
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 44);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-Position5]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 1486);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-Position5]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 62379);
}

