#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"

#include <iostream>

using namespace ChessCore;
using namespace ChessCore::Color;
using namespace ChessCore::Piece;

TEST_CASE("DEFAULT BOARD STATE", "[BoardState]") {
	BoardState bs;
	
	/*
	REQUIRE(bs.getWhitePawnSquares() == Square::getDefaultStartingWhitePawnSquares());
	REQUIRE(bs.getWhiteKnightSquares() == Square::getDefaultStartingWhiteKnightSquares());
	REQUIRE(bs.getWhiteBishopSquares() == Square::getDefaultStartingWhiteBishopSquares());
	REQUIRE(bs.getWhiteRookSquares() == Square::getDefaultStartingWhiteRookSquares());
	std::vector<Square_t> wq = { Square::getDefaultStartingWhiteQueenSquare() };
	REQUIRE(bs.getWhiteQueenSquares() == wq);
	REQUIRE(bs.getWhiteKingSquares().at(0) == Square::getDefaultStartingWhiteKingSquare());
	
	REQUIRE(bs.getBlackPawnSquares() == Square::getDefaultStartingBlackPawnSquares());
	REQUIRE(bs.getBlackKnightSquares() == Square::getDefaultStartingBlackKnightSquares());
	REQUIRE(bs.getBlackBishopSquares() == Square::getDefaultStartingBlackBishopSquares());
	REQUIRE(bs.getBlackRookSquares() == Square::getDefaultStartingBlackRookSquares());
	std::vector<Square_t> bq = { Square::getDefaultStartingBlackQueenSquare() };
	REQUIRE(bs.getBlackQueenSquares() == bq);
	REQUIRE(bs.getBlackKingSquares().at(0) == Square::getDefaultStartingBlackKingSquare());
	*/
	
	REQUIRE(bs.getTurnColor() == WHITE);
	REQUIRE(bs.getCheckStatus() == false);
	REQUIRE(bs.getCheckmateStatus() == false);
	REQUIRE(bs.getStalemateStatus() == false);
	
	std::vector<Move> legalMoveVec = bs.getLegalMoves();
	REQUIRE(legalMoveVec.size() == 20);
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("a3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g1"),Square::getSquare("h3")));
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
	
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("d3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e2"),Square::getSquare("f3")));
	
	REQUIRE(!bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("a6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("b8"),Square::getSquare("c6")));
	
	REQUIRE(!bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("f6")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("g8"),Square::getSquare("h6")));
}

TEST_CASE("EMPTY BOARD STATE", "[BoardState]") {
	BoardState bs(false);
	
	/*
	REQUIRE(bs.getWhitePawnSquares().empty());
	REQUIRE(bs.getWhiteKnightSquares().empty());
	REQUIRE(bs.getWhiteBishopSquares().empty());
	REQUIRE(bs.getWhiteRookSquares().empty());
	REQUIRE(bs.getWhiteQueenSquares().empty());
	REQUIRE(bs.getWhiteKingSquares().empty());
	
	REQUIRE(bs.getBlackPawnSquares().empty());
	REQUIRE(bs.getBlackKnightSquares().empty());
	REQUIRE(bs.getBlackBishopSquares().empty());
	REQUIRE(bs.getBlackRookSquares().empty());
	REQUIRE(bs.getBlackQueenSquares().empty());
	REQUIRE(bs.getBlackKingSquares().empty());
	*/
	REQUIRE(bs.getTurnColor() == WHITE);
	REQUIRE(bs.getCheckStatus() == false);
	REQUIRE(bs.getCheckmateStatus() == false);
	REQUIRE(bs.getStalemateStatus() == false);
	
	REQUIRE(bs.getLegalMoves().empty());
	REQUIRE(!bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("c3")));
	REQUIRE(!bs.isMoveLegal(Square::getSquare("b1"),Square::getSquare("a3")));
}

TEST_CASE("VALID BOARD STATE FROM FEN", "[BoardState]") {
	std::string FEN = "3k4/p6p/8/8/1Pp5/8/3PP3/K7 b - b3 1 1";
	BoardState bs(FEN);
	
	/*
	std::vector<Square_t> wpRef = {Square::getSquare("b4"),Square::getSquare("d2"),Square::getSquare("e2")};
	REQUIRE(bs.getWhitePawnSquares() == wpRef);
	REQUIRE(bs.getWhiteKnightSquares().empty());
	REQUIRE(bs.getWhiteBishopSquares().empty());
	REQUIRE(bs.getWhiteRookSquares().empty());
	REQUIRE(bs.getWhiteQueenSquares().empty());
	REQUIRE(bs.getWhiteKingSquares().at(0) == Square::getSquare("a1"));
	
	std::vector<Square_t> bpRef = {Square::getSquare("a7"),Square::getSquare("h7"),Square::getSquare("c4")};
	REQUIRE(bs.getBlackPawnSquares() == bpRef);
	REQUIRE(bs.getBlackKnightSquares().empty());
	REQUIRE(bs.getBlackBishopSquares().empty());
	REQUIRE(bs.getBlackRookSquares().empty());
	REQUIRE(bs.getBlackQueenSquares().empty());
	REQUIRE(bs.getBlackKingSquares().at(0) == Square::getSquare("d8"));
	*/
	REQUIRE(bs.getTurnColor() == BLACK);
	REQUIRE(!bs.getCheckStatus());
	REQUIRE(!bs.getCheckmateStatus());
	REQUIRE(!bs.getStalemateStatus());
	
	REQUIRE(bs.getLegalMoves().size() == 11);
	REQUIRE(bs.isMoveLegal(Square::	getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::	getSquare("a7"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a7"),Square::getSquare("a5")));
	REQUIRE(bs.isMoveLegal(Square::	getSquare("h7"),Square::getSquare("h6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h7"),Square::getSquare("h5")));
	REQUIRE(bs.isMoveLegal(Square::	getSquare("d8"),Square::getSquare("e8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("c8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("c7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("e7")));
}

TEST_CASE("BOARD COPY", "[BoardState]") {
	std::string FEN = "3k4/p6p/8/8/1Pp5/8/3PP3/K7 b - b3 1 1";
	BoardState bsBase(FEN);
	BoardState bs(bsBase);
	
	/*
	std::vector<Square_t> wpRef = {Square::getSquare("b4"),Square::getSquare("d2"),Square::getSquare("e2")};
	REQUIRE(bs.getWhitePawnSquares() == wpRef);
	REQUIRE(bs.getWhiteKnightSquares().empty());
	REQUIRE(bs.getWhiteBishopSquares().empty());
	REQUIRE(bs.getWhiteRookSquares().empty());
	REQUIRE(bs.getWhiteQueenSquares().empty());
	REQUIRE(bs.getWhiteKingSquares().at(0) == Square::getSquare("a1"));
	
	std::vector<Square_t> bpRef = {Square::getSquare("a7"),Square::getSquare("h7"),Square::getSquare("c4")};
	REQUIRE(bs.getBlackPawnSquares() == bpRef);
	REQUIRE(bs.getBlackKnightSquares().empty());
	REQUIRE(bs.getBlackBishopSquares().empty());
	REQUIRE(bs.getBlackRookSquares().empty());
	REQUIRE(bs.getBlackQueenSquares().empty());
	REQUIRE(bs.getBlackKingSquares().at(0) == Square::getSquare("d8"));
	*/
	
	REQUIRE(bs.getTurnColor() == BLACK);
	REQUIRE(bs.getCheckStatus() == false);
	REQUIRE(bs.getCheckmateStatus() == false);
	REQUIRE(bs.getStalemateStatus() == false);
	
	REQUIRE(bs.getLegalMoves().size() == 11);
	REQUIRE(bs.isMoveLegal(Square::
	getSquare("c4"),Square::getSquare("b3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c4"),Square::getSquare("c3")));
	REQUIRE(bs.isMoveLegal(Square::
	getSquare("a7"),Square::getSquare("a6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("a7"),Square::getSquare("a5")));
	REQUIRE(bs.isMoveLegal(Square::
	getSquare("h7"),Square::getSquare("h6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h7"),Square::getSquare("h5")));
	REQUIRE(bs.isMoveLegal(Square::
	getSquare("d8"),Square::getSquare("e8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("c8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("d7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("c7")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("e7")));
}

TEST_CASE("BASIC MAKE MOVE", "[makeMove]") {
	std::string FEN = "k7/7p/8/8/8/8/p7/7K w - - 0 1";
	BoardState bs(FEN);
	std::cout << "---------------- basic make move ----------------" << std::endl;
	//REQUIRE(bs.getKingSquare(WHITE) == Square::getSquare("h1"));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(bs.makeMove(Square::getSquare("h1"),Square::getSquare("g1")));
	//REQUIRE(bs.getKingSquare(WHITE) == Square::getSquare("g1"));
}

/*
TEST_CASE("BOARD STATE EQUALS", "[activeStateEquals]") {
	std::string FEN = "3k4/p6p/8/8/1Pp5/8/3PP3/K7 b - b3 1 1";
	BoardState bs1(FEN);
	BoardState bs2(FEN);
	REQUIRE(bs1.activeStateEquals(bs2));
}

TEST_CASE("BOARD STATE NOT EQUALS", "[activeStateEquals]") {
	std::string FEN1 = "3k4/p6p/8/8/1Pp5/8/3PP3/K7 b - b3 1 1";
	BoardState bs1(FEN1);
	std::string FEN2 = "k7/7p/7b/8/8/7R/p7/7K w - - 0 1";
	BoardState bs2(FEN2);
	REQUIRE(!bs1.activeStateEquals(bs2));
}
*/

TEST_CASE("MOVE IS CAPTURE", "[activeStateEquals]") {
	std::string FEN1 = "1r5k/P7/8/8/8/8/7n/7K w - - 0 1";
	BoardState bs(FEN1);
	REQUIRE(bs.moveIsCapture(Square::getSquare("a7"),Square::getSquare("b8")));
	REQUIRE(!bs.moveIsCapture(Square::getSquare("a7"),Square::getSquare("a8")));
	REQUIRE(bs.moveIsCapture(Square::getSquare("h1"),Square::getSquare("h2")));
	REQUIRE(!bs.moveIsCapture(Square::getSquare("h1"),Square::getSquare("g1")));
	REQUIRE(!bs.moveIsCapture(Square::getSquare("h1"),Square::getSquare("g2")));
}

TEST_CASE("WHITE MOVE WOULD BE CHECK", "[moveGivesCheck]") {
	std::string FEN = "4k3/2P5/5P2/1N6/6B1/7n/1Qr5/2R2b1K w - - 0 1";
	BoardState bs(FEN);
	
	
	REQUIRE(!bs.getCheckStatus());
	// Queen 
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("e5")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("b2"),Square::getSquare("e5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b2"),Square::getSquare("b1")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("b2"),Square::getSquare("b1")));
	// Knight
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("d6")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("b5"),Square::getSquare("d6")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("b5"),Square::getSquare("a7")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("b5"),Square::getSquare("a7")));
	// Bishop
	REQUIRE(bs.isMoveLegal(Square::getSquare("g4"),Square::getSquare("h5")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("g4"),Square::getSquare("h5")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g4"),Square::getSquare("f3")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("g4"),Square::getSquare("f3")));
	// Rook
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("e1")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("c1"),Square::getSquare("e1")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c1"),Square::getSquare("b1")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("c1"),Square::getSquare("b1")));
	// Pawn - promote
	ExtendedMove m;
	m = {Square::getSquare("c7"),Square::getSquare("c8"),ROOK};
	REQUIRE(bs.isMoveLegal(m));
	m = {Square::getSquare("c7"),Square::getSquare("c8"),ROOK};
	REQUIRE(bs.moveGivesCheck(m));
	m = {Square::getSquare("c7"),Square::getSquare("c8"),KNIGHT};
	REQUIRE(bs.isMoveLegal(m));
	m = {Square::getSquare("c7"),Square::getSquare("c8"),KNIGHT};
	REQUIRE(!bs.moveGivesCheck(m));
	// Pawn - no promote
	REQUIRE(bs.isMoveLegal(Square::getSquare("f6"),Square::getSquare("f7")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("f6"),Square::getSquare("f7")));
}

TEST_CASE("BLACK MOVE WOULD BE CHECK", "[moveGivesCheck]") {
	std::string FEN = "3r1R2/8/6q1/2b5/7n/3p3N/2p5/4KB1k b - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.getCheckStatus());
	// Queen 
	REQUIRE(bs.isMoveLegal(Square::getSquare("g6"),Square::getSquare("e4")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("g6"),Square::getSquare("e4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("g6"),Square::getSquare("g7")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("g6"),Square::getSquare("g7")));
	// Knight
	REQUIRE(bs.isMoveLegal(Square::getSquare("h4"),Square::getSquare("f3")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("h4"),Square::getSquare("f3")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("h4"),Square::getSquare("f5")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("h4"),Square::getSquare("f5")));
	// Bishop
	REQUIRE(bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b4")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("c5"),Square::getSquare("b4")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("c5"),Square::getSquare("b6")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("c5"),Square::getSquare("b6")));
	// Rook
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("e8")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("d8"),Square::getSquare("e8")));
	REQUIRE(bs.isMoveLegal(Square::getSquare("d8"),Square::getSquare("f8")));
	REQUIRE(!bs.moveGivesCheck(Square::getSquare("d8"),Square::getSquare("f8")));
	// Pawn - promote
	ExtendedMove m;
	m = {Square::getSquare("c2"),Square::getSquare("c1"),ROOK};
	REQUIRE(bs.isMoveLegal(m));
	m = {Square::getSquare("c2"),Square::getSquare("c1"),ROOK};
	REQUIRE(bs.moveGivesCheck(m));
	m = {Square::getSquare("c2"),Square::getSquare("c1"),KNIGHT};
	REQUIRE(bs.isMoveLegal(m));
	m = {Square::getSquare("c2"),Square::getSquare("c1"),KNIGHT};
	REQUIRE(!bs.moveGivesCheck(m));
	// Pawn - no promote
	REQUIRE(bs.isMoveLegal(Square::getSquare("d3"),Square::getSquare("d2")));
	REQUIRE(bs.moveGivesCheck(Square::getSquare("d3"),Square::getSquare("d2")));
}

TEST_CASE("KING DEFENDS PIECE", "[moveGivesCheck]") {
	std::string FEN = "8/8/8/3n4/2k1K3/8/8/8 w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.isMoveLegal(Square::getSquare("e4"),Square::getSquare("d5")));
}

TEST_CASE("WHITE SUFFICIENT CHECKMATING MATERIAL", "[whiteHasSufficientCheckmatingMaterial]") {
	std::string FEN = "1k6/8/4n3/4P3/8/8/5B2/1K6 w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(!bs.blackHasSufficientCheckmatingMaterial());
	REQUIRE(bs.whiteHasSufficientCheckmatingMaterial());
}

TEST_CASE("BLACK SUFFICIENT CHECKMATING MATERIAL", "[blackHasSufficientCheckmatingMaterial]") {
	std::string FEN = "1k6/8/4n3/4p3/8/8/5B2/1K6 w - - 0 1";
	BoardState bs(FEN);
	
	REQUIRE(bs.blackHasSufficientCheckmatingMaterial());
	REQUIRE(!bs.whiteHasSufficientCheckmatingMaterial());
}
