#ifndef SQUARE_H
#define SQUARE_H

#include "Types.h" 

#include <string>
#include <vector>

namespace ChessCore {
namespace Square {
	extern Square_t aFile;
	extern Square_t allSquares;
	Square_t getSquare(const int& file, const int& rank);
	Square_t getSquare(const int& idx);
	Square_t getSquare(const std::string& str);
	int getIndex(const Square_t& s);
	int getIndex(const int& file, const int& rank);
	int getRank(const Square_t& s);
	int getFile(const Square_t& s);
	int getRank(const int& s);
	int getFile(const int& s);
	std::string getString(const Square_t& s);
	Color_t getShade(const Square_t& s);
	Square_t aRookStartingSquare(const Color_t& c);
	Square_t hRookStartingSquare(const Color_t& c);
	Square_t aRookCastleTarget(const Color_t& c);
	Square_t hRookCastleTarget(const Color_t& c);
	std::vector<Square_t> getDefaultStartingWhitePawnSquares();
	std::vector<Square_t> getDefaultStartingWhiteKnightSquares();
	std::vector<Square_t> getDefaultStartingWhiteBishopSquares();
	std::vector<Square_t> getDefaultStartingWhiteRookSquares();
	Square_t getDefaultStartingWhiteQueenSquare();
	Square_t getDefaultStartingWhiteKingSquare();
	std::vector<Square_t> getDefaultStartingBlackPawnSquares();
	std::vector<Square_t> getDefaultStartingBlackKnightSquares();
	std::vector<Square_t> getDefaultStartingBlackBishopSquares();
	std::vector<Square_t> getDefaultStartingBlackRookSquares();
	Square_t getDefaultStartingBlackQueenSquare();
	Square_t getDefaultStartingBlackKingSquare();
	Square_t getDefaultStartingKingSquare(const Color_t& c);
	// Computing squares in cardinal directions of squares containing pieces
	// Args: boards representing locations of pieces
	// Return values: boards representing squares in the specified directions
	// of the arg pieces, avoiding erroneously wrapping around ranks
	BoardMask_t n(const BoardMask_t& bm);
	BoardMask_t ne(const BoardMask_t& bm);
	BoardMask_t e(const BoardMask_t& bm);
	BoardMask_t se(const BoardMask_t& bm);
	BoardMask_t s(const BoardMask_t& bm);
	BoardMask_t sw(const BoardMask_t& bm);
	BoardMask_t w(const BoardMask_t& bm);
	BoardMask_t nw(const BoardMask_t& bm);
	// Computing squares two jumps in a cardinal direction of squares containing pieces
	// Args: boards representing locations of pieces
	// Return values: boards representing squares in the specified directions
	// of the arg pieces, avoiding erroneously wrapping around ranks
	BoardMask_t nn(const BoardMask_t& bm);
	BoardMask_t ss(const BoardMask_t& bm);
	BoardMask_t ee(const BoardMask_t& bm);
	BoardMask_t ww(const BoardMask_t& bm);
	// Get vector of squares represented by 1 bits in BoardMask_T
	// Args: a board
	// Return value: vector of squares 
	std::vector<Square_t> getSquares(const BoardMask_t& bm);
	int getNumSquares(BoardMask_t bm);
	// Determine if a given square is on a given rank
	// Args: a square
	// Return balue: bool 
	bool onSecondRank(const Square_t& sq);
	bool onSeventhRank(const Square_t& sq);
	bool onFirstRank(const Square_t& sq);
	bool onEighthRank(const Square_t& sq);
	bool onPromotionRank(const Square_t& sq, const Color_t& c);
	// Get a mask of squares the King must cross to castle
	BoardMask_t eCastleCrossingSquares(const Color_t& c);
	BoardMask_t wCastleCrossingSquares(const Color_t& c);
	// Get a mask of squares between the king and rook starting squares
	BoardMask_t eCastleBetweenSquares(const Color_t& c);
	BoardMask_t wCastleBetweenSquares(const Color_t& c);
}
}

#endif // SQUARE_H 