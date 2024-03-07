#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

#define TEST_FEN "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1"

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 14);
}

TEST_CASE("CAPTURES", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 1);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 2);
}

TEST_CASE("CHECKMATES", "[Perft-Depth1-Position3]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 191);
}

TEST_CASE("CAPTURES", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 15);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 12);
}

TEST_CASE("CHECKMATES", "[Perft-Depth2-Position3]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 2812);
}

TEST_CASE("CAPTURES", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 224);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 2);
}

TEST_CASE("CASTLES", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 279);
}

TEST_CASE("CHECKMATES", "[Perft-Depth3-Position3]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 4 ------ //

TEST_CASE("LEAVES", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 43238);
}

TEST_CASE("CAPTURES", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 3572);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 125);
}

TEST_CASE("CASTLES", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 1959);
}

TEST_CASE("CHECKMATES", "[Perft-Depth4-Position3]") {
	PerftEngine eng;
	eng.runPerft(4,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 17);
}