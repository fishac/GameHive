#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"

using namespace ChessCore;
using namespace ChessCore::Piece;

TEST_CASE("NOPIECE", "[Piece_t]") {
	REQUIRE(NOPIECE == 0);
}

TEST_CASE("PAWN", "[Piece_t]") {
	REQUIRE(PAWN == 1);
}

TEST_CASE("KNIGHT", "[Piece_t]") {
	REQUIRE(KNIGHT == 2);
}

TEST_CASE("BISHOP", "[Piece_t]") {
	REQUIRE(BISHOP == 3);
}

TEST_CASE("ROOK", "[Piece_t]") {
	REQUIRE(ROOK == 4);
}

TEST_CASE("QUEEN", "[Piece_t]") {
	REQUIRE(QUEEN == 5);
}

TEST_CASE("KING", "[Piece_t]") {
	REQUIRE(KING == 6);
}

TEST_CASE("NOPIECE NOT VALID PIECE", "[isValidPiece]") {
	REQUIRE(!Piece::isValidPiece(NOPIECE));
}

TEST_CASE("INVALID PIECE NOT VALID PIECE", "[isValidPiece]") {
	REQUIRE(!Piece::isValidPiece(7));
}

TEST_CASE("NOPIECE NOT VALID PROMOTION PIECE", "[isValidPromotionPiece]") {
	REQUIRE(!Piece::isValidPromotionPiece(NOPIECE));
}

TEST_CASE("PAWN NOT VALID PROMOTION PIECE", "[isValidPromotionPiece]") {
	REQUIRE(!Piece::isValidPromotionPiece(PAWN));
}

TEST_CASE("KING NOT VALID PROMOTION PIECE", "[isValidPromotionPiece]") {
	REQUIRE(!Piece::isValidPromotionPiece(KING));
}

TEST_CASE("BISHOP VALID PROMOTION PIECE", "[isValidPromotionPiece]") {
	REQUIRE(Piece::isValidPromotionPiece(BISHOP));
}
