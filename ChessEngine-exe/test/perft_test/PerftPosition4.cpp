#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

#define TEST_FEN "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 6);
}

TEST_CASE("CAPTURES", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 0);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 0);
}

TEST_CASE("CHECKMATES", "[Perft-Depth1-Position4]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 264);
}

TEST_CASE("CAPTURES", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 87);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 6);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 48);
}

TEST_CASE("CHECKS", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 10);
}

TEST_CASE("CHECKMATES", "[Perft-Depth2-Position4]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 9467);
}

TEST_CASE("CAPTURES", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 1108);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 4);
}

TEST_CASE("CASTLES", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 6);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 168);
}

TEST_CASE("CHECKS", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 48);
}

TEST_CASE("CHECKMATES", "[Perft-Depth3-Position4]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 22);
}
