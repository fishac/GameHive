#include "ChessCore.h"
#include <regex>
#include <string>
#include <iostream>

static BoardMask_t notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
static BoardMask_t notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

namespace ChessCore {
namespace Square {
	Square_t aFile = 0x0101010101010101;
	Square_t allSquares = 0xFFFFFFFFFFFFFFFF;
	
	Square_t getSquare(const int& file, const int& rank) {
		return ((Square_t)1) << (rank*8 + file);
	}

	Square_t getSquare(const int& idx) {
		return ((Square_t)1) << idx;
	}

	Square_t getSquare(const std::string& str) {
		std::regex sqRegex("[a-h][1-8]");
		if (std::regex_match(str, sqRegex) && str.length() == 2) {
			int file = ((int) (str.at(0)))-97;
			int rank = atoi(&(str.at(1)))-1;
			return getSquare(file,rank);
		} else {
			return 0;
		}
	}
	
	int getIndex(const Square_t& s) {
		switch (s) {
			case ((Square_t)1):
				return 0;
			case (((Square_t)1)<<1):
				return 1;
			case (((Square_t)1)<<2):
				return 2;
			case (((Square_t)1)<<3):
				return 3;
			case (((Square_t)1)<<4):
				return 4;
			case (((Square_t)1)<<5):
				return 5;
			case (((Square_t)1)<<6):
				return 6;
			case (((Square_t)1)<<7):
				return 7;
			case (((Square_t)1)<<8):
				return 8;
			case (((Square_t)1)<<9):
				return 9;
			case (((Square_t)1)<<10):
				return 10;
			case (((Square_t)1)<<11):
				return 11;
			case (((Square_t)1)<<12):
				return 12;
			case (((Square_t)1)<<13):
				return 13;
			case (((Square_t)1)<<14):
				return 14;
			case (((Square_t)1)<<15):
				return 15;
			case (((Square_t)1)<<16):
				return 16;
			case (((Square_t)1)<<17):
				return 17;
			case (((Square_t)1)<<18):
				return 18;
			case (((Square_t)1)<<19):
				return 19;
			case (((Square_t)1)<<20):
				return 20;
			case (((Square_t)1)<<21):
				return 21;
			case (((Square_t)1)<<22):
				return 22;
			case (((Square_t)1)<<23):
				return 23;
			case (((Square_t)1)<<24):
				return 24;
			case (((Square_t)1)<<25):
				return 25;
			case (((Square_t)1)<<26):
				return 26;
			case (((Square_t)1)<<27):
				return 27;
			case (((Square_t)1)<<28):
				return 28;
			case (((Square_t)1)<<29):
				return 29;
			case (((Square_t)1)<<30):
				return 30;
			case (((Square_t)1)<<31):
				return 31;
			case (((Square_t)1)<<32):
				return 32;
			case (((Square_t)1)<<33):
				return 33;
			case (((Square_t)1)<<34):
				return 34;
			case (((Square_t)1)<<35):
				return 35;
			case (((Square_t)1)<<36):
				return 36;
			case (((Square_t)1)<<37):
				return 37;
			case (((Square_t)1)<<38):
				return 38;
			case (((Square_t)1)<<39):
				return 39;
			case (((Square_t)1)<<40):
				return 40;
			case (((Square_t)1)<<41):
				return 41;
			case (((Square_t)1)<<42):
				return 42;
			case (((Square_t)1)<<43):
				return 43;
			case (((Square_t)1)<<44):
				return 44;
			case (((Square_t)1)<<45):
				return 45;
			case (((Square_t)1)<<46):
				return 46;
			case (((Square_t)1)<<47):
				return 47;
			case (((Square_t)1)<<48):
				return 48;
			case (((Square_t)1)<<49):
				return 49;
			case (((Square_t)1)<<50):
				return 50;
			case (((Square_t)1)<<51):
				return 51;
			case (((Square_t)1)<<52):
				return 52;
			case (((Square_t)1)<<53):
				return 53;
			case (((Square_t)1)<<54):
				return 54;
			case (((Square_t)1)<<55):
				return 55;
			case (((Square_t)1)<<56):
				return 56;
			case (((Square_t)1)<<57):
				return 57;
			case (((Square_t)1)<<58):
				return 58;
			case (((Square_t)1)<<59):
				return 59;
			case (((Square_t)1)<<60):
				return 60;
			case (((Square_t)1)<<61):
				return 61;
			case (((Square_t)1)<<62):
				return 62;
			case (((Square_t)1)<<63):
				return 63;
			default:
				return -1;
		}
	}

	int getRank(const Square_t& s) {
		return getIndex(s)/8;
	}

	int getFile(const Square_t& s) {
		return getIndex(s)%8;
	}
	
	int getIndex(const int& file, const int& rank) {
		return rank*8+file;
	}
		
	int getRank(const int& index) {
		return index/8;
	}
	
	int getFile(const int& index) {
		return index%8;
	}
	
	std::string getString(const Square_t& s) {
		if (s == NO_SQUARE) {
			return "xx";
		} else {
			int idx = getIndex(s);
			int rank = idx / 8;
			int file = idx % 8;
			char fileChar = ((char) file+97);
			std::string ret;
			ret += fileChar;
			ret += std::to_string(rank+1);
			return ret;
		}
	}
	
	std::string getString(const int& idx) {
		return getString(getSquare(idx));
	}
	
	Color_t getShade(const Square_t& s) {
		int idx = getIndex(s);
		return (getRank(idx)%2) != (getFile(idx)%2);
	}

	Square_t aRookStartingSquare(const Color_t& c) {
		return (c * getSquare(0,0)) | (!c * getSquare(0,7));
	}

	Square_t hRookStartingSquare(const Color_t& c) {
		return (c * getSquare(7,0)) | (!c * getSquare(7,7));
	}

	Square_t aRookCastleTarget(const Color_t& c) {
		return (c * getSquare(3,0)) | (!c * getSquare(3,7));
	}

	Square_t hRookCastleTarget(const Color_t& c) {
		return (c * getSquare(5,0)) | (!c * getSquare(5,7));
	}
	
	std::vector<Square_t> getDefaultStartingWhitePawnSquares() {
		return {
			getSquare(0,1), 
			getSquare(1,1),
			getSquare(2,1),
			getSquare(3,1),
			getSquare(4,1),
			getSquare(5,1),
			getSquare(6,1),
			getSquare(7,1) 
		};
	}

	std::vector<Square_t> getDefaultStartingWhiteKnightSquares() {
		return {
			getSquare("b1"), 
			getSquare("g1")
		};
	}

	std::vector<Square_t> getDefaultStartingWhiteBishopSquares() {
		return {
			getSquare(2,0), 
			getSquare(5,0)
		};
	}

	std::vector<Square_t> getDefaultStartingWhiteRookSquares() {
		return {
			getSquare(0,0),
			getSquare(7,0)
		};
	}

	Square_t getDefaultStartingWhiteQueenSquare() {
		return getSquare(3,0);
	}

	Square_t getDefaultStartingWhiteKingSquare() {
		return getSquare(4,0);
	}

	std::vector<Square_t> getDefaultStartingBlackPawnSquares() {
		return {
			getSquare(0,6), 
			getSquare(1,6),
			getSquare(2,6),
			getSquare(3,6),
			getSquare(4,6),
			getSquare(5,6),
			getSquare(6,6),
			getSquare(7,6) 
		};
	}

	std::vector<Square_t> getDefaultStartingBlackKnightSquares() {
		return {
			getSquare(1,7), 
			getSquare(6,7)
		};
	}

	std::vector<Square_t> getDefaultStartingBlackBishopSquares() {
		return {
			getSquare(2,7), 
			getSquare(5,7)
		};
	}

	std::vector<Square_t> getDefaultStartingBlackRookSquares() {
		return {
			getSquare(0,7), 
			getSquare(7,7)
		};
	}

	Square_t getDefaultStartingBlackQueenSquare() {
		return getSquare(3,7);
	}

	Square_t getDefaultStartingBlackKingSquare() {
		return getSquare(4,7);
	}
	
	Square_t getDefaultStartingKingSquare(const Color_t& c) {
		return (c*getDefaultStartingWhiteKingSquare()) | (!c*getDefaultStartingBlackKingSquare());
	}

	BoardMask_t n(const BoardMask_t& bm) {
		return  bm << 8;
	}

	BoardMask_t ne(const BoardMask_t& bm) {
		return (bm << 9) & notAFile;
	}

	BoardMask_t e(const BoardMask_t& bm) {
		return (bm << 1) & notAFile;
	}

	BoardMask_t se(const BoardMask_t& bm) {
		return (bm >> 7) & notAFile;
	}

	BoardMask_t s(const BoardMask_t& bm) {
		return bm >> 8;
	}

	BoardMask_t sw(const BoardMask_t& bm) {
		return (bm >> 9) & notHFile;
	}

	BoardMask_t w(const BoardMask_t& bm) {
		return (bm >> 1) & notHFile;
	}

	BoardMask_t nw(const BoardMask_t& bm) {
		return (bm << 7)  & notHFile;
	}

	BoardMask_t nn(const BoardMask_t& bm) {
		return  bm << 16;
	}

	BoardMask_t ss(const BoardMask_t& bm) {
		return  bm >> 16;
	}

	BoardMask_t ee(const BoardMask_t& bm) {
		return ((bm << 1) & notAFile) << 1 & notAFile;
	}

	BoardMask_t ww(const BoardMask_t& bm) {
		return ((bm >> 1) & notHFile) >> 1 & notHFile;
	}

	std::vector<Square_t> getSquares(const BoardMask_t& bm) {
		std::vector<Square_t> ret;
		Square_t testSquare = (Square_t) 1;
		BoardMask_t bm_ = bm;
		while(bm_ != EMPTY_BOARD) {
			if ((bm_ & testSquare) != EMPTY_BOARD) {
				ret.push_back(testSquare);
				bm_ &= ~testSquare;
			}
			testSquare <<= 1;
		}
		return ret;
	}
	
	int getNumSquares(BoardMask_t bm) {
		int ret = 0;
		Square_t testSquare = (Square_t) 1;
		while(bm != EMPTY_BOARD) {
			if ((bm & testSquare) != EMPTY_BOARD) {
				ret++;
				bm &= ~testSquare;
			}
			testSquare <<= 1;
		}
		return ret;
	}

	bool onSecondRank(const Square_t& sq) {
		return (sq & 0x000000000000FF00) != 0;
	}

	bool onSeventhRank(const Square_t& sq) {
		return (sq & 0x00FF000000000000) != 0;
	}

	bool onFirstRank(const Square_t& sq) {
		return (sq & 0x00000000000000FF) != 0;
	}

	bool onEighthRank(const Square_t& sq) {
		return (sq & 0xFF00000000000000) != 0;
	}
	
	bool onPromotionRank(const Square_t& sq, const Color_t& c) {
		return (c && onEighthRank(sq)) || (!c && onFirstRank(sq));
	}

	BoardMask_t eCastleCrossingSquares(const Color_t& c) {
		return (c * 0x0000000000000060) | (!c * 0x6000000000000000);
	}

	BoardMask_t wCastleCrossingSquares(const Color_t& c) {
		return (c * 0x000000000000000C) | (!c * 0x0C00000000000000);
	}

	BoardMask_t eCastleBetweenSquares(const Color_t& c) {
		return (c * 0x0000000000000060) | (!c * 0x6000000000000000);
	}

	BoardMask_t wCastleBetweenSquares(const Color_t& c) {
		return (c * 0x000000000000000E) | (!c * 0x0E00000000000000);
	}
}
}
