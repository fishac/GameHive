#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "ChessEngine.h"
#include "Weights.h"

#include <iostream>

using namespace ChessCore;
using namespace ChessCore::Piece;
TEST_CASE("Symmetric weight mapping white:black", "[EvaluationTest,true)") {
	Square_t a1 = Square::getSquare("a1");
	Square_t a2 = Square::getSquare("a2");
	Square_t b3 = Square::getSquare("b3");
	Square_t e4 = Square::getSquare("e4");
	Square_t e5 = Square::getSquare("e5");
	Square_t b6 = Square::getSquare("b6");
	Square_t a7 = Square::getSquare("a7");
	Square_t a8 = Square::getSquare("a8");
	
	int a1_idx = Square::getIndex(a1);
	int a2_idx = Square::getIndex(a2);
	int b3_idx = Square::getIndex(b3);
	int e4_idx = Square::getIndex(e4);
	int e5_idx = Square::getIndex(e5);
	int b6_idx = Square::getIndex(b6);
	int b7_idx = Square::getIndex(b7);
	int a8_idx = Square::getIndex(a8);
	
	
	REQUIRE(getEarlygameWeights(PAWN,a1_idx)==getEarlygameWeights(PAWN,a8_idx,true));
	REQUIRE(getEarlygameWeights(PAWN,a2_idx,false)==getEarlygameWeights(PAWN,a7_idx,true));
	REQUIRE(getEarlygameWeights(PAWN,b3_idx)==getEarlygameWeights(PAWN,b6_idx,true));
	REQUIRE(getEarlygameWeights(PAWN,e4_idx,false)==getEarlygameWeights(PAWN,d5_idx,true));
	
	REQUIRE(getEarlygameWeights(KNIGHT,a1_idx,false)==getEarlygameWeights(KNIGHT,a8_idx,true));
	REQUIRE(getEarlygameWeights(KNIGHT,a2_idx,false)==getEarlygameWeights(KNIGHT,a7_idx,true));
	REQUIRE(getEarlygameWeights(KNIGHT,b3_idx,false)==getEarlygameWeights(KNIGHT,b6_idx,true));
	REQUIRE(getEarlygameWeights(KNIGHT,e4_idx,false)==getEarlygameWeights(KNIGHT,d5_idx,true));
	
	REQUIRE(getEarlygameWeights(BISHOP,a1_idx,false)==getEarlygameWeights(BISHOP,a8_idx,true));
	REQUIRE(getEarlygameWeights(BISHOP,a2_idx,false)==getEarlygameWeights(BISHOP,a7_idx,true));
	REQUIRE(getEarlygameWeights(BISHOP,b3_idx,false)==getEarlygameWeights(BISHOP,b6_idx,true));
	REQUIRE(getEarlygameWeights(BISHOP,e4_idx,false)==getEarlygameWeights(BISHOP,d5_idx,true));
	
	REQUIRE(getEarlygameWeights(ROOK,a1_idx,false)==getEarlygameWeights(ROOK,a8_idx,true));
	REQUIRE(getEarlygameWeights(ROOK,a2_idx,false)==getEarlygameWeights(ROOK,a7_idx,true));
	REQUIRE(getEarlygameWeights(ROOK,b3_idx,false)==getEarlygameWeights(ROOK,b6_idx,true));
	REQUIRE(getEarlygameWeights(ROOK,e4_idx,false)==getEarlygameWeights(ROOK,d5_idx,true));
	
	REQUIRE(getEarlygameWeights(QUEEN,a1_idx,false)==getEarlygameWeights(QUEEN,a8_idx,true));
	REQUIRE(getEarlygameWeights(QUEEN,a2_idx,false)==getEarlygameWeights(QUEEN,a7_idx,true));
	REQUIRE(getEarlygameWeights(QUEEN,b3_idx,false)==getEarlygameWeights(QUEEN,b6_idx,true));
	REQUIRE(getEarlygameWeights(QUEEN,e4_idx,false)==getEarlygameWeights(QUEEN,d5_idx,true));
	
	REQUIRE(getEarlygameWeights(KING,a1_idx,false)==getEarlygameWeights(KING,a8_idx,true));
	REQUIRE(getEarlygameWeights(KING,a2_idx,false)==getEarlygameWeights(KING,a7_idx,true));
	REQUIRE(getEarlygameWeights(KING,b3_idx,false)==getEarlygameWeights(KING,b6_idx,true));
	REQUIRE(getEarlygameWeights(KING,e4_idx,false)==getEarlygameWeights(KING,d5_idx,true));
	
	REQUIRE(getEarlygameWeights(PAWN,a1_idx,true)==getEarlygameWeights(PAWN,a8_idx,false));
	REQUIRE(getEarlygameWeights(PAWN,a2_idx,true)==getEarlygameWeights(PAWN,a7_idx,false));
	REQUIRE(getEarlygameWeights(PAWN,b3_idx,true)==getEarlygameWeights(PAWN,b6_idx,false));
	REQUIRE(getEarlygameWeights(PAWN,e4_idx,true)==getEarlygameWeights(PAWN,d5_idx,false));
	
	REQUIRE(getEarlygameWeights(KNIGHT,a1_idx,true)==getEarlygameWeights(KNIGHT,a8_idx,false));
	REQUIRE(getEarlygameWeights(KNIGHT,a2_idx,true)==getEarlygameWeights(KNIGHT,a7_idx,false));
	REQUIRE(getEarlygameWeights(KNIGHT,b3_idx,true)==getEarlygameWeights(KNIGHT,b6_idx,false));
	REQUIRE(getEarlygameWeights(KNIGHT,e4_idx,true)==getEarlygameWeights(KNIGHT,d5_idx,false));
	
	REQUIRE(getEarlygameWeights(BISHOP,a1_idx,true)==getEarlygameWeights(BISHOP,a8_idx,false));
	REQUIRE(getEarlygameWeights(BISHOP,a2_idx,true)==getEarlygameWeights(BISHOP,a7_idx,false));
	REQUIRE(getEarlygameWeights(BISHOP,b3_idx,true)==getEarlygameWeights(BISHOP,b6_idx,false));
	REQUIRE(getEarlygameWeights(BISHOP,e4_idx,true)==getEarlygameWeights(BISHOP,d5_idx,false));
	
	REQUIRE(getEarlygameWeights(ROOK,a1_idx,true)==getEarlygameWeights(ROOK,a8_idx,false));
	REQUIRE(getEarlygameWeights(ROOK,a2_idx,true)==getEarlygameWeights(ROOK,a7_idx,false));
	REQUIRE(getEarlygameWeights(ROOK,b3_idx,true)==getEarlygameWeights(ROOK,b6_idx,false));
	REQUIRE(getEarlygameWeights(ROOK,e4_idx,true)==getEarlygameWeights(ROOK,d5_idx,false));
	
	REQUIRE(getEarlygameWeights(QUEEN,a1_idx,true)==getEarlygameWeights(QUEEN,a8_idx,false));
	REQUIRE(getEarlygameWeights(QUEEN,a2_idx,true)==getEarlygameWeights(QUEEN,a7_idx,false));
	REQUIRE(getEarlygameWeights(QUEEN,b3_idx,true)==getEarlygameWeights(QUEEN,b6_idx,false));
	REQUIRE(getEarlygameWeights(QUEEN,e4_idx,true)==getEarlygameWeights(QUEEN,d5_idx,false));
	
	REQUIRE(getEarlygameWeights(KING,a1_idx,true)==getEarlygameWeights(KING,a8_idx,false));
	REQUIRE(getEarlygameWeights(KING,a2_idx,true)==getEarlygameWeights(KING,a7_idx,false));
	REQUIRE(getEarlygameWeights(KING,b3_idx,true)==getEarlygameWeights(KING,b6_idx,false));
	REQUIRE(getEarlygameWeights(KING,e4_idx,true)==getEarlygameWeights(KING,d5_idx,false));
}