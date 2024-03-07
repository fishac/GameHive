#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

#define TEST_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 48);
}

TEST_CASE("CAPTURES", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 8);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 2);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 0);
}

TEST_CASE("CHECKMATES", "[Perft-Depth1-Position2]") {
	PerftEngine eng;
	eng.runPerft(1,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 2039);
}

TEST_CASE("CAPTURES", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 359);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 1);
}

TEST_CASE("CASTLES", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 93);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 3);
}

TEST_CASE("CHECKMATES", "[Perft-Depth2-Position2]") {
	PerftEngine eng;
	eng.runPerft(2,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedLeaves() == 97862);
}

TEST_CASE("CAPTURES", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCaptures() == 17461);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedEnPassants() == 46);
}

TEST_CASE("CASTLES", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCastles() == 3255);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedChecks() == 996);
}

TEST_CASE("CHECKMATES", "[Perft-Depth3-Position2]") {
	PerftEngine eng;
	eng.runPerft(3,TEST_FEN);
	REQUIRE(eng.getNumScannedCheckmates() == 1);
}
