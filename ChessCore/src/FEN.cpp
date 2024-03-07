#include "ChessCore.h"

#include <sstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
namespace FEN {
	bool isValidFEN(const std::string& FEN) {
		std::regex fenRegex("\\s*([rnbqkpRNBQKP1-8]+\\/){7}([rnbqkpRNBQKP1-8]+)\\s[bw]\\s((K?Q?k?q?)|(-))\\s(([a-h][1-8])|(-))\\s\\d+\\s\\d+\\s*");
		return std::regex_match(FEN, fenRegex) && isValidFENKingCount(FEN);
	}
	
	bool isValidFENBoard(const std::string& fenBoard) {
		std::regex fenBoardRegex("\\s*([rnbqkpRNBQKP1-8]+\\/){7}([rnbqkpRNBQKP1-8]+)\\s*");
		return std::regex_match(fenBoard, fenBoardRegex) && isValidFENKingCount(fenBoard);
	}
	
	bool isValidFENKingCount(const std::string& FEN) {
		int totalWhiteKings = 0;
		int totalBlackKings = 0;
		for(int i=0; i<FEN.length() && FEN[i] != ' '; i++) {
			if(FEN[i] == 'k') {
				totalBlackKings++;
			} else if (FEN[i] == 'K') {
				totalWhiteKings++;
			}
		}
		return totalBlackKings == 1 && totalWhiteKings == 1;
	}
	
	std::vector<std::string> getFENTokens(const std::string& FEN) {
		std::vector<std::string> fenTokens;
		if (isValidFEN(FEN)) {
			std::istringstream fenStream(FEN);
			std::string fenToken;    
			while (std::getline(fenStream, fenToken, ' ')) {
				fenTokens.push_back(fenToken);
			}
		} 
		return fenTokens;
	}
	
	std::vector<std::string> getFENBoardTokens(const std::string& FENBoard) {
		std::vector<std::string> fenBoardTokens;
		if (isValidFENBoard(FENBoard)) {
			std::istringstream fenBoardStream(FENBoard);
			std::string fenBoardToken;    
			while (std::getline(fenBoardStream, fenBoardToken, '/')) {
				fenBoardTokens.push_back(fenBoardToken);
			}
		}
		return fenBoardTokens;
	}
	
	Color_t getFENBoardCharColor(const char& fileChar) {
		if (islower(fileChar)) {
			return BLACK;
		} else {
			return WHITE;
		}
	}
	
	Piece_t getFENBoardCharPiece(const char& fileChar) {
		const char fileCharLower = tolower(fileChar);
		switch (fileCharLower) {
			case 'p':
				return PAWN;
			case 'n':
				return KNIGHT;
			case 'b':
				return BISHOP;
			case 'r':
				return ROOK;
			case 'q':
				return QUEEN;
			case 'k':
				return KING;
			default:
				return NOPIECE;
		}
	}
	
	char getFENPieceLabel(const Piece_t& p, const Color_t& c) {
		char label;
		switch (p) {
			case PAWN:
				label = 'p';
				break;
			case KNIGHT:
				label = 'n';
				break;
			case BISHOP:
				label = 'b';
				break;
			case ROOK:
				label = 'r';
				break;
			case QUEEN:
				label = 'q';
				break;
			case KING:
				label = 'k';
				break;
			default:
				label = 'x';
		}
		if (c) {
			label = std::toupper(label); 
		}
		return label;
	}
}
}