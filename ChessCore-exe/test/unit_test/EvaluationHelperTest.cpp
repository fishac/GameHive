#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"

using namespace ChessCore;
using namespace ChessCore::Color;

TEST_CASE("WHITE PASSED PAWNS", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/7p/4p3/1P1P2PP/2p5/2P2P2/8/K7 w - - 0 1");
	REQUIRE(bs.getNumWhitePassedPawns() == 1);
}

TEST_CASE("BLACK PASSED PAWNS", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/5p2/p1p2Pp1/8/8/1P2p3/8/K7 w - - 0 1");
	REQUIRE(bs.getNumBlackPassedPawns() == 1);
}

TEST_CASE("WHITE DOUBLED PAWNS", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/8/1P2p3/1P4p1/1P2P1P1/8/4P3/K7 w - - 0 1");
	REQUIRE(bs.getNumWhiteDoubledPawns() == 2);
}

TEST_CASE("BLACK DOUBLED PAWNS", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/4p3/1p6/1p1pp1p1/1p6/1P3P2/8/K7 w - - 0 1");
	REQUIRE(bs.getNumBlackDoubledPawns() == 2);
}

TEST_CASE("WHITE ISOLATED PAWNS", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/2pp1pp1/2P3p1/3P2P1/1p6/P7/8/K7 w - - 0 1");
	REQUIRE(bs.getNumWhiteIsolatedPawns() == 2);
}

TEST_CASE("BLACK ISOLATED PAWNS", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/8/3p2p1/p2P4/3P4/1P2pP2/P3P1P1/K7 w - - 0 1");
	REQUIRE(bs.getNumBlackIsolatedPawns() == 2);
}

TEST_CASE("KING DISTANCE TO EDGE", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("k7/8/8/8/8/8/8/K7 w - - 0 1");
	REQUIRE(bs.getWhiteKingDistanceToEdge() == 0);
	REQUIRE(bs.getBlackKingDistanceToEdge() == 0);
	bs.setFEN("8/8/8/4k3/8/3K4/8/8 w - - 0 1");
	REQUIRE(bs.getWhiteKingDistanceToEdge() == 2);
	REQUIRE(bs.getBlackKingDistanceToEdge() == 3);
}

TEST_CASE("TOTAL ATTACKS ON REGION", "[EvaluationHelper]") {
	BoardState bs;
	BoardMask_t region = Square::getSquare("b2")
	| Square::getSquare("c2")
	| Square::getSquare("d2")
	| Square::getSquare("b3")
	| Square::getSquare("c3")
	| Square::getSquare("d3")
	| Square::getSquare("b4")
	| Square::getSquare("c4")
	| Square::getSquare("d4");
	
	bs.setFEN("1r4k1/8/8/8/3n4/3P4/7R/2B4K w - - 0 1");
	REQUIRE(bs.getTotalAttacksOnRegionByWhite(region) == 5);
	REQUIRE(bs.getTotalAttacksOnRegionByBlack(region) == 5);
	REQUIRE(bs.getTotalAttacksOnRegionByColor(region, WHITE) == 5);
	REQUIRE(bs.getTotalAttacksOnRegionByColor(region, BLACK) == 5);
	
	bs.setFEN("6k1/8/8/8/8/2Q5/8/7K w - - 0 1");
	REQUIRE(bs.getTotalAttacksOnRegionByWhite(region) == 8);
	REQUIRE(bs.getTotalAttacksOnRegionByBlack(region) == 0);
	REQUIRE(bs.getTotalAttacksOnRegionByColor(region, WHITE) == 8);
	REQUIRE(bs.getTotalAttacksOnRegionByColor(region, BLACK) == 0);
}

TEST_CASE("TOTAL MOBILITY", "[EvaluationHelper]") {
	BoardState bs;
	bs.setFEN("7k/8/2r2q2/4b3/2p2n2/2Q3N1/2NB4/7K w - - 0 1");
	REQUIRE(bs.getWhiteTotalMobility() == 27);
	REQUIRE(bs.getBlackTotalMobility() == 32);
	REQUIRE(bs.getTotalMobility(WHITE) == 27);
	REQUIRE(bs.getTotalMobility(BLACK) == 32);
	
	bs.setFEN("7k/8/2r2q2/4b3/2p2n2/2Q3N1/2NB4/7K b - - 0 1");
	REQUIRE(bs.getWhiteTotalMobility() == 27);
	REQUIRE(bs.getBlackTotalMobility() == 32);
	REQUIRE(bs.getTotalMobility(WHITE) == 27);
	REQUIRE(bs.getTotalMobility(BLACK) == 32);
}