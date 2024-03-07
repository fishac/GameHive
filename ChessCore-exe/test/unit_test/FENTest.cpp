#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"

using namespace ChessCore;
using namespace ChessCore::Color;
using namespace ChessCore::Piece;

TEST_CASE("INVALID FEN EMPTY BOARD", "[isValidFEN]") {
	std::string FEN = "8/8/8/8/8/8/8/8 w KQkq - 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("VALID FEN DEFAULT BOARD", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	REQUIRE(FEN::isValidFEN(FEN));
}

TEST_CASE("VALID FEN WITH EN PASSANT", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/P7/PPPPPPP/RNBQKBNR w KQkq a3 0 1";
	REQUIRE(FEN::isValidFEN(FEN));
}

TEST_CASE("VALID FEN NO CASTLE", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/8/8/8/8/P7/8/RNBQKBNR w - - 0 1";
	REQUIRE(FEN::isValidFEN(FEN));
}

TEST_CASE("EMPTY INVALID FEN", "[isValidFEN]") {
	std::string FEN = "";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("NONSENSE INVALID FEN", "[isValidFEN]") {
	std::string FEN = "abcd";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD NUMBER INVALID FULL FEN", "[isValidFEN]") {
	std::string FEN = "9/8/8/8/8/8/8/8 w KQkq e4 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD PIECE INVALID FULL FEN", "[isValidFEN]") {
	std::string FEN = "xnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD SLASHES INVALID FEN", "[isValidFEN]") {
	std::string FEN = "xnbqkbnr-pppppppp-8-8-8-8-PPPPPPPP-RNBQKBNR w KQkq - 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD ROW COUNT INVALID FEN", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD TURN COLOR INVALID FEN", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR a KQkq - 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD CASTLE RIGHTS INVALID FEN", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w aaAA - 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD EN PASSANT SQUARE INVALID FEN", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq a9 0 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD HALFMOVE CLOCK INVALID FEN", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - a 1";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("BAD FULLMOVE NUMBER INVALID FEN", "[isValidFEN]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 a";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("TOO MANY KINGS INVALID FEN", "[isValidFEN]") {
	std::string FEN = "3kk3/pppppppp/8/8/8/8/PPPPPPPP/3KK3 w KQkq - 0 a";
	REQUIRE(!FEN::isValidFEN(FEN));
}

TEST_CASE("EMPTY RETURN INVALID FEN", "[getFENTokens]") {
	std::string FEN = "";
	std::vector<std::string> ret = FEN::getFENTokens(FEN);
	REQUIRE(ret.empty());
}

TEST_CASE("SIX TOKENS FEN", "[getFENTokens]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::vector<std::string> ret = FEN::getFENTokens(FEN);
	REQUIRE(ret.size() == 6);
}

TEST_CASE("ZERO BOARD TOKENS INVALID FEN", "[getFENBoardTokens]") {
	std::string FEN = "";
	std::vector<std::string> ret = FEN::getFENBoardTokens(FEN);
	REQUIRE(ret.empty());
}

TEST_CASE("EIGHT BOARD TOKENS FEN", "[getFENBoardTokens]") {
	std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	std::vector<std::string> tokens = FEN::getFENTokens(FEN);
	std::vector<std::string> ret = FEN::getFENBoardTokens(tokens[0]);
	REQUIRE(ret.size() == 8);
}

TEST_CASE("BLACK COLOR PIECE", "[getFENBoardCharColor]") {
	char piece = 'p';
	REQUIRE(FEN::getFENBoardCharColor(piece) == BLACK);
}

TEST_CASE("WHITE COLOR PIECE", "[getFENBoardCharColor]") {
	char piece = 'P';
	REQUIRE(FEN::getFENBoardCharColor(piece) == WHITE);
}

TEST_CASE("VALID PIECE", "[getFENBoardCharPiece]") {
	char piece = 'p';
	REQUIRE(FEN::getFENBoardCharPiece(piece) == PAWN);
}

TEST_CASE("INVALID PIECE NOPIECE", "[getFENBoardCharPiece]") {
	char piece = 'x';
	REQUIRE(FEN::getFENBoardCharPiece(piece) == NOPIECE);
}