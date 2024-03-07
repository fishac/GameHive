#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "ChessCore.h"

using namespace ChessCore;
using namespace ChessCore::Color;
using namespace ChessCore::Piece;

TEST_CASE("FIRST 5 PLIES 1. e4 e5 2. bb5 nf6 3. bd7 ...", "[BoardStateFunctional]") {
	// Set up board
	BoardState bs;
	// 1. e4
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 20);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a2"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a2"),Square::getSquare("a4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f2"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f2"),Square::getSquare("f4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g2"),Square::getSquare("g3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g2"),Square::getSquare("g4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h2"),Square::getSquare("h3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h2"),Square::getSquare("h4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("h3")));
	
	REQUIRE(bs.makeMove(Square::getSquare("e2"),Square::getSquare("e4")));
	/*
	std::vector<Square_t> wpawns = bs.getWhitePawnSquares();
	REQUIRE(!Vector::squareInVector(wpawns,Square::getSquare("e2")));
	REQUIRE(Vector::squareInVector(wpawns,Square::getSquare("e4")));
	REQUIRE(wpawns.size() == 8);
	*/
	
	// 1. ... e5
	REQUIRE(bs.getTurnColor() == BLACK);
	legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 20);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a7"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a7"),Square::getSquare("a5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b7"),Square::getSquare("b6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b7"),Square::getSquare("b5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c7"),Square::getSquare("c6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c7"),Square::getSquare("c5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f7"),Square::getSquare("f6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f7"),Square::getSquare("f5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g7"),Square::getSquare("g6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g7"),Square::getSquare("g5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h7"),Square::getSquare("h6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h7"),Square::getSquare("h5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("c6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("f6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("h6")));
	
	REQUIRE(bs.makeMove(Square::getSquare("e7"),Square::getSquare("e5")));
	/*
	std::vector<Square_t> bpawns = bs.getBlackPawnSquares();
	REQUIRE(!Vector::squareInVector(bpawns,Square::getSquare("e7")));
	REQUIRE(Vector::squareInVector(bpawns,Square::getSquare("e5")));
	REQUIRE(bpawns.size() == 8);
	*/
	
	// 2. bb5 
	legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 29);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a2"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a2"),Square::getSquare("a4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f2"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f2"),Square::getSquare("f4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g2"),Square::getSquare("g3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g2"),Square::getSquare("g4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h2"),Square::getSquare("h3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h2"),Square::getSquare("h4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("h3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("e2")));
	// White queen opened up
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("e2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("g4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("h5")));
	// White bishop on f1 opened up
	REQUIRE(bs.isMoveLegal(Square::getSquare("f1"),Square::getSquare("e2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f1"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f1"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f1"),Square::getSquare("b5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f1"),Square::getSquare("a6")));
	// King can move
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("e2")));
	
	REQUIRE(bs.makeMove(Square::getSquare("f1"),Square::getSquare("b5")));
	/*
	std::vector<Square_t> wbishops = bs.getWhiteBishopSquares();
	REQUIRE(!Vector::squareInVector(wbishops,Square::getSquare("f1")));
	REQUIRE(Vector::squareInVector(wbishops,Square::getSquare("b5")));
	REQUIRE(wbishops.size() == 2);
	*/
	
	// 2. ... nf6
	legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 26);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a7"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a7"),Square::getSquare("a5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b7"),Square::getSquare("b6")));
	// Can't move to square bishop is on.
	REQUIRE(!bs.isMoveLegal(Square::getSquare("b7"),Square::getSquare("b5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c7"),Square::getSquare("c6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c7"),Square::getSquare("c5")));
	// d7 pawn pinned
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f7"),Square::getSquare("f6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f7"),Square::getSquare("f5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g7"),Square::getSquare("g6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g7"),Square::getSquare("g5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h7"),Square::getSquare("h6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h7"),Square::getSquare("h5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("c6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("f6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("h6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("e7")));
	// Black queen opened up
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("e7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("f6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("g5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("h4")));
	// Black bishop f8 opened up
	REQUIRE(bs.isMoveLegal(Square::getSquare("f8"),Square::getSquare("e7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f8"),Square::getSquare("d6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f8"),Square::getSquare("c5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f8"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f8"),Square::getSquare("a3")));
	// King can move
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("e7")));
	
	REQUIRE(bs.makeMove(Square::getSquare("g8"),Square::getSquare("f6")));
	/*
	std::vector<Square_t> bknights = bs.getBlackKnightSquares();
	REQUIRE(!Vector::squareInVector(bknights,Square::getSquare("g8")));
	REQUIRE(Vector::squareInVector(bknights,Square::getSquare("f6")));
	REQUIRE(bknights.size() == 2);
	*/
	
	// 3. bd7 
	legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 33);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a2"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a2"),Square::getSquare("a4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f2"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f2"),Square::getSquare("f4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g2"),Square::getSquare("g3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g2"),Square::getSquare("g4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h2"),Square::getSquare("h3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h2"),Square::getSquare("h4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("h3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("e2")));
	// White queen opened up
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("e2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("g4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d1"),Square::getSquare("h5")));
	// White bishop on f1 opened up
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("a4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("c6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("e2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("f1")));
	// King can move
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("e2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("f1")));
	
	REQUIRE(bs.makeMove(Square::getSquare("b5"),Square::getSquare("d7")));
	/*
	wbishops = bs.getWhiteBishopSquares();
	bpawns = bs.getBlackPawnSquares();
	REQUIRE(!Vector::squareInVector(wbishops,Square::getSquare("b5")));
	REQUIRE(Vector::squareInVector(wbishops,Square::getSquare("d7")));
	REQUIRE(!Vector::squareInVector(bpawns,Square::getSquare("d7")));
	REQUIRE(wbishops.size() == 2);
	REQUIRE(bpawns.size() == 7);
	*/
	REQUIRE(bs.getCheckStatus());
	
	// Check black legal moves 
	legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 6);
	REQUIRE(bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c8"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("e7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("f6"),Square::getSquare("d7")));
}

TEST_CASE("BISHOP PINNING QUEEN", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/8/4b3/1n6/2Q5/8/K7 w - - 0 1";
	BoardState bs(FEN);
	
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 5);
	// Knight attacking a2
	REQUIRE(!bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("a2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("e5")));
}

TEST_CASE("BISHOP PINNING BISHOP", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/8/4b3/1n6/2B5/8/K7 w - - 0 1";
	BoardState bs(FEN);
	
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 5);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("e5")));
}

TEST_CASE("BISHOP PINNING PAWN", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/8/4b3/1n6/2P5/8/K7 w - - 0 1";
	BoardState bs(FEN);
	
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 2);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b1")));
}

TEST_CASE("BISHOP PINNING KNIGHT", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/8/1p1pb3/8/2N5/8/K7 w - - 0 1";
	BoardState bs(FEN);
	
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 3);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b1")));
}

TEST_CASE("BISHOP PINNING ROOK", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/8/4b3/2q5/2R5/8/K7 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 2);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a1"),Square::getSquare("b1")));
}

TEST_CASE("ROOK PINNING ROOK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/2r5/8/2R1r3/8/2K5 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 8);
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c5")));
}

TEST_CASE("ROOK PINNING QUEEN", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/2r5/8/2Q1r3/8/2K5 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 8);
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c5")));
}

TEST_CASE("ROOK PINNING PAWN", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/2r5/1b1b4/2P5/8/2K5 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 6);
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c3"),Square::getSquare("c4")));
}

TEST_CASE("ROOK PINNING PAWN TWO SQUARES", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/2r5/8/1b1b4/2P5/2K5 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 6);
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c2"),Square::getSquare("c4")));
}

TEST_CASE("ROOK PINNING KNIGHT", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/1pr5/4p3/2N5/8/2K5 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 5);
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
}

TEST_CASE("ROOK PINNING BISHOP", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/2r5/8/2B5/8/2K5 w - - 0 1";
	BoardState bs(FEN);
		
	std::vector<Move> legalMoves = bs.getLegalMoves();
	REQUIRE(legalMoves.size() == 5);
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
}

TEST_CASE("KING PROPER COVERAGE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/8/8/1np5/1NKB4 w - - 0 1";
	BoardState bs(FEN);

	REQUIRE(!bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d2")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("d1")));
}

TEST_CASE("WHITE PAWN PROPER COVERAGE NO BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/8/2n5/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("e3")));
}

TEST_CASE("WHITE PAWN PROPER COVERAGE WHITE TWO BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/3N4/2n5/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("e3")));
}

TEST_CASE("WHITE PAWN PROPER COVERAGE WHITE FORWARD BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/8/2nN4/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("e3")));
}

TEST_CASE("WHITE PAWN PROPER COVERAGE WHITE TWO FORWARD BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/3n4/2nN4/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("e3")));
}

TEST_CASE("WHITE PAWN PROPER COVERAGE BLACK TWO BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/3b4/2n5/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("e3")));
}

TEST_CASE("WHITE PAWN PROPER COVERAGE BLACK FORWARD BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/8/2nn4/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("d4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d2"),Square::getSquare("e3")));
}

TEST_CASE("BLACK PAWN PROPER COVERAGE NO BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/2N5/8/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("c6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("e6")));
}

TEST_CASE("BLACK PAWN PROPER COVERAGE WHITE TWO BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/2N5/3N4/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("c6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("e6")));
}

TEST_CASE("BLACK PAWN PROPER COVERAGE WHITE FORWARD BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/2NN4/8/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("c6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("e6")));
}

TEST_CASE("BLACK PAWN PROPER COVERAGE WHITE TWO FORWARD BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/2NN4/3N4/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("c6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("e6")));
}

TEST_CASE("BLACK PAWN PROPER COVERAGE BLACK TWO BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/2N5/3n4/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("c6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("e6")));
}

TEST_CASE("BLACK PAWN PROPER COVERAGE BLACK FORWARD BLOCK STARTING RANK", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/2Nn4/3n4/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("d5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("c6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d7"),Square::getSquare("e6")));
}

TEST_CASE("PROPER KNIGHT COVERAGE", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/2b5/1b6/3N4/1B6/2B5/3K4 w - - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f5")));
}

TEST_CASE("PROPER BISHOP COVERAGE", "[BoardStateFunctional]") {
	std::string FEN = "3k4/8/5p2/2n5/3B4/2N5/5P2/3K4 w - - 0 1";
	BoardState bs(FEN);
	
	// Normal moves
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f6")));

	// Ensure no legal moves past pieces
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b2")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("g7")));
}

TEST_CASE("PROPER ROOK COVERAGE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/3n4/1p1RP3/8/3P4/7K w - - 0 1";
	BoardState bs(FEN);
		
	// Normal moves
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d2")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d5")));

	// Ensure no legal moves past pieces
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("a4")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f4")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d6")));
}

TEST_CASE("PROPER QUEEN COVERAGE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/5p2/2nn4/1p1QP3/8/3P1P2/7K w - - 0 1";
	BoardState bs(FEN);
		
	// Bishop moves
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f6")));
	
	// Rook moves
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("c4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d2")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("e4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d5")));

	// Ensure no legal moves past pieces
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("a4")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("f4")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("d6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("b6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("g7")));
}

TEST_CASE("WHITE CASTLING KINGSIDE", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/8/8/8/8/4K2R w KQ - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.makeMove(Square::getSquare("e1"),Square::getSquare("g1")));
	//REQUIRE(bs.getWhiteKingSquare() == Square::getSquare("g1"));
	
	//std::vector<Square_t> wrooks = bs.getWhiteRookSquares();
	//REQUIRE(Vector::squareInVector(wrooks,Square::getSquare("f1")));
}

TEST_CASE("BLACK CASTLING KINGSIDE", "[BoardStateFunctional]") {
	std::string FEN = "4k2r/8/8/8/8/8/8/6K1 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.makeMove(Square::getSquare("e8"),Square::getSquare("g8")));
	//REQUIRE(bs.getBlackKingSquare() == Square::getSquare("g8"));
	
	//std::vector<Square_t> brooks = bs.getBlackRookSquares();
	//REQUIRE(Vector::squareInVector(brooks,Square::getSquare("f8")));
}

TEST_CASE("WHITE CASTLING QUEENSIDE", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/8/8/8/8/R3K3 w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.makeMove(Square::getSquare("e1"),Square::getSquare("c1")));
	//REQUIRE(bs.getWhiteKingSquare() == Square::getSquare("c1"));
	
	//std::vector<Square_t> wrooks = bs.getWhiteRookSquares();
	//REQUIRE(Vector::squareInVector(wrooks,Square::getSquare("d1")));
}

TEST_CASE("BLACK CASTLING QUEENSIDE", "[BoardStateFunctional]") {
	std::string FEN = "r3k3/8/8/8/8/8/8/6K1 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.makeMove(Square::getSquare("e8"),Square::getSquare("c8")));
	//REQUIRE(bs.getBlackKingSquare() == Square::getSquare("c8"));
	
	//std::vector<Square_t> brooks = bs.getBlackRookSquares();
	//REQUIRE(Vector::squareInVector(brooks,Square::getSquare("d8")));
}

TEST_CASE("WHITE CANT CASTLE CROSS CHECK", "[BoardStateFunctional]") {
	std::string FEN = "1k1r1r2/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("BLACK CANT CASTLE CROSS CHECK", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/1K1R1R2 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("WHITE CANT CASTLE INTO CHECK", "[BoardStateFunctional]") {
	std::string FEN = "1kr3r1/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("BLACK CANT CASTLE INTO CHECK", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/1KR3R1 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("WHITE CAN CASTLE WITH OUTSIDE ATTACK", "[BoardStateFunctional]") {
	std::string FEN = "1rk5/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("BLACK CAN CASTLE WITH OUTSIDE ATTACK", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/1RK5 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("WHITE CAN CASTLE WITH ROOK ATTACKED", "[BoardStateFunctional]") {
	std::string FEN = "r1k4r/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("BLACK CAN CASTLE WITH ROOK ATTACKED", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/R1K4R b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("WHITE CANT CASTLE WITH BLOCKER 1/3", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/8/8/8/8/R2NKN1R w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("WHITE CANT CASTLE WITH BLOCKER 2/3", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/8/8/8/8/R1N1K1NR w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("WHITE CANT CASTLE WITH BLOCKER 3/3", "[BoardStateFunctional]") {
	std::string FEN = "6k1/8/8/8/8/8/8/RN2K1NR w KQ - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("g1")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e1"),Square::getSquare("c1")));
}

TEST_CASE("BLACK CANT CASTLE WITH BLOCKER 1/3", "[BoardStateFunctional]") {
	std::string FEN = "r2nkn1r/8/8/8/8/8/8/6K1 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("BLACK CANT CASTLE WITH BLOCKER 2/3", "[BoardStateFunctional]") {
	std::string FEN = "r1n1k1nr/8/8/8/8/8/8/6K1 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("BLACK CANT CASTLE WITH BLOCKER 3/3", "[BoardStateFunctional]") {
	std::string FEN = "rn2k1nr/8/8/8/8/8/8/6K1 b kq - 0 1";
	BoardState bs(FEN);
		
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("g8")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e8"),Square::getSquare("c8")));
}

TEST_CASE("WHITE EN PASSANT CAPTURE", "[BoardStateFunctional]") {
	std::string FEN = "8/1p6/8/k1P1r3/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	// White cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("h1"),Square::getSquare("h2")));
	// Black creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b7"),Square::getSquare("b5")));
	// White takes with en passant
	REQUIRE(bs.makeMove(Square::getSquare("c5"),Square::getSquare("b6")));
	// Ensure en passant occurred properly
	//std::vector<Square_t> wpawns = bs.getWhitePawnSquares();
	//std::vector<Square_t> bpawns = bs.getBlackPawnSquares();
	//REQUIRE(Vector::squareInVector(wpawns,Square::getSquare("b6")));
	//REQUIRE(!Vector::squareInVector(wpawns,Square::getSquare("c5")));
	//REQUIRE(!Vector::squareInVector(bpawns,Square::getSquare("b5")));
}

TEST_CASE("BLACK EN PASSANT CAPTURE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/K1p1R3/8/1P6/8 b - - 0 1";
	BoardState bs(FEN);
	
	// Black cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.makeMove(Square::getSquare("h8"),Square::getSquare("h7")));
	// White creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b2"),Square::getSquare("b4")));
	// Black takes with en passant
	REQUIRE(bs.makeMove(Square::getSquare("c4"),Square::getSquare("b3")));
	// Ensure en passant occurred properly
	//std::vector<Square_t> wpawns = bs.getWhitePawnSquares();
	//std::vector<Square_t> bpawns = bs.getBlackPawnSquares();
	//REQUIRE(Vector::squareInVector(bpawns,Square::getSquare("b3")));
	//REQUIRE(!Vector::squareInVector(bpawns,Square::getSquare("c4")));
	//REQUIRE(!Vector::squareInVector(wpawns,Square::getSquare("b4")));
}

TEST_CASE("WHITE EN PASSANT NO CAPTURE", "[BoardStateFunctional]") {
	std::string FEN = "8/1p6/8/k1P1r3/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	// White cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("h1"),Square::getSquare("h2")));
	// Black creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b7"),Square::getSquare("b5")));
	// White can en passant, makes random move instead
	REQUIRE(bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("h2"),Square::getSquare("h1")));
	// Black makes move, en passant not legal when blacks turn
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("e5"),Square::getSquare("f5")));
	// En passant no longer legal for white
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
}

TEST_CASE("BLACK EN PASSANT NO CAPTURE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/K1p1R3/8/1P6/8 b - - 0 1";
	BoardState bs(FEN);
	
	// Black cant en passant, makes random move 
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.makeMove(Square::getSquare("h8"),Square::getSquare("h7")));
	// White creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b2"),Square::getSquare("b4")));
	// Black can en passant, makes random move instead
	REQUIRE(bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.makeMove(Square::getSquare("h7"),Square::getSquare("h8")));
	// White makes move, en passant not legal when whites turn
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.makeMove(Square::getSquare("e4"),Square::getSquare("f4")));
	// En passant no longer legal
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
}

TEST_CASE("WHITE EN PASSANT TRICKY PIN 1/2", "[BoardStateFunctional]") {
	std::string FEN = "7k/1p6/8/K1P1r3/8/8/8/R7 w - - 0 1";
	BoardState bs(FEN);
	
	// White cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("a1"),Square::getSquare("a2")));
	// Black creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b7"),Square::getSquare("b5")));
	// White cant en passant because of pin
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("c6")));
}

TEST_CASE("WHITE EN PASSANT TRICKY PIN 2/2", "[BoardStateFunctional]") {
	std::string FEN = "7k/3p4/8/K1P1r3/8/8/8/R7 w - - 0 1";
	BoardState bs(FEN);
	
	// White cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("a1"),Square::getSquare("a2")));
	// Black creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("d7"),Square::getSquare("d5")));
	// White cant en passant because of pin
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("d6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("c6")));
}

TEST_CASE("BLACK EN PASSANT TRICKY PIN 1/2", "[BoardStateFunctional]") {
	std::string FEN = "r7/8/8/8/k1p1R3/8/1P6/7K b - - 0 1";
	BoardState bs(FEN);
	
	// Black cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.makeMove(Square::getSquare("a8"),Square::getSquare("a7")));
	// White creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b2"),Square::getSquare("b4")));
	// Black cant en passant because of pin
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("c3")));
}

TEST_CASE("BLACK EN PASSANT TRICKY PIN 2/2", "[BoardStateFunctional]") {
	std::string FEN = "r7/8/8/8/k1p1R3/8/3P4/7K b - - 0 1";
	BoardState bs(FEN);
	
	// Black cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.makeMove(Square::getSquare("a8"),Square::getSquare("a7")));
	// White creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("d2"),Square::getSquare("d4")));
	// Black cant en passant because of pin
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("d3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("c3")));
}

TEST_CASE("CHECK", "[BoardStateFunctional]") {
	std::string FEN = "k6r/8/8/8/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
}

TEST_CASE("CHECKMATE", "[BoardStateFunctional]") {
	std::string FEN = "k5rr/8/8/8/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getCheckStatus());
	REQUIRE(bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getLegalMoves().empty()); 
}

TEST_CASE("STALEMATE EMPTY", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/8/8/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(bs.getStalemateStatus());
}

TEST_CASE("STALEMATE NO MOVES", "[BoardStateFunctional]") {
	std::string FEN = "k5r1/8/8/8/8/8/r7/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(bs.getStalemateStatus());
	REQUIRE(bs.getLegalMoves().empty()); 
}

TEST_CASE("MOVE MAKES CHECK", "[BoardStateFunctional]") {
	std::string FEN = "k5r1/8/8/8/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.makeMove(Square::getSquare("g8"),Square::getSquare("h8")));
	REQUIRE(bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 2);
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g2")));
}

TEST_CASE("MOVE MAKES CHECKMATE", "[BoardStateFunctional]") {
	std::string FEN = "kr6/6r1/8/8/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.makeMove(Square::getSquare("b8"),Square::getSquare("h8")));
	REQUIRE(bs.getCheckStatus());
	REQUIRE(bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 0);
}

TEST_CASE("MOVE MAKES STALEMATE", "[BoardStateFunctional]") {
	std::string FEN = "kr4r1/8/8/8/8/8/8/7K b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.makeMove(Square::getSquare("b8"),Square::getSquare("b2")));
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 0);
}

TEST_CASE("CAN BLOCK CHECK", "[BoardStateFunctional]") {
	std::string FEN = "k6r/8/8/8/6N1/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 4);
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g4"),Square::getSquare("h2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g4"),Square::getSquare("h6")));
	REQUIRE(bs.makeMove(Square::getSquare("g4"),Square::getSquare("h2")));
	
	REQUIRE(bs.makeMove(Square::getSquare("h8"),Square::getSquare("h7")));
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 2);
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g2")));
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
}

TEST_CASE("CAN TAKE CHECKING PIECE WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "k6r/8/8/8/3Q4/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 4);
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g2")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("h8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d4"),Square::getSquare("h4")));
	REQUIRE(bs.makeMove(Square::getSquare("d4"),Square::getSquare("h8")));
	
	//std::vector<Square_t> brooks = bs.getBlackRookSquares();
	//REQUIRE(brooks.empty());
	REQUIRE(bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 2);
	REQUIRE(bs.isMoveLegal(Square::getSquare("a8"),Square::getSquare("a7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a8"),Square::getSquare("b7")));
	REQUIRE(bs.makeMove(Square::getSquare("a8"),Square::getSquare("a7")));
	
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
}

TEST_CASE("WHITE MOVE KING LOSE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "1k6/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.getQueensideCastleRights(WHITE));
	REQUIRE(bs.makeMove(Square::getSquare("e1"),Square::getSquare("e2")));
	REQUIRE(!bs.getKingsideCastleRights(WHITE));
	REQUIRE(!bs.getQueensideCastleRights(WHITE));
}

TEST_CASE("WHITE MOVE KINGSIDE ROOK LOSE KINGSIDE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "1k6/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.getQueensideCastleRights(WHITE));
	REQUIRE(bs.makeMove(Square::getSquare("h1"),Square::getSquare("h2")));
	REQUIRE(!bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.getQueensideCastleRights(WHITE));
}

TEST_CASE("WHITE MOVE QUEENSIDE ROOK LOSE QUEENSIDE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "1k6/8/8/8/8/8/8/R3K2R w KQ - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.getQueensideCastleRights(WHITE));
	REQUIRE(bs.makeMove(Square::getSquare("a1"),Square::getSquare("a2")));
	REQUIRE(bs.getKingsideCastleRights(WHITE));
	REQUIRE(!bs.getQueensideCastleRights(WHITE));
}

TEST_CASE("BLACK MOVE KING LOSE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/1K6 b kq - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.makeMove(Square::getSquare("e8"),Square::getSquare("e7")));
	REQUIRE(!bs.getKingsideCastleRights(BLACK));
	REQUIRE(!bs.getQueensideCastleRights(BLACK));
}

TEST_CASE("BLACK MOVE KINGSIDE ROOK LOSE KINGSIDE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/1K6 b kq - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.makeMove(Square::getSquare("h8"),Square::getSquare("h7")));
	REQUIRE(!bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.getQueensideCastleRights(BLACK));
}

TEST_CASE("BLACK MOVE QUEENSIDE ROOK LOSE QUEENSIDE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "r3k2r/8/8/8/8/8/8/1K6 b kq - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(bs.makeMove(Square::getSquare("a8"),Square::getSquare("a7")));
	REQUIRE(bs.getKingsideCastleRights(BLACK));
	REQUIRE(!bs.getQueensideCastleRights(BLACK));
}

TEST_CASE("ROOK TAKEN LOSE CASTLE RIGHTS", "[BoardStateFunctional]") {
	std::string FEN = "1k6/8/8/8/8/8/7r/R3K2R b KQ - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.makeMove(Square::getSquare("h2"),Square::getSquare("h1")));
	
	REQUIRE(!bs.getKingsideCastleRights(WHITE));
	REQUIRE(bs.getQueensideCastleRights(WHITE));
}

TEST_CASE("WHITE PAWN MUST PROMOTE", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(!bs.makeMove(Square::getSquare("e7"),Square::getSquare("e8")));
}

TEST_CASE("WHITE CANT PROMOTE TO NOPIECE", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(!bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), NOPIECE));
}

TEST_CASE("WHITE CANT PROMOTE TO PAWN", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(!bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), PAWN));
}

TEST_CASE("WHITE CANT PROMOTE TO KING", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(!bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), KING));
}

TEST_CASE("WHITE CAN PROMOTE TO KNIGHT", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), KNIGHT));
	REQUIRE(!bs.getCheckStatus());
}

TEST_CASE("WHITE CAN PROMOTE TO KNIGHT WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "8/2k1P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), KNIGHT));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("WHITE CAN PROMOTE TO BISHOP", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), BISHOP));
	REQUIRE(!bs.getCheckStatus());
}

TEST_CASE("WHITE CAN PROMOTE TO BISHOP WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "8/3kP3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), BISHOP));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("WHITE CAN PROMOTE TO ROOK", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), ROOK));
	REQUIRE(!bs.getCheckStatus());
}

TEST_CASE("WHITE CAN PROMOTE TO ROOK WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "k7/4P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("e8"), ROOK));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("WHITE CAN TAKE TO PROMOTE", "[BoardStateFunctional]") {
	std::string FEN = "k4n2/4P3/8/8/8/p7/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e7"),Square::getSquare("f8"), ROOK));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("BLACK PAWN MUST PROMOTE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/K3p3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(!bs.makeMove(Square::getSquare("e2"),Square::getSquare("e1")));
}

TEST_CASE("BLACK CANT PROMOTE TO NOPIECE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/K3p3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(!bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), NOPIECE));
}

TEST_CASE("BLACK CANT PROMOTE TO PAWN", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/K3p3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(!bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), PAWN));
}

TEST_CASE("BLACK CANT PROMOTE TO KING", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/K3p3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(!bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), KING));
}

TEST_CASE("BLACK CAN PROMOTE TO KNIGHT", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/4p3/7K b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), KNIGHT));
	REQUIRE(!bs.getCheckStatus());
}

TEST_CASE("BLACK CAN PROMOTE TO KNIGHT WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/2K1p3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), KNIGHT));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("BLACK CAN PROMOTE TO BISHOP", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/4p3/7K b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), BISHOP));
	REQUIRE(!bs.getCheckStatus());
}

TEST_CASE("BLACK CAN PROMOTE TO BISHOP WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/3Kp3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), BISHOP));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("BLACK CAN PROMOTE TO ROOK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/K3p3/8 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), ROOK));
	REQUIRE(!bs.getCheckStatus());
}

TEST_CASE("BLACK CAN PROMOTE TO ROOK WITH CHECK", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/4p3/7K b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("e1"), ROOK));
	REQUIRE(bs.getCheckStatus());
}

TEST_CASE("BLACK CAN TAKE TO PROMOTE", "[BoardStateFunctional]") {
	std::string FEN = "7k/8/P7/8/8/8/4p3/K4N2 b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("e1")));
	REQUIRE(bs.makeMoveAndPromote(Square::getSquare("e2"),Square::getSquare("f1"), ROOK));
	REQUIRE(bs.getCheckStatus());
}

/*
TEST_CASE("BOARD STATE UNDO MOVE", "[undoMove]") {
	std::string FEN = "3k4/p6p/8/8/1Pp5/8/3PP3/K7 b - b3 1 1";
	BoardState bs1(FEN);
	BoardState bs2(bs1);
	REQUIRE(bs1.activeStateEquals(bs2));
	REQUIRE(bs1.makeMove(Square::getSquare("a7"),Square::getSquare("a6")));
	BoardState bs3(bs1);
	REQUIRE(!bs1.activeStateEquals(bs2));
	REQUIRE(bs1.activeStateEquals(bs3));
	REQUIRE(bs1.getActivePly() == 1);
	bs1.undoMove();
	bs1.updateLegality();
	REQUIRE(bs1.activeStateEquals(bs2));
	REQUIRE(!bs1.activeStateEquals(bs3));
	REQUIRE(!bs1.isRewound());
	REQUIRE(!bs1.getLegalMoves().empty());
	REQUIRE(bs1.getActivePly() == 0);
}

TEST_CASE("FIRST 5 PLIES 1. e4 e5 2. bb5 nf6 3. bd7 ... REWIND/FASTFORWARD", "[BoardStateFunctional]") {
	// Set up board
	BoardState bs;
	BoardState bs0(bs);
	REQUIRE(bs.makeMove(Square::getSquare("e2"),Square::getSquare("e4")));
	BoardState bs1(bs);
	REQUIRE(bs.makeMove(Square::getSquare("e7"),Square::getSquare("e5")));
	BoardState bs2(bs);
	REQUIRE(bs.makeMove(Square::getSquare("f1"),Square::getSquare("b5")));
	BoardState bs3(bs);
	REQUIRE(bs.makeMove(Square::getSquare("g8"),Square::getSquare("f6")));
	BoardState bs4(bs);
	REQUIRE(bs.makeMove(Square::getSquare("b5"),Square::getSquare("d7")));
	BoardState bs5(bs);
	
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 5);
	
	bs.rewindOneMove();
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(bs.activeStateEquals(bs4));
	REQUIRE(!bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 4);
	REQUIRE(bs.isRewound());
	REQUIRE(bs.getLegalMoves().empty());
	
	bs.rewindToStart();
	REQUIRE(bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(!bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 0);
	REQUIRE(bs.isRewound());
	REQUIRE(bs.getLegalMoves().empty());
	
	bs.fastForwardOneMove();
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(!bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 1);
	REQUIRE(bs.isRewound());
	REQUIRE(bs.getLegalMoves().empty());
	
	bs.fastForwardToPresent();
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 5);
	REQUIRE(!bs.isRewound());
	REQUIRE(!bs.getLegalMoves().empty());
	
	bs.fastForwardOneMove();
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 5);
	REQUIRE(!bs.isRewound());
	REQUIRE(!bs.getLegalMoves().empty());
	
	bs.rewindToStart();
	bs.rewindOneMove();
	REQUIRE(bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(!bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 0);
	REQUIRE(bs.isRewound());
	REQUIRE(bs.getLegalMoves().empty());
	
	bs.setViewingPly(3);
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(!bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 3);
	REQUIRE(bs.isRewound());
	REQUIRE(bs.getLegalMoves().empty());
	
	bs.setViewingPly(-100);
	REQUIRE(bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(!bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 0);
	REQUIRE(bs.isRewound());
	REQUIRE(bs.getLegalMoves().empty());
	
	bs.setViewingPly(100);
	REQUIRE(!bs.activeStateEquals(bs0));
	REQUIRE(!bs.activeStateEquals(bs1));
	REQUIRE(!bs.activeStateEquals(bs2));
	REQUIRE(!bs.activeStateEquals(bs3));
	REQUIRE(!bs.activeStateEquals(bs4));
	REQUIRE(bs.activeStateEquals(bs5));
	REQUIRE(bs.getActivePly() == 5);
	REQUIRE(!bs.isRewound());
	REQUIRE(!bs.getLegalMoves().empty());
}
*/


TEST_CASE("EN PASSANT UTILITIES", "[BoardStateFunctional]") {
	std::string FEN = "8/1p6/8/k1P1r3/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	// White cant en passant, makes random move
	REQUIRE(!bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.makeMove(Square::getSquare("h1"),Square::getSquare("h2")));
	// Black creates en passant square
	REQUIRE(bs.makeMove(Square::getSquare("b7"),Square::getSquare("b5")));
	
	REQUIRE(bs.moveIsEnPassant(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(bs.getEnPassantableSquare() == Square::getSquare("b6"));
	REQUIRE(bs.getEnPassantCaptureSquare() == Square::getSquare("b5"));
}

TEST_CASE("PROMOTION UTILITIES", "[BoardStateFunctional]") {
	std::string FEN = "8/k3P3/8/8/8/p7/8/R1K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.moveRequiresPromotion(Square::getSquare("e7"),Square::getSquare("e8")));
	REQUIRE(!bs.moveRequiresPromotion(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(!bs.moveRequiresPromotion(Square::getSquare("a1"),Square::getSquare("a3")));
}

TEST_CASE("DRAW BY REPITITION FROM START", "[BoardStateFunctional]") {
	BoardState bs;
	REQUIRE(bs.getHalfmoveClock() == 0);
	// Move 1
	REQUIRE(bs.makeMove(Square::getSquare("g2"),Square::getSquare("g3")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 0);
	REQUIRE(bs.makeMove(Square::getSquare("g7"),Square::getSquare("g6")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 0);
	// Move 2
	REQUIRE(bs.makeMove(Square::getSquare("f1"),Square::getSquare("g2")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 1);
	REQUIRE(bs.makeMove(Square::getSquare("f8"),Square::getSquare("g7")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 2);
	// Move 3
	REQUIRE(bs.makeMove(Square::getSquare("g2"),Square::getSquare("f1")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 3);
	REQUIRE(bs.makeMove(Square::getSquare("g7"),Square::getSquare("f8")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 4);
	// Move 4
	REQUIRE(bs.makeMove(Square::getSquare("f1"),Square::getSquare("g2")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 5);
	REQUIRE(bs.makeMove(Square::getSquare("f8"),Square::getSquare("g7")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 6);
	// Move 5
	REQUIRE(bs.makeMove(Square::getSquare("g2"),Square::getSquare("f1")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 7);
	REQUIRE(bs.makeMove(Square::getSquare("g7"),Square::getSquare("f8")));
	REQUIRE(bs.getStalemateStatus());
	REQUIRE(bs.getHalfmoveClock() == 8);
}

TEST_CASE("DRAW BY REPITITION AFTER MOVES", "[BoardStateFunctional]") {
	BoardState bs;
	// Move 1
	REQUIRE(bs.makeMove(Square::getSquare("d2"),Square::getSquare("d3")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("e7"),Square::getSquare("e5")));
	REQUIRE(!bs.getStalemateStatus());
	// Move 2
	REQUIRE(bs.makeMove(Square::getSquare("d3"),Square::getSquare("d4")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("e5"),Square::getSquare("d4")));
	REQUIRE(!bs.getStalemateStatus());
	// Move 3
	REQUIRE(bs.makeMove(Square::getSquare("d1"),Square::getSquare("d2")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("d8"),Square::getSquare("e7")));
	REQUIRE(!bs.getStalemateStatus());
	//Move 4
	REQUIRE(bs.makeMove(Square::getSquare("g2"),Square::getSquare("g3")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("g7"),Square::getSquare("g6")));
	REQUIRE(!bs.getStalemateStatus());
	// Move 5
	REQUIRE(bs.makeMove(Square::getSquare("f1"),Square::getSquare("g2")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("f8"),Square::getSquare("g7")));
	REQUIRE(!bs.getStalemateStatus());
	// Move 6
	REQUIRE(bs.makeMove(Square::getSquare("g2"),Square::getSquare("f1")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("g7"),Square::getSquare("f8")));
	REQUIRE(!bs.getStalemateStatus());
	// Move 7
	REQUIRE(bs.makeMove(Square::getSquare("f1"),Square::getSquare("g2")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("f8"),Square::getSquare("g7")));
	REQUIRE(!bs.getStalemateStatus());
	// Move 8
	REQUIRE(bs.makeMove(Square::getSquare("g2"),Square::getSquare("f1")));
	REQUIRE(!bs.getStalemateStatus());
	REQUIRE(bs.makeMove(Square::getSquare("g7"),Square::getSquare("f8")));
	REQUIRE(bs.getStalemateStatus());
}

TEST_CASE("GET LEGAL EXTENDED MOVES", "[BoardStateFunctional]") {
	std::string FEN = "7k/1P7/8/8/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getLegalExtendedMoves().size() == 7);
}

TEST_CASE("GET LEGAL EXTENDED MOVES WITH CAPTURE", "[BoardStateFunctional]") {
	std::string FEN = "r6k/1P7/8/8/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.getLegalExtendedMoves().size() == 11);
}

TEST_CASE("GET LEGAL EXTENDED MOVES WITH CAPTURE AND BLOCK", "[BoardStateFunctional]") {
	std::string FEN = "rN5k/1P7/8/8/8/8/8/7K w - - 0 1";
	BoardState bs(FEN);

	REQUIRE(bs.getLegalExtendedMoves().size() == 10);
}
