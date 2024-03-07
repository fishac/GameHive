#include "ChessCore.h"
#include <regex>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
namespace MoveUtils {
	std::string getString(Move& m) {	
		std::string ret = Square::getString(m.from) + Square::getString(m.to);
		return ret;
	}
	
	std::string getString(ExtendedMove& m) {
		std::string ret = Square::getString(m.from) + Square::getString(m.to);
		if (m.promotionPiece != NOPIECE) {
			ret = ret + "=" + FEN::getFENPieceLabel(m.promotionPiece,WHITE);
		}
		return ret;
	}
	
	std::string getString(ExtendedMove& m, const Color_t& turnColor) {
		std::string ret = Square::getString(m.from) + Square::getString(m.to);
		if (m.promotionPiece != NOPIECE) {
			ret = ret + "=" + FEN::getFENPieceLabel(m.promotionPiece,turnColor);
		}
		return ret;
	}
	
	bool extendedMoveEquals(const ExtendedMove& m1, const ExtendedMove& m2) {
		return (
			m1.from == m2.from
			&& m1.to == m2.to 
			&& m1.promotionPiece == m2.promotionPiece
		);
	}
	
	ExtendedMove getExtendedMove(std::string moveString) {
		std::regex nonpromotionRegex("^[a-hA-H][1-8][a-hA-H][1-8]$");
		std::regex promotionRegex("^[a-hA-H][1-8][a-hA-H][1-8]=[kbrqKBRQ]$");
		if (std::regex_match(moveString, nonpromotionRegex)) {
			std::string from = moveString.substr(0,2);
			std::string to = moveString.substr(2,2);
			return {Square::getSquare(from),Square::getSquare(to),NOPIECE};
		} else if (std::regex_match(moveString, promotionRegex)) {
			std::string from = moveString.substr(0,2);
			std::string to = moveString.substr(2,2);
			return {Square::getSquare(from),Square::getSquare(to),FEN::getFENBoardCharPiece(moveString.at(5))};
		} else {
			return {NO_SQUARE,NO_SQUARE,NOPIECE};
		}
	}
}
}