#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include "ChessEngine.h"
#include "Weights.h"

#include <iostream>

using namespace ChessCore;
using namespace ChessCore::Piece;


TEST_CASE("Symmetric weight mapping white:black", "[EvaluationTest]") {
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
	int a7_idx = Square::getIndex(a7);
	int a8_idx = Square::getIndex(a8);
	
	
	REQUIRE(getWhiteEarlygameWeight(PAWN,a1_idx)==getBlackEarlygameWeight(PAWN,a8_idx));
	REQUIRE(getWhiteEarlygameWeight(PAWN,a2_idx)==getBlackEarlygameWeight(PAWN,a7_idx));
	REQUIRE(getWhiteEarlygameWeight(PAWN,b3_idx)==getBlackEarlygameWeight(PAWN,b6_idx));
	REQUIRE(getWhiteEarlygameWeight(PAWN,e4_idx)==getBlackEarlygameWeight(PAWN,e5_idx));
	REQUIRE(getWhiteEarlygameWeight(KNIGHT,a1_idx)==getBlackEarlygameWeight(KNIGHT,a8_idx));
	REQUIRE(getWhiteEarlygameWeight(KNIGHT,a2_idx)==getBlackEarlygameWeight(KNIGHT,a7_idx));
	REQUIRE(getWhiteEarlygameWeight(KNIGHT,b3_idx)==getBlackEarlygameWeight(KNIGHT,b6_idx));
	REQUIRE(getWhiteEarlygameWeight(KNIGHT,e4_idx)==getBlackEarlygameWeight(KNIGHT,e5_idx));
	REQUIRE(getWhiteEarlygameWeight(BISHOP,a1_idx)==getBlackEarlygameWeight(BISHOP,a8_idx));
	REQUIRE(getWhiteEarlygameWeight(BISHOP,a2_idx)==getBlackEarlygameWeight(BISHOP,a7_idx));
	REQUIRE(getWhiteEarlygameWeight(BISHOP,b3_idx)==getBlackEarlygameWeight(BISHOP,b6_idx));
	REQUIRE(getWhiteEarlygameWeight(BISHOP,e4_idx)==getBlackEarlygameWeight(BISHOP,e5_idx));
	REQUIRE(getWhiteEarlygameWeight(ROOK,a1_idx)==getBlackEarlygameWeight(ROOK,a8_idx));
	REQUIRE(getWhiteEarlygameWeight(ROOK,a2_idx)==getBlackEarlygameWeight(ROOK,a7_idx));
	REQUIRE(getWhiteEarlygameWeight(ROOK,b3_idx)==getBlackEarlygameWeight(ROOK,b6_idx));
	REQUIRE(getWhiteEarlygameWeight(ROOK,e4_idx)==getBlackEarlygameWeight(ROOK,e5_idx));
	REQUIRE(getWhiteEarlygameWeight(QUEEN,a1_idx)==getBlackEarlygameWeight(QUEEN,a8_idx));
	REQUIRE(getWhiteEarlygameWeight(QUEEN,a2_idx)==getBlackEarlygameWeight(QUEEN,a7_idx));
	REQUIRE(getWhiteEarlygameWeight(QUEEN,b3_idx)==getBlackEarlygameWeight(QUEEN,b6_idx));
	REQUIRE(getWhiteEarlygameWeight(QUEEN,e4_idx)==getBlackEarlygameWeight(QUEEN,e5_idx));
	REQUIRE(getWhiteEarlygameWeight(KING,a1_idx)==getBlackEarlygameWeight(KING,a8_idx));
	REQUIRE(getWhiteEarlygameWeight(KING,a2_idx)==getBlackEarlygameWeight(KING,a7_idx));
	REQUIRE(getWhiteEarlygameWeight(KING,b3_idx)==getBlackEarlygameWeight(KING,b6_idx));
	REQUIRE(getWhiteEarlygameWeight(KING,e4_idx)==getBlackEarlygameWeight(KING,e5_idx));
	
	REQUIRE(getWhiteEndgameWeight(PAWN,a1_idx)==getBlackEndgameWeight(PAWN,a8_idx));
	REQUIRE(getWhiteEndgameWeight(PAWN,a2_idx)==getBlackEndgameWeight(PAWN,a7_idx));
	REQUIRE(getWhiteEndgameWeight(PAWN,b3_idx)==getBlackEndgameWeight(PAWN,b6_idx));
	REQUIRE(getWhiteEndgameWeight(PAWN,e4_idx)==getBlackEndgameWeight(PAWN,e5_idx));
	REQUIRE(getWhiteEndgameWeight(KNIGHT,a1_idx)==getBlackEndgameWeight(KNIGHT,a8_idx));
	REQUIRE(getWhiteEndgameWeight(KNIGHT,a2_idx)==getBlackEndgameWeight(KNIGHT,a7_idx));
	REQUIRE(getWhiteEndgameWeight(KNIGHT,b3_idx)==getBlackEndgameWeight(KNIGHT,b6_idx));
	REQUIRE(getWhiteEndgameWeight(KNIGHT,e4_idx)==getBlackEndgameWeight(KNIGHT,e5_idx));
	REQUIRE(getWhiteEndgameWeight(BISHOP,a1_idx)==getBlackEndgameWeight(BISHOP,a8_idx));
	REQUIRE(getWhiteEndgameWeight(BISHOP,a2_idx)==getBlackEndgameWeight(BISHOP,a7_idx));
	REQUIRE(getWhiteEndgameWeight(BISHOP,b3_idx)==getBlackEndgameWeight(BISHOP,b6_idx));
	REQUIRE(getWhiteEndgameWeight(BISHOP,e4_idx)==getBlackEndgameWeight(BISHOP,e5_idx));
	REQUIRE(getWhiteEndgameWeight(ROOK,a1_idx)==getBlackEndgameWeight(ROOK,a8_idx));
	REQUIRE(getWhiteEndgameWeight(ROOK,a2_idx)==getBlackEndgameWeight(ROOK,a7_idx));
	REQUIRE(getWhiteEndgameWeight(ROOK,b3_idx)==getBlackEndgameWeight(ROOK,b6_idx));
	REQUIRE(getWhiteEndgameWeight(ROOK,e4_idx)==getBlackEndgameWeight(ROOK,e5_idx));
	REQUIRE(getWhiteEndgameWeight(QUEEN,a1_idx)==getBlackEndgameWeight(QUEEN,a8_idx));
	REQUIRE(getWhiteEndgameWeight(QUEEN,a2_idx)==getBlackEndgameWeight(QUEEN,a7_idx));
	REQUIRE(getWhiteEndgameWeight(QUEEN,b3_idx)==getBlackEndgameWeight(QUEEN,b6_idx));
	REQUIRE(getWhiteEndgameWeight(QUEEN,e4_idx)==getBlackEndgameWeight(QUEEN,e5_idx));
	REQUIRE(getWhiteEndgameWeight(KING,a1_idx)==getBlackEndgameWeight(KING,a8_idx));
	REQUIRE(getWhiteEndgameWeight(KING,a2_idx)==getBlackEndgameWeight(KING,a7_idx));
	REQUIRE(getWhiteEndgameWeight(KING,b3_idx)==getBlackEndgameWeight(KING,b6_idx));
	REQUIRE(getWhiteEndgameWeight(KING,e4_idx)==getBlackEndgameWeight(KING,e5_idx));
	
	
	REQUIRE(getBlackEarlygameWeight(PAWN,a1_idx)==getWhiteEarlygameWeight(PAWN,a8_idx));
	REQUIRE(getBlackEarlygameWeight(PAWN,a2_idx)==getWhiteEarlygameWeight(PAWN,a7_idx));
	REQUIRE(getBlackEarlygameWeight(PAWN,b3_idx)==getWhiteEarlygameWeight(PAWN,b6_idx));
	REQUIRE(getBlackEarlygameWeight(PAWN,e4_idx)==getWhiteEarlygameWeight(PAWN,e5_idx));
	REQUIRE(getBlackEarlygameWeight(KNIGHT,a1_idx)==getWhiteEarlygameWeight(KNIGHT,a8_idx));
	REQUIRE(getBlackEarlygameWeight(KNIGHT,a2_idx)==getWhiteEarlygameWeight(KNIGHT,a7_idx));
	REQUIRE(getBlackEarlygameWeight(KNIGHT,b3_idx)==getWhiteEarlygameWeight(KNIGHT,b6_idx));
	REQUIRE(getBlackEarlygameWeight(KNIGHT,e4_idx)==getWhiteEarlygameWeight(KNIGHT,e5_idx));
	REQUIRE(getBlackEarlygameWeight(BISHOP,a1_idx)==getWhiteEarlygameWeight(BISHOP,a8_idx));
	REQUIRE(getBlackEarlygameWeight(BISHOP,a2_idx)==getWhiteEarlygameWeight(BISHOP,a7_idx));
	REQUIRE(getBlackEarlygameWeight(BISHOP,b3_idx)==getWhiteEarlygameWeight(BISHOP,b6_idx));
	REQUIRE(getBlackEarlygameWeight(BISHOP,e4_idx)==getWhiteEarlygameWeight(BISHOP,e5_idx));
	REQUIRE(getBlackEarlygameWeight(ROOK,a1_idx)==getWhiteEarlygameWeight(ROOK,a8_idx));
	REQUIRE(getBlackEarlygameWeight(ROOK,a2_idx)==getWhiteEarlygameWeight(ROOK,a7_idx));
	REQUIRE(getBlackEarlygameWeight(ROOK,b3_idx)==getWhiteEarlygameWeight(ROOK,b6_idx));
	REQUIRE(getBlackEarlygameWeight(ROOK,e4_idx)==getWhiteEarlygameWeight(ROOK,e5_idx));
	REQUIRE(getBlackEarlygameWeight(QUEEN,a1_idx)==getWhiteEarlygameWeight(QUEEN,a8_idx));
	REQUIRE(getBlackEarlygameWeight(QUEEN,a2_idx)==getWhiteEarlygameWeight(QUEEN,a7_idx));
	REQUIRE(getBlackEarlygameWeight(QUEEN,b3_idx)==getWhiteEarlygameWeight(QUEEN,b6_idx));
	REQUIRE(getBlackEarlygameWeight(QUEEN,e4_idx)==getWhiteEarlygameWeight(QUEEN,e5_idx));
	REQUIRE(getBlackEarlygameWeight(KING,a1_idx)==getWhiteEarlygameWeight(KING,a8_idx));
	REQUIRE(getBlackEarlygameWeight(KING,a2_idx)==getWhiteEarlygameWeight(KING,a7_idx));
	REQUIRE(getBlackEarlygameWeight(KING,b3_idx)==getWhiteEarlygameWeight(KING,b6_idx));
	REQUIRE(getBlackEarlygameWeight(KING,e4_idx)==getWhiteEarlygameWeight(KING,e5_idx));
	
	REQUIRE(getBlackEndgameWeight(PAWN,a1_idx)==getWhiteEndgameWeight(PAWN,a8_idx));
	REQUIRE(getBlackEndgameWeight(PAWN,a2_idx)==getWhiteEndgameWeight(PAWN,a7_idx));
	REQUIRE(getBlackEndgameWeight(PAWN,b3_idx)==getWhiteEndgameWeight(PAWN,b6_idx));
	REQUIRE(getBlackEndgameWeight(PAWN,e4_idx)==getWhiteEndgameWeight(PAWN,e5_idx));
	REQUIRE(getBlackEndgameWeight(KNIGHT,a1_idx)==getWhiteEndgameWeight(KNIGHT,a8_idx));
	REQUIRE(getBlackEndgameWeight(KNIGHT,a2_idx)==getWhiteEndgameWeight(KNIGHT,a7_idx));
	REQUIRE(getBlackEndgameWeight(KNIGHT,b3_idx)==getWhiteEndgameWeight(KNIGHT,b6_idx));
	REQUIRE(getBlackEndgameWeight(KNIGHT,e4_idx)==getWhiteEndgameWeight(KNIGHT,e5_idx));
	REQUIRE(getBlackEndgameWeight(BISHOP,a1_idx)==getWhiteEndgameWeight(BISHOP,a8_idx));
	REQUIRE(getBlackEndgameWeight(BISHOP,a2_idx)==getWhiteEndgameWeight(BISHOP,a7_idx));
	REQUIRE(getBlackEndgameWeight(BISHOP,b3_idx)==getWhiteEndgameWeight(BISHOP,b6_idx));
	REQUIRE(getBlackEndgameWeight(BISHOP,e4_idx)==getWhiteEndgameWeight(BISHOP,e5_idx));
	REQUIRE(getBlackEndgameWeight(ROOK,a1_idx)==getWhiteEndgameWeight(ROOK,a8_idx));
	REQUIRE(getBlackEndgameWeight(ROOK,a2_idx)==getWhiteEndgameWeight(ROOK,a7_idx));
	REQUIRE(getBlackEndgameWeight(ROOK,b3_idx)==getWhiteEndgameWeight(ROOK,b6_idx));
	REQUIRE(getBlackEndgameWeight(ROOK,e4_idx)==getWhiteEndgameWeight(ROOK,e5_idx));
	REQUIRE(getBlackEndgameWeight(QUEEN,a1_idx)==getWhiteEndgameWeight(QUEEN,a8_idx));
	REQUIRE(getBlackEndgameWeight(QUEEN,a2_idx)==getWhiteEndgameWeight(QUEEN,a7_idx));
	REQUIRE(getBlackEndgameWeight(QUEEN,b3_idx)==getWhiteEndgameWeight(QUEEN,b6_idx));
	REQUIRE(getBlackEndgameWeight(QUEEN,e4_idx)==getWhiteEndgameWeight(QUEEN,e5_idx));
	REQUIRE(getBlackEndgameWeight(KING,a1_idx)==getWhiteEndgameWeight(KING,a8_idx));
	REQUIRE(getBlackEndgameWeight(KING,a2_idx)==getWhiteEndgameWeight(KING,a7_idx));
	REQUIRE(getBlackEndgameWeight(KING,b3_idx)==getWhiteEndgameWeight(KING,b6_idx));
	REQUIRE(getBlackEndgameWeight(KING,e4_idx)==getWhiteEndgameWeight(KING,e5_idx));
}

TEST_CASE("Basic evaluation assumptions", "[EvaluationTest]") {
	ChessEngine eng;
	eng.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	int evaluation0 = eng.evaluateInternalState();
	
	// initial position is even
	REQUIRE(evaluation0 == 0);
	
	
	eng.setFEN("rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1");
	int evaluationD3 = eng.evaluateInternalState();
	
	// black is behind after first move
	REQUIRE(evaluationD3 < evaluation0);
	
	eng.setFEN("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1");
	int evaluationD4 = eng.evaluateInternalState();
	
	// black is worse off after d4 than d3
	REQUIRE(evaluationD4 < evaluation0);
	REQUIRE(evaluationD4 < evaluationD3);
	
	eng.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R1BQKBNR w KQkq - 0 1");
	int evaluationMissingKnight = eng.evaluateInternalState();
	
	// white is behind when starting without a knight
	REQUIRE(evaluationMissingKnight < evaluation0);
}

TEST_CASE("King safety", "[EvaluationTest]") {
	ChessEngine eng;
	eng.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	int evaluation0 = eng.evaluateInternalState();
	
	// initial position is even
	REQUIRE(evaluation0 == 0);
	
	
	eng.setFEN("rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1");
	int evaluationD3 = eng.evaluateInternalState();
	
	// black is behind after first move
	REQUIRE(evaluationD3 < evaluation0);
	
	eng.setFEN("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1");
	int evaluationD4 = eng.evaluateInternalState();
	
	// black is worse off after d4 than d3
	REQUIRE(evaluationD4 < evaluation0);
	REQUIRE(evaluationD4 < evaluationD3);
	
	eng.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R1BQKBNR w KQkq - 0 1");
	int evaluationMissingKnight = eng.evaluateInternalState();
	
	// white is behind when starting without a knight
	REQUIRE(evaluationMissingKnight < evaluation0);
}