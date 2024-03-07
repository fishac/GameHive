#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "PerftEngine.h"

#include <iostream>

// ------ Depth 1 ------ //

TEST_CASE("LEAVES", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedLeaves() == 20);
}

TEST_CASE("CAPTURES", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedCaptures() == 0);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedChecks() == 0);
}

TEST_CASE("CHECKMATES", "[Perft-Depth1-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(1);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 2 ------ //

TEST_CASE("LEAVES", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedLeaves() == 400);
}

TEST_CASE("CAPTURES", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedCaptures() == 0);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedChecks() == 0);
}

TEST_CASE("CHECKMATES", "[Perft-Depth2-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(2);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 3 ------ //

TEST_CASE("LEAVES", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedLeaves() == 8902);
}

TEST_CASE("CAPTURES", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedCaptures() == 34);
}

TEST_CASE("EN PASSANTS", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
}

TEST_CASE("CASTLES", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedCastles() == 0);
}

TEST_CASE("PROMOTIONS", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedPromotions() == 0);
}

TEST_CASE("CHECKS", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedChecks() == 12);
}

TEST_CASE("CHECKMATES", "[Perft-Depth3-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(3);
	REQUIRE(eng.getNumScannedCheckmates() == 0);
}

// ------ Depth 4 ------ //

TEST_CASE("ALL", "[Perft-Depth4-InitialPosition]") {
	PerftEngine eng;
	eng.runPerft(4);
	REQUIRE(eng.getNumScannedLeaves() == 197281);
	REQUIRE(eng.getNumScannedCaptures() == 1610);
	REQUIRE(eng.getNumScannedEnPassants() == 0);
	REQUIRE(eng.getNumScannedCastles() == 0);
	REQUIRE(eng.getNumScannedPromotions() == 0);
	REQUIRE(eng.getNumScannedChecks() == 481);
	REQUIRE(eng.getNumScannedCheckmates() == 8);
}
