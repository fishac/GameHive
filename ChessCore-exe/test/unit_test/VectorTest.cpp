#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"

using namespace ChessCore;

TEST_CASE("NOT IN EMPTY VECTOR", "[squareInVector]") {
	std::vector<Square_t> vec;
	Square_t sq = Square::getSquare(0);
	REQUIRE(!Vector::squareInVector(vec,sq));
}

TEST_CASE("NOT IN VECTOR", "[squareInVector]") {
	std::vector<Square_t> vec;
	Square_t sq1 = Square::getSquare(0);
	Square_t sq2 = Square::getSquare(1);
	Square_t sq3 = Square::getSquare(2);
	vec.push_back(sq1);
	vec.push_back(sq2);
	REQUIRE(!Vector::squareInVector(vec,sq3));
}

TEST_CASE("IN VECTOR", "[squareInVector]") {
	std::vector<Square_t> vec;
	Square_t sq1 = Square::getSquare(0);
	Square_t sq2 = Square::getSquare(1);
	Square_t sq3 = Square::getSquare(2);
	vec.push_back(sq1);
	vec.push_back(sq2);
	vec.push_back(sq3);
	REQUIRE(Vector::squareInVector(vec,sq2));
}

TEST_CASE("VECTOR MASK EMPTY", "[getVectorMask]") {
	std::vector<Square_t> vec;
	BoardMask_t bm_ref = NO_SQUARE;
	REQUIRE(Vector::getVectorMask(vec) == bm_ref);
}

TEST_CASE("VECTOR MASK", "[getVectorMask]") {
	std::vector<Square_t> vec = { Square::getSquare("a1"), Square::getSquare("e4"), Square::getSquare("h7") };
	BoardMask_t bm_ref = Square::getSquare("a1") | Square::getSquare("e4") | Square::getSquare("h7");
	REQUIRE(Vector::getVectorMask(vec) == bm_ref);
}