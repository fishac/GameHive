#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"
#include <iostream>

using namespace ChessCore;
using namespace ChessCore::Color;
using namespace ChessCore::Piece;

TEST_CASE("GETSQUARE a1", "[getSquare(int,int)]") {
	Square_t sq = Square::getSquare(0,0);
	uint64_t ref = 0x0000000000000001;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE a2", "[getSquare(int,int)]") {
	Square_t sq = Square::getSquare(0,1);
	uint64_t ref = 0x0000000000000100;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE e4", "[getSquare(int,int)]") {
	Square_t sq = Square::getSquare(4,3);
	uint64_t ref = 0x0000000010000000;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE h8", "[getSquare(int,int)]") {
	Square_t sq = Square::getSquare(7,7);
	uint64_t ref = 0x8000000000000000;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE a1", "[getSquare(int)]") {
	Square_t sq = Square::getSquare(0);
	uint64_t ref = 0x0000000000000001;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE a2", "[getSquare(int)]") {
	Square_t sq = Square::getSquare(8);
	uint64_t ref = 0x0000000000000100;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE e4", "[getSquare(int)]") {
	Square_t sq = Square::getSquare(28);
	uint64_t ref = 0x0000000010000000;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE h8", "[getSquare(int)]") {
	Square_t sq = Square::getSquare(63);
	uint64_t ref = 0x8000000000000000;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE a1", "[getSquare(std::string)]") {
	Square_t sq = Square::getSquare("a1");
	uint64_t ref = 0x0000000000000001;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE a2", "[getSquare(std::string)]") {
	Square_t sq = Square::getSquare("a2");
	uint64_t ref = 0x0000000000000100;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE e4", "[getSquare(std::string)]") {
	Square_t sq = Square::getSquare("e4");
	uint64_t ref = 0x0000000010000000;
	REQUIRE(sq == ref);
}

TEST_CASE("GETSQUARE h8", "[getSquare(std::string)]") {
	Square_t sq = Square::getSquare("h8");
	uint64_t ref = 0x8000000000000000;
	REQUIRE(sq == ref);
}

TEST_CASE("GETINDEX a1", "[getIndex(int i)]") {
	Square_t sq = Square::getSquare("a1");
	REQUIRE(Square::getIndex(sq) == 0);
}

TEST_CASE("GETINDEX b1", "[getIndex(int i)]") {
	Square_t sq = Square::getSquare("b1");
	REQUIRE(Square::getIndex(sq) == 1);
}

TEST_CASE("GETRANK/GETFILE a1", "[getRank(Square_t)/getFile(Square_t)]") {
	Square_t sq = Square::getSquare("a1");
	REQUIRE(Square::getRank(sq) == 0);
	REQUIRE(Square::getFile(sq) == 0);
}

TEST_CASE("GETRANK/GETFILE b6", "[getRank(Square_t)/getFile(Square_t)]") {
	Square_t sq = Square::getSquare("b6");
	REQUIRE(Square::getRank(sq) == 5);
	REQUIRE(Square::getFile(sq) == 1);
}

TEST_CASE("GETRANK/GETFILE a1", "[getRank(int i)/getFile(int i)]") {
	Square_t sq = Square::getSquare("a1");
	int idx = Square::getIndex(sq);
	REQUIRE(Square::getRank(idx) == 0);
	REQUIRE(Square::getFile(idx) == 0);
}

TEST_CASE("GETRANK/GETFILE b6", "[getRank(int i)/getFile(int i)]") {
	Square_t sq = Square::getSquare("b6");
	int idx = Square::getIndex(sq);
	std::cout << "b6 idx: " << idx << std::endl;
	REQUIRE(Square::getRank(idx) == 5);
	REQUIRE(Square::getFile(idx) == 1);
}

TEST_CASE("GETINDEX a2", "[getIndex(Square_t)]") {
	Square_t sq = Square::getSquare("a2");
	REQUIRE(Square::getIndex(sq) == 8);
}

TEST_CASE("GETINDEX e4", "[getIndex(Square_t)]") {
	Square_t sq = Square::getSquare("e4");
	REQUIRE(Square::getIndex(sq) == 28);
}

TEST_CASE("GETINDEX h7", "[getIndex(Square_t)]") {
	Square_t sq = Square::getSquare("h7");
	REQUIRE(Square::getIndex(sq) == 55);
}

TEST_CASE("GETINDEX h8", "[getIndex(Square_t)]") {
	Square_t sq = Square::getSquare("h8");
	REQUIRE(Square::getIndex(sq) == 63);
}

TEST_CASE("GETSHADE a1", "[getShade(Square_t)]") {
	Square_t sq = Square::getSquare("a1");
	REQUIRE(Square::getShade(sq) == BLACK);
}

TEST_CASE("GETSHADE a2", "[getShade(Square_t)]") {
	Square_t sq = Square::getSquare("a2");
	REQUIRE(Square::getShade(sq) == WHITE);
}

TEST_CASE("GETSHADE b6", "[getShade(Square_t)]") {
	Square_t sq = Square::getSquare("b6");
	REQUIRE(Square::getShade(sq) == BLACK);
}

TEST_CASE("GETSHADE h7", "[getShade(Square_t)]") {
	Square_t sq = Square::getSquare("h7");
	REQUIRE(Square::getShade(sq) == WHITE);
}

TEST_CASE("GETRANK a2", "[getRank(Square_t)]") {
	Square_t sq = Square::getSquare("a2");
	REQUIRE(Square::getRank(sq) == 1);
}

TEST_CASE("GETRANK e4", "[getRank(Square_t)]") {
	Square_t sq = Square::getSquare("e4");
	REQUIRE(Square::getRank(sq) == 3);
}

TEST_CASE("GETRANK h7", "[getRank(Square_t)]") {
	Square_t sq = Square::getSquare("h7");
	REQUIRE(Square::getRank(sq) == 6);
}

TEST_CASE("GETFILE a2", "[getFile(Square_t)]") {
	Square_t sq = Square::getSquare("a2");
	REQUIRE(Square::getFile(sq) == 0);
}

TEST_CASE("GETFILE e4", "[getFile(Square_t)]") {
	Square_t sq = Square::getSquare("e4");
	REQUIRE(Square::getFile(sq) == 4);
}

TEST_CASE("GETFILE h7", "[getFile(Square_t)]") {
	Square_t sq = Square::getSquare("h7");
	REQUIRE(Square::getFile(sq) == 7);
}

TEST_CASE("GETSTRING a1", "[getString(Square_t)]") {
	Square_t sq = Square::getSquare("a1");
	REQUIRE(Square::getString(sq) == "a1");
}

TEST_CASE("GETSTRING h8", "[getString(Square_t)]") {
	Square_t sq = Square::getSquare("h8");
	REQUIRE(Square::getString(sq) == "h8");
}

TEST_CASE("AROOKSTARTINGSQUARE WHITE", "[aRookStartingSquare(Color_t)]") {
	Square_t sq = Square::aRookStartingSquare(WHITE);
	Square_t ref = Square::getSquare("a1");
	REQUIRE(sq == ref);
}

TEST_CASE("AROOKSTARTINGSQUARE BLACK", "[aRookStartingSquare(Color_t)]") {
	Square_t sq = Square::aRookStartingSquare(BLACK);
	Square_t ref = Square::getSquare("a8");
	REQUIRE(sq == ref);
}

TEST_CASE("HROOKSTARTINGSQUARE WHITE", "[aRookStartingSquare(Color_t)]") {
	Square_t sq = Square::hRookStartingSquare(WHITE);
	Square_t ref = Square::getSquare("h1");
	REQUIRE(sq == ref);
}

TEST_CASE("HROOKSTARTINGSQUARE BLACK", "[aRookStartingSquare(Color_t)]") {
	Square_t sq = Square::hRookStartingSquare(BLACK);
	Square_t ref = Square::getSquare("h8");
	REQUIRE(sq == ref);
}

TEST_CASE("AROOKCASTLETARGET WHITE", "[aRookCastleTarget(Color_t)]") {
	Square_t sq = Square::aRookCastleTarget(WHITE);
	Square_t ref = Square::getSquare("d1");
	REQUIRE(sq == ref);
}

TEST_CASE("AROOKCASTLETARGET BLACK", "[aRookStartingSquare(Color_t)]") {
	Square_t sq = Square::aRookCastleTarget(BLACK);
	Square_t ref = Square::getSquare("d8");
	REQUIRE(sq == ref);
}

TEST_CASE("HROOKCASTLETARGET WHITE", "[hRookCastleTarget(Color_t)]") {
	Square_t sq = Square::hRookCastleTarget(WHITE);
	Square_t ref = Square::getSquare("f1");
	REQUIRE(sq == ref);
}

TEST_CASE("HROOKCASTLETARGET BLACK", "[hRookCastleTarget(Color_t)]") {
	Square_t sq = Square::hRookCastleTarget(BLACK);
	Square_t ref = Square::getSquare("f8");
	REQUIRE(sq == ref);
}

TEST_CASE("GETDEFAULTSTARTINGWHITEPAWNSQUARES", "[getDefaultStartingWhitePawnSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingWhitePawnSquares();
	REQUIRE(vec.size() == 8);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("a2")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("e2")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("h2")));
}

TEST_CASE("GETDEFAULTSTARTINGBLACKPAWNSQUARES", "[getDefaultStartingBlackPawnSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingBlackPawnSquares();
	REQUIRE(vec.size() == 8);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("a7")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("e7")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("h7")));
}

TEST_CASE("GETDEFAULTSTARTINGWHITEKNIGHTSQUARES", "[getDefaultStartingWhiteKnightSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingWhiteKnightSquares();
	REQUIRE(vec.size() == 2);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("b1")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("g1")));
}

TEST_CASE("GETDEFAULTSTARTINGBLACKKNIGHTSQUARES", "[getDefaultStartingBlackKnightSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingBlackKnightSquares();
	REQUIRE(vec.size() == 2);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("b8")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("g8")));
}

TEST_CASE("GETDEFAULTSTARTINGWHITEBISHOPSQUARES", "[getDefaultStartingWhiteBishopSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingWhiteBishopSquares();
	REQUIRE(vec.size() == 2);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("c1")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("f1")));
}

TEST_CASE("GETDEFAULTSTARTINGBLACKBISHOPSQUARES", "[getDefaultStartingBlackBishopSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingBlackBishopSquares();
	REQUIRE(vec.size() == 2);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("c8")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("f8")));
}

TEST_CASE("GETDEFAULTSTARTINGWHITEROOKSQUARES", "[getDefaultStartingWhiteRookSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingWhiteRookSquares();
	REQUIRE(vec.size() == 2);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("a1")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("h1")));
}

TEST_CASE("GETDEFAULTSTARTINGBLACKROOKSQUARES", "[getDefaultStartingBlackRookSquares()]") {
	std::vector<Square_t> vec = Square::getDefaultStartingBlackRookSquares();
	REQUIRE(vec.size() == 2);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("a8")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("h8")));
}

TEST_CASE("GETDEFAULTSTARTINGWHITEQUEENSQUARE", "[getDefaultStartingWhiteQueenSquare()]") {
	Square_t sq = Square::getDefaultStartingWhiteQueenSquare();
	REQUIRE(sq == Square::getSquare("d1"));
}

TEST_CASE("GETDEFAULTSTARTINGBLACKQUEENSQUARE", "[getDefaultStartingBlackQueenSquare()]") {
	Square_t sq = Square::getDefaultStartingBlackQueenSquare();
	REQUIRE(sq == Square::getSquare("d8"));
}

TEST_CASE("GETDEFAULTSTARTINGWHITEKINGSQUARE", "[getDefaultStartingWhiteKingSquare()]") {
	Square_t sq = Square::getDefaultStartingWhiteKingSquare();
	REQUIRE(sq == Square::getSquare("e1"));
}

TEST_CASE("GETDEFAULTSTARTINGBLACKKINGSQUARE", "[getDefaultStartingBlackKingSquare()]") {
	Square_t sq = Square::getDefaultStartingBlackKingSquare();
	REQUIRE(sq == Square::getSquare("e8"));
}

TEST_CASE("N ONE SQUARE", "[n()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = Square::getSquare("a2");
	BoardMask_t ret = Square::n(from);
	REQUIRE(ret == to);
}

TEST_CASE("N MULTI SQUARE", "[n()]") {
	Square_t from1 = Square::getSquare("a1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("a2") | Square::getSquare("e5");
	BoardMask_t ret = Square::n(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("N OFF BOARD", "[n()]") {
	Square_t from = Square::getSquare("a8");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::n(from);
	REQUIRE(ret == to);
}

TEST_CASE("S ONE SQUARE", "[s()]") {
	Square_t from = Square::getSquare("a8");
	BoardMask_t to = Square::getSquare("a7");
	BoardMask_t ret = Square::s(from);
	REQUIRE(ret == to);
}

TEST_CASE("S MULTI SQUARE", "[s()]") {
	Square_t from1 = Square::getSquare("a8");
	Square_t from2 = Square::getSquare("e5");
	BoardMask_t to = Square::getSquare("a7") | Square::getSquare("e4");
	BoardMask_t ret = Square::s(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("S OFF BOARD", "[s()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::s(from);
	REQUIRE(ret == to);
}

TEST_CASE("E ONE SQUARE", "[e()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = Square::getSquare("b1");
	BoardMask_t ret = Square::e(from);
	REQUIRE(ret == to);
}

TEST_CASE("E MULTI SQUARE", "[e()]") {
	Square_t from1 = Square::getSquare("a1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("b1") | Square::getSquare("f4");
	BoardMask_t ret = Square::e(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("S OFF BOARD", "[e()]") {
	Square_t from = Square::getSquare("h1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::e(from);
	REQUIRE(ret == to);
}

TEST_CASE("W ONE SQUARE", "[w()]") {
	Square_t from = Square::getSquare("h1");
	BoardMask_t to = Square::getSquare("g1");
	BoardMask_t ret = Square::w(from);
	REQUIRE(ret == to);
}

TEST_CASE("W MULTI SQUARE", "[w()]") {
	Square_t from1 = Square::getSquare("h1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("g1") | Square::getSquare("d4");
	BoardMask_t ret = Square::w(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("W OFF BOARD", "[w()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::w(from);
	REQUIRE(ret == to);
}

TEST_CASE("NE ONE SQUARE", "[ne()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = Square::getSquare("b2");
	BoardMask_t ret = Square::ne(from);
	REQUIRE(ret == to);
}

TEST_CASE("NE MULTI SQUARE", "[ne()]") {
	Square_t from1 = Square::getSquare("a1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("b2") | Square::getSquare("f5");
	BoardMask_t ret = Square::ne(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("NE OFF BOARD", "[ne()]") {
	Square_t from = Square::getSquare("h8");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::ne(from);
	REQUIRE(ret == to);
}

TEST_CASE("SE ONE SQUARE", "[se()]") {
	Square_t from = Square::getSquare("a8");
	BoardMask_t to = Square::getSquare("b7");
	BoardMask_t ret = Square::se(from);
	REQUIRE(ret == to);
}

TEST_CASE("SE MULTI SQUARE", "[se()]") {
	Square_t from1 = Square::getSquare("a8");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("b7") | Square::getSquare("f3");
	BoardMask_t ret = Square::se(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("SE OFF BOARD", "[se()]") {
	Square_t from = Square::getSquare("h1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::se(from);
	REQUIRE(ret == to);
}

TEST_CASE("SW ONE SQUARE", "[sw()]") {
	Square_t from = Square::getSquare("h8");
	BoardMask_t to = Square::getSquare("g7");
	BoardMask_t ret = Square::sw(from);
	REQUIRE(ret == to);
}

TEST_CASE("SW MULTI SQUARE", "[sw()]") {
	Square_t from1 = Square::getSquare("h8");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("g7") | Square::getSquare("d3");
	BoardMask_t ret = Square::sw(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("SW OFF BOARD", "[sw()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::sw(from);
	REQUIRE(ret == to);
}

TEST_CASE("NW ONE SQUARE", "[nw()]") {
	Square_t from = Square::getSquare("h1");
	BoardMask_t to = Square::getSquare("g2");
	BoardMask_t ret = Square::nw(from);
	REQUIRE(ret == to);
}

TEST_CASE("NW MULTI SQUARE", "[nw()]") {
	Square_t from1 = Square::getSquare("h1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("g2") | Square::getSquare("d5");
	BoardMask_t ret = Square::nw(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("NW OFF BOARD", "[nw()]") {
	Square_t from = Square::getSquare("a8");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::nw(from);
	REQUIRE(ret == to);
}

TEST_CASE("NN ONE SQUARE", "[nn()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = Square::getSquare("a3");
	BoardMask_t ret = Square::nn(from);
	REQUIRE(ret == to);
}

TEST_CASE("NN MULTI SQUARE", "[nn()]") {
	Square_t from1 = Square::getSquare("a1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("a3") | Square::getSquare("e6");
	BoardMask_t ret = Square::nn(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("NN OFF BOARD", "[nn()]") {
	Square_t from = Square::getSquare("a7");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::nn(from);
	REQUIRE(ret == to);
}

TEST_CASE("EE ONE SQUARE", "[ee()]") {
	Square_t from = Square::getSquare("a1");
	BoardMask_t to = Square::getSquare("c1");
	BoardMask_t ret = Square::ee(from);
	REQUIRE(ret == to);
}

TEST_CASE("EE MULTI SQUARE", "[ee()]") {
	Square_t from1 = Square::getSquare("a1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("c1") | Square::getSquare("g4");
	BoardMask_t ret = Square::ee(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("EE OFF BOARD", "[ee()]") {
	Square_t from = Square::getSquare("g1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::ee(from);
	REQUIRE(ret == to);
}

TEST_CASE("SS ONE SQUARE", "[ss()]") {
	Square_t from = Square::getSquare("a8");
	BoardMask_t to = Square::getSquare("a6");
	BoardMask_t ret = Square::ss(from);
	REQUIRE(ret == to);
}

TEST_CASE("SS MULTI SQUARE", "[ss()]") {
	Square_t from1 = Square::getSquare("a8");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("a6") | Square::getSquare("e2");
	BoardMask_t ret = Square::ss(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("SS OFF BOARD", "[ss()]") {
	Square_t from = Square::getSquare("a2");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::ss(from);
	REQUIRE(ret == to);
}

TEST_CASE("WW ONE SQUARE", "[ww()]") {
	Square_t from = Square::getSquare("h1");
	BoardMask_t to = Square::getSquare("f1");
	BoardMask_t ret = Square::ww(from);
	REQUIRE(ret == to);
}

TEST_CASE("WW MULTI SQUARE", "[ww()]") {
	Square_t from1 = Square::getSquare("h1");
	Square_t from2 = Square::getSquare("e4");
	BoardMask_t to = Square::getSquare("f1") | Square::getSquare("c4");
	BoardMask_t ret = Square::ww(from1 | from2);
	REQUIRE(ret == to);
}

TEST_CASE("WW OFF BOARD", "[ww()]") {
	Square_t from = Square::getSquare("b1");
	BoardMask_t to = (uint64_t) 0;
	BoardMask_t ret = Square::ww(from);
	REQUIRE(ret == to);
}

TEST_CASE("GETSQUARES EMPTY", "[getSquares()]") {
	BoardMask_t bm =(uint64_t) 0;
	std::vector<Square_t> vec = Square::getSquares(bm);
	REQUIRE(vec.empty());
}

TEST_CASE("GETSQUARES NONEMPTY", "[getSquares()]") {
	BoardMask_t bm = Square::getSquare("a1") | Square::getSquare("e4") | Square::getSquare("f7") | Square::getSquare("h8");
	std::vector<Square_t> vec = Square::getSquares(bm);
	REQUIRE(vec.size() == 4);
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("a1")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("e4")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("f7")));
	REQUIRE(Vector::squareInVector(vec,Square::getSquare("h8")));
}

TEST_CASE("ONSECONDRANK FALSE", "[onSecondRank()]") {
	Square_t sq1 = Square::getSquare("a1");
	Square_t sq2 = Square::getSquare("a3");
	
	REQUIRE(!Square::onSecondRank(sq1));
	REQUIRE(!Square::onSecondRank(sq2));
}

TEST_CASE("ONSECONDRANK TRUE", "[onSecondRank()]") {
	Square_t sq1 = Square::getSquare("a2");
	Square_t sq2 = Square::getSquare("e2");
	Square_t sq3 = Square::getSquare("h2");
	
	REQUIRE(Square::onSecondRank(sq1));
	REQUIRE(Square::onSecondRank(sq2));
	REQUIRE(Square::onSecondRank(sq3));
}

TEST_CASE("ONSEVENTHRANK FALSE", "[onSeventhRank()]") {
	Square_t sq1 = Square::getSquare("a8");
	Square_t sq2 = Square::getSquare("a6");
	
	REQUIRE(!Square::onSeventhRank(sq1));
	REQUIRE(!Square::onSeventhRank(sq2));
}

TEST_CASE("ONSEVENTHRANK TRUE", "[onSeventhRank()]") {
	Square_t sq1 = Square::getSquare("a7");
	Square_t sq2 = Square::getSquare("e7");
	Square_t sq3 = Square::getSquare("h7");
	
	REQUIRE(Square::onSeventhRank(sq1));
	REQUIRE(Square::onSeventhRank(sq2));
	REQUIRE(Square::onSeventhRank(sq3));
}

TEST_CASE("ONFIRSTRANK FALSE", "[onFirstRank()]") {
	Square_t sq1 = Square::getSquare("a2");
	Square_t sq2 = Square::getSquare("a3");
	
	REQUIRE(!Square::onFirstRank(sq1));
	REQUIRE(!Square::onFirstRank(sq2));
}

TEST_CASE("ONFIRSTRANK TRUE", "[onFirstRank()]") {
	Square_t sq1 = Square::getSquare("a1");
	Square_t sq2 = Square::getSquare("e1");
	Square_t sq3 = Square::getSquare("h1");
	
	REQUIRE(Square::onFirstRank(sq1));
	REQUIRE(Square::onFirstRank(sq2));
	REQUIRE(Square::onFirstRank(sq3));
}

TEST_CASE("ONEIGHTHRANK FALSE", "[onEighthRank()]") {
	Square_t sq1 = Square::getSquare("a7");
	Square_t sq2 = Square::getSquare("a6");
	
	REQUIRE(!Square::onEighthRank(sq1));
	REQUIRE(!Square::onEighthRank(sq2));
}

TEST_CASE("ONEIGHTHRANK TRUE", "[onEighthRank()]") {
	Square_t sq1 = Square::getSquare("a8");
	Square_t sq2 = Square::getSquare("e8");
	Square_t sq3 = Square::getSquare("h8");
	
	REQUIRE(Square::onEighthRank(sq1));
	REQUIRE(Square::onEighthRank(sq2));
	REQUIRE(Square::onEighthRank(sq3));
}

TEST_CASE("ECASTLECROSSINGSQUARES WHITE", "[eCastleCrossingSquares()]") {
	BoardMask_t bm = Square::getSquare("f1") | Square::getSquare("g1");
	
	REQUIRE(Square::eCastleCrossingSquares(WHITE) == bm);
}

TEST_CASE("WCASTLECROSSINGSQUARES WHITE", "[wCastleCrossingSquares()]") {
	BoardMask_t bm = Square::getSquare("c1") | Square::getSquare("d1");
	
	REQUIRE(Square::wCastleCrossingSquares(WHITE) == bm);
}

TEST_CASE("ECASTLECROSSINGSQUARES BLACK", "[eCastleCrossingSquares()]") {
	BoardMask_t bm = Square::getSquare("f8") | Square::getSquare("g8");
	
	REQUIRE(Square::eCastleCrossingSquares(BLACK) == bm);
}

TEST_CASE("WCASTLECROSSINGSQUARES BLACK", "[wCastleCrossingSquares()]") {
	BoardMask_t bm = Square::getSquare("c8") | Square::getSquare("d8");
	
	REQUIRE(Square::wCastleCrossingSquares(BLACK) == bm);
}

TEST_CASE("ECASTLEBETWEENSQUARES WHITE", "[eCastleBetweenSquares()]") {
	BoardMask_t bm = Square::getSquare("f1") | Square::getSquare("g1");
	
	REQUIRE(Square::eCastleBetweenSquares(WHITE) == bm);
}

TEST_CASE("WCASTLECROSSINGSQUARES WHITE", "[wCastleBetweenSquares()]") {
	BoardMask_t bm = Square::getSquare("b1") | Square::getSquare("c1") | Square::getSquare("d1");
	
	REQUIRE(Square::wCastleBetweenSquares(WHITE) == bm);
}

TEST_CASE("ECASTLEBETWEENSQUARES BLACK", "[eCastleBetweenSquares()]") {
	BoardMask_t bm = Square::getSquare("f8") | Square::getSquare("g8");
	
	REQUIRE(Square::eCastleBetweenSquares(BLACK) == bm);
}

TEST_CASE("WCASTLECROSSINGSQUARES BLACK", "[wCastleBetweenSquares()]") {
	BoardMask_t bm = Square::getSquare("b8") | Square::getSquare("c8") | Square::getSquare("d8");
	
	REQUIRE(Square::wCastleBetweenSquares(BLACK) == bm);
}

TEST_CASE("ONPROMOTIONRANK WHITE", "[onPromotionRank()]") {
	Square_t first = Square::getSquare("e1");
	Square_t fourth = Square::getSquare("e4");
	Square_t eighth = Square::getSquare("e8");
	
	REQUIRE(!Square::onPromotionRank(first,WHITE));
	REQUIRE(!Square::onPromotionRank(fourth,WHITE));
	REQUIRE(Square::onPromotionRank(eighth,WHITE));
}

TEST_CASE("ONPROMOTIONRANK BLACK", "[onPromotionRank()]") {
	Square_t first = Square::getSquare("e1");
	Square_t fourth = Square::getSquare("e4");
	Square_t eighth = Square::getSquare("e8");
	
	REQUIRE(Square::onPromotionRank(first,BLACK));
	REQUIRE(!Square::onPromotionRank(fourth,BLACK));
	REQUIRE(!Square::onPromotionRank(eighth,BLACK));
}