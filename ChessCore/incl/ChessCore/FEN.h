#ifndef FEN_H
#define FEN_H

#include "Types.h"
#include "Color.h"
#include "Piece.h"

#include <string>
#include <vector>

namespace ChessCore {
namespace FEN {
	bool isValidFEN(const std::string& FEN);
	bool isValidFENKingCount(const std::string& FEN);
	bool isValidFENBoard(const std::string& fenBoard);
	std::vector<std::string> getFENTokens(const std::string& FEN);
	std::vector<std::string> getFENBoardTokens(const std::string& FEN);
	Color_t getFENBoardCharColor(const char& fileChar);
	Piece_t getFENBoardCharPiece(const char& fileChar);
	char getFENPieceLabel(const Piece_t& p, const Color_t& c);
}
}


#endif // FEN_H 