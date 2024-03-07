#include <catch2/catch_test_macros.hpp>
#include "ChessCore.h"

using namespace ChessCore::Color;

TEST_CASE("WHITE", "[Color_t]") {
	REQUIRE(WHITE == 1);
}

TEST_CASE("BLACK", "[Color_t]") {
	REQUIRE(BLACK == 0);
}