#include "ChessCore.h"

#include <algorithm>
#include <iostream>

using namespace ChessCore::Color;
using namespace ChessCore::Piece;

namespace ChessCore {
BoardState::BoardState() {
	setDefaultStartingState();
}

BoardState::BoardState(const bool& setupDefaultStartingPosition) {
	if (setupDefaultStartingPosition) {
		setDefaultStartingState();
	} else {
		clearBoard();
	}
}

BoardState::BoardState(const std::string& FEN) {
	setFEN(FEN);
}

void BoardState::setDefaultStartingState() {
	clearBoard();
	
	initializeDefaultWhitePieces();
	initializeDefaultBlackPieces();
	initializeDerivativeData();

	turnColor = WHITE;
	
	kSideCastleRights = {true, true};
	qSideCastleRights = {true, true};
	
	halfmoveClock = 0;
	moveNumber = 1;
	
	initializeMoveGenerationArrays();
	initializeZobristBoardHash();
	updateLegality();
	appendBoardStateHistory();
}

bool BoardState::setFEN(const std::string& FEN) {
	clearBoard();
	if (FEN::isValidFEN(FEN)) {
		std::vector<std::string> fenTokens = FEN::getFENTokens(FEN);
		std::vector<std::string> fenBoardTokens = FEN::getFENBoardTokens(fenTokens.at(0));
		int file;
		for (int rankIdx = 0; rankIdx < 8; rankIdx++) {
			file = 0;
			for (int fileIdx = 0; fileIdx < fenBoardTokens[rankIdx].size(); fileIdx++) {
				char fileChar = fenBoardTokens[rankIdx][fileIdx];
				if (isdigit(fileChar)) {
					file += atoi(&fileChar);
				} else {
					const Color_t c = FEN::getFENBoardCharColor(fileChar);
					const Piece_t p = FEN::getFENBoardCharPiece(fileChar);
					getPieces(c)[Square::getIndex(file,7-rankIdx)] = p;
					file++;
				}
			}
		}
		
		turnColor = fenTokens.at(1) == "w";
		
		std::string castleRights = fenTokens.at(2);
		kSideCastleRights[WHITE] = castleRights.find("K") != std::string::npos;
		qSideCastleRights[WHITE] = castleRights.find("Q") != std::string::npos;
		kSideCastleRights[BLACK] = castleRights.find("k") != std::string::npos;
		qSideCastleRights[BLACK] = castleRights.find("q") != std::string::npos;
		
		if (fenTokens.at(3) == "-") {
			enPassantableSquare = NO_SQUARE;
		} else {
			enPassantableSquare = Square::getSquare(fenTokens.at(3));
		}
		
		halfmoveClock = stoi(fenTokens.at(4));
		moveNumber = stoi(fenTokens.at(5));
		activePly = 0;
		totalPlies = 0;
		
		initializeDerivativeData();
		initializeMoveGenerationArrays();
		initializeZobristBoardHash();
		updateLegality();
		appendBoardStateHistory();
		return true;
	} else {
		return false;
	}
}

void BoardState::clearBoard() {
	clearAllPieces();
	
	whiteKingSquare = NO_SQUARE;
	blackKingSquare = NO_SQUARE;
	
	whitePiecesMask = EMPTY_BOARD;
	blackPiecesMask = EMPTY_BOARD;
	
	enPassantableSquare = NO_SQUARE;
	
	kingAttackers.clear();
	kingAttackers.reserve(2);

	whiteDefendedPiecesMask = NO_SQUARE;
	blackDefendedPiecesMask = NO_SQUARE;
	whitePossibleDefendedPiecesMask = NO_SQUARE;
	blackPossibleDefendedPiecesMask = NO_SQUARE;
	kingPierceSquare = NO_SQUARE;
	
	initializeMoveGenerationArrays();
	
	checkStatus = false;
	checkmateStatus = false;
	stalemateStatus = false;
	
	turnColor = WHITE;
	
	kSideCastleRights[WHITE] = false;
	qSideCastleRights[WHITE] = false;
	kSideCastleRights[BLACK] = false;
	qSideCastleRights[BLACK] = false;
	
	halfmoveClock = 0;
	moveNumber = 0;
	activePly = 0;
	totalPlies = 0;
	
	zobristBoardHash = (uint64_t) 0;

	moveHistory.clear();
	boardStateHistory.clear();
}


BoardState::BoardState(const BoardState& bs) {
	whitePieces = bs.whitePieces;
	blackPieces = bs.blackPieces;
	whiteKingSquare = bs.whiteKingSquare;
	blackKingSquare = bs.blackKingSquare;
	numWhitePieces = bs.numWhitePieces;
	numBlackPieces = bs.numBlackPieces;
	whitePieceMasks = bs.whitePieceMasks;
	blackPieceMasks = bs.blackPieceMasks;
	whitePiecesMask = bs.whitePiecesMask;
	blackPiecesMask = bs.blackPiecesMask;
	pinningPieces = bs.pinningPieces;
	enPassantableSquare = bs.enPassantableSquare;
	visibility = bs.visibility;
	xRayVisibility = bs.xRayVisibility;
	legalMoves = bs.legalMoves;
	
	checkStatus = bs.checkStatus;
	checkmateStatus = bs.checkmateStatus;
	stalemateStatus = bs.stalemateStatus;
	
	turnColor = bs.turnColor;
	
	kSideCastleRights = bs.kSideCastleRights;
	qSideCastleRights = bs.qSideCastleRights;
	
	halfmoveClock = bs.halfmoveClock;
	moveNumber = bs.moveNumber;
	activePly = bs.activePly;
	totalPlies = bs.totalPlies;
	
	zobristBoardHash = bs.zobristBoardHash;

	moveHistory = bs.moveHistory;
	boardStateHistory = bs.boardStateHistory;
}

std::string BoardState::toFEN() {
	std::string fenString = "";
	Square_t s;
	Piece_t p;
	int consecutiveEmpty = 0;
	for(int rank=7; rank >= 0; rank--) {
		for(int file=0; file < 8; file++) {
			s = Square::getSquare(file,rank);
			p = getPieceOnSquare(s);
			if (p == NOPIECE) {
				consecutiveEmpty++;
			} else {
				if (consecutiveEmpty != 0) {
					fenString = fenString + std::to_string(consecutiveEmpty);
				}
				consecutiveEmpty = 0;
				fenString = fenString + FEN::getFENPieceLabel(p,getColorOnSquare(s));
			}
		}
		if (consecutiveEmpty != 0) {
			fenString = fenString + std::to_string(consecutiveEmpty);
		}
		if (rank != 0) {
			fenString = fenString + "/";
		}
		consecutiveEmpty = 0;
	}
	fenString = fenString + " ";
	if (turnColor) {
		fenString = fenString + "w ";
	} else {
		fenString = fenString + "b ";
	}
	bool anyCastleRights = false;
	if (kSideCastleRights[WHITE]) {
		fenString = fenString + "K";
		anyCastleRights = true;
	}
	if (qSideCastleRights[WHITE]) {
		fenString = fenString + "Q";
		anyCastleRights = true;
	}
	if (kSideCastleRights[WHITE]) {
		fenString = fenString + "k";
		anyCastleRights = true;
	}
	if (qSideCastleRights[BLACK]) {
		fenString = fenString + "q";
		anyCastleRights = true;
	}
	if (!anyCastleRights) {
		fenString = fenString + "-";
	}
	fenString = fenString + " ";
	if (enPassantableSquare != NO_SQUARE) {
		fenString = fenString + Square::getString(enPassantableSquare);
	} else {
		fenString = fenString + "-";
	}
	fenString = fenString + " " + std::to_string(halfmoveClock) + " " + std::to_string(moveNumber);
	return fenString;
}

Piece_t BoardState::getPieceOnSquare(const Square_t& s) {
	int sq_idx = Square::getIndex(s);
	Piece_t p = whitePieces[sq_idx];
	if (p == NOPIECE) {
		return blackPieces[sq_idx];
	} else { 
		return p;
	}
}

Piece_t BoardState::getPieceOnSquareIndex(const int& sq_idx) {
	Piece_t p = whitePieces[sq_idx];
	if (!Piece::isValidPiece(p)) {
		p = blackPieces[sq_idx];
	} 
	if (Piece::isValidPiece(p)) { 
		return p;
	} else {
		return NOPIECE;
	}
}

Color_t BoardState::getColorOnSquare(const Square_t& s) {
	int sq_idx = Square::getIndex(s);
	if (blackPieces[sq_idx] != NOPIECE) {
		return BLACK;
	} else {
		return WHITE;
	}
}
	
Color_t BoardState::getTurnColor() {
	return turnColor;
}

Piece_t BoardState::getPiece(const Square_t& sq, const Color_t& c) {
	int sq_idx = Square::getIndex(sq);
	if (c) {
		return whitePieces[sq_idx];
	} else {
		return blackPieces[sq_idx];
	}
}

void BoardState::updateCheckStatus() {
	// If the king is attacked, turnColor is in check
	checkStatus = (kingAttackers.size() > 0);
}

void BoardState::updateCheckmateStatus() {
	// If the king is attacked and turnColor has no legal moves, turnColor is checkmated
	checkmateStatus = (
		(kingAttackers.size() > 0)
		&& (getLegalMovesMask() == EMPTY_BOARD)
	);
}

bool BoardState::getCheckStatus() {
	return checkStatus;
}

bool BoardState::getCheckmateStatus() {
	return checkmateStatus;
}

bool BoardState::getStalemateStatus() {
	return stalemateStatus;
}

const std::array<Piece_t,64>& BoardState::getWhitePieces() {
	return whitePieces;
}

const std::array<Piece_t,64>& BoardState::getBlackPieces() {
	return blackPieces;
}

std::vector<Square_t> BoardState::getWhitePawnSquares() {
	return Square::getSquares(whitePieceMasks[PAWN]);
}

std::vector<Square_t> BoardState::getBlackPawnSquares() {
	return Square::getSquares(blackPieceMasks[PAWN]);
}

std::vector<Square_t> BoardState::getWhiteKnightSquares() {
	return Square::getSquares(whitePieceMasks[KNIGHT]);
}

std::vector<Square_t> BoardState::getBlackKnightSquares() {
	return Square::getSquares(blackPieceMasks[KNIGHT]);
}

std::vector<Square_t> BoardState::getWhiteBishopSquares() {
	return Square::getSquares(whitePieceMasks[BISHOP]);
}

std::vector<Square_t> BoardState::getBlackBishopSquares() {
	return Square::getSquares(blackPieceMasks[BISHOP]);
}

std::vector<Square_t> BoardState::getWhiteRookSquares() {
	return Square::getSquares(whitePieceMasks[ROOK]);
}

std::vector<Square_t> BoardState::getBlackRookSquares() {
	return Square::getSquares(blackPieceMasks[ROOK]);
}

std::vector<Square_t> BoardState::getWhiteQueenSquares() {
	return Square::getSquares(whitePieceMasks[QUEEN]);
}

std::vector<Square_t> BoardState::getBlackQueenSquares() {
	return Square::getSquares(blackPieceMasks[QUEEN]);
}

Square_t BoardState::getWhiteKingSquare() {
	return whiteKingSquare;
}

Square_t BoardState::getBlackKingSquare() {
	return blackKingSquare;
}

const int& BoardState::getNumWhitePawns() {
	return numWhitePieces[PAWN];
}

const int& BoardState::getNumWhiteKnights() {
	return numWhitePieces[KNIGHT];
}

const int& BoardState::getNumWhiteBishops() {
	return numWhitePieces[BISHOP];
}

const int& BoardState::getNumWhiteRooks() {
	return numWhitePieces[ROOK];
}

const int& BoardState::getNumWhiteQueens() {
	return numWhitePieces[QUEEN];
}

const int& BoardState::getNumBlackPawns() {
	return numBlackPieces[PAWN];
}

const int& BoardState::getNumBlackKnights() {
	return numBlackPieces[KNIGHT];
}

const int& BoardState::getNumBlackBishops() {
	return numBlackPieces[BISHOP];
}

const int& BoardState::getNumBlackRooks() {
	return numBlackPieces[ROOK];
}

const int& BoardState::getNumBlackQueens() {
	return numBlackPieces[QUEEN];
}

const BoardMask_t& BoardState::getWhitePawnMask() {
	return whitePieceMasks[PAWN];
}

const BoardMask_t& BoardState::getWhiteKnightMask() {
	return whitePieceMasks[KNIGHT];
}

const BoardMask_t& BoardState::getWhiteBishopMask() {
	return whitePieceMasks[BISHOP];
}

const BoardMask_t& BoardState::getWhiteRookMask() {
	return whitePieceMasks[ROOK];
}

const BoardMask_t& BoardState::getWhiteQueenMask() {
	return whitePieceMasks[QUEEN];
}

const BoardMask_t& BoardState::getBlackPawnMask() {
	return blackPieceMasks[PAWN];
}

const BoardMask_t& BoardState::getBlackKnightMask() {
	return blackPieceMasks[KNIGHT];
}

const BoardMask_t& BoardState::getBlackBishopMask() {
	return blackPieceMasks[BISHOP];
}

const BoardMask_t& BoardState::getBlackRookMask() {
	return blackPieceMasks[ROOK];
}

const BoardMask_t& BoardState::getBlackQueenMask() {
	return blackPieceMasks[QUEEN];
}

void BoardState::reportPieceSquares() {
	std::cout << "Board Piece Locations" << std::endl;
	std::cout << "FEN: " << toFEN() << std::endl;
	std::cout << "White:" << std::endl;
	std::cout << "\tPawns: ";
	for (int i=0; i<64; i++) {
		if (whitePieces[i] == PAWN) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tKnights: ";
	for (int i=0; i<64; i++) {
		if (whitePieces[i] == KNIGHT) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tBishops: ";
	for (int i=0; i<64; i++) {
		if (whitePieces[i] == BISHOP) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tRooks: ";
	for (int i=0; i<64; i++) {
		if (whitePieces[i] == ROOK) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tQueens: ";
	for (int i=0; i<64; i++) {
		if (whitePieces[i] == QUEEN) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tKing: ";
	for (int i=0; i<64; i++) {
		if (whitePieces[i] == KING) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "Black:" << std::endl;
	std::cout << "\tPawns: ";
	for (int i=0; i<64; i++) {
		if (blackPieces[i] == PAWN) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tKnights: ";
	for (int i=0; i<64; i++) {
		if (blackPieces[i] == KNIGHT) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tBishops: ";
	for (int i=0; i<64; i++) {
		if (blackPieces[i] == BISHOP) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tRooks: ";
	for (int i=0; i<64; i++) {
		if (blackPieces[i] == ROOK) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tQueens: ";
	for (int i=0; i<64; i++) {
		if (blackPieces[i] == QUEEN) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "\tKing: ";
	for (int i=0; i<64; i++) {
		if (blackPieces[i] == KING) {
			std::cout << Square::getString(Square::getSquare(i)) << ", ";
		}
	}
	std::cout << std::endl;
}

void BoardState::reportCastleRights() {
	std::cout << "Castle Rights" << std::endl;
	std::cout << "White K: " << kSideCastleRights[WHITE] << ", Q: " << qSideCastleRights[WHITE] << std::endl;
	std::cout << "Black K: " << kSideCastleRights[BLACK] << ", Q: " << qSideCastleRights[BLACK] << std::endl;
}

/*
void BoardState::reportInternalState() {
	std::cout << "xRayVisibility: " << std::endl;
	for (auto kv = xRayVisibility.begin(); kv != xRayVisibility.end(); ++kv) {
		std::vector<Square_t> toSquares = Square::getSquares(kv->second);
		for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
			std::cout << "\t" << Square::getString(kv->first) << " " << Square::getString(*iter) << std::endl;
		}
	}
	
	std::cout << "visibility[WHITE]: " << std::endl;
	for (auto kv = whiteVisibility.begin(); kv != whiteVisibility.end(); ++kv) {
		std::vector<Square_t> toSquares = Square::getSquares(kv->second);
		for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
			std::cout << "\t" << Square::getString(kv->first) << " " << Square::getString(*iter) << std::endl;
		}
	}
	
	std::cout << "visibility[BLACK]: " << std::endl;
	for (auto kv = blackVisibility.begin(); kv != blackVisibility.end(); ++kv) {
		std::vector<Square_t> toSquares = Square::getSquares(kv->second);
		for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
			std::cout << "\t" << Square::getString(kv->first) << " " << Square::getString(*iter) << std::endl;
		}
	}
	
	std::cout << "legalMoves: " << std::endl;
	for (auto kv = getLegalMoves(turnColor).begin(); kv != getLegalMoves(turnColor).end(); ++kv) {
		std::vector<Square_t> toSquares = Square::getSquares(kv->second);
		for (auto iter = toSquares.begin(); iter != toSquares.end(); ++iter) {
			std::cout << "\t" << Square::getString(kv->first) << " " << Square::getString(*iter) << std::endl;
		}
	}
	
	std::cout << "kingAttackers: ";
	for (auto iter = kingAttackers.begin(); iter != kingAttackers.end(); ++iter) {
		std::cout << Square::getString(*iter) << ", ";
	}
	std::cout << std::endl;
	
	std::cout << "kSideCastleRights[WHITE]: " << whiteKSideCastleRights << std::endl;
	std::cout << "qSideCastleRights[WHITE]: " << whiteQSideCastleRights << std::endl;
	std::cout << "kSideCastleRights[BLACK]: " << blackKSideCastleRights << std::endl;
	std::cout << "qSideCastleRights[BLACK]: " << blackQSideCastleRights << std::endl;
}
*/

int BoardState::getHalfmoveClock() {
	return halfmoveClock;
}

int BoardState::getMoveNumber() {
	return moveNumber;
}

Square_t BoardState::getEnPassantableSquare() {
	return enPassantableSquare;
}

Square_t BoardState::getEnPassantCaptureSquare() {
	if (turnColor) {
		return Square::s(enPassantableSquare);
	} else {
		return Square::n(enPassantableSquare);
	}
}

int BoardState::getActivePly() {
	return activePly;
}

MoveRecord BoardState::getActivePreviousMoveRecord() {
	return moveHistory.at(activePly);
}

int BoardState::getNumWhitePassedPawns() {
	int num = 0;
	for(int i=0; i<64; i++) {
		if (whitePieces[i] == PAWN) {
			int file = Square::getFile(i);
			int rank = Square::getRank(i);
			BoardMask_t pawnFile = Square::aFile << file;
			BoardMask_t relevantFiles = (
				Square::w(pawnFile) | pawnFile | Square::e(pawnFile)
			);
			BoardMask_t relevantRanks = Square::allSquares << (rank*8);
			if (((relevantRanks & relevantFiles) & blackPieceMasks[PAWN]) == NO_SQUARE) {
				num++;
			}
		}
	}
	return num;
}

int BoardState::getNumBlackPassedPawns() {
	int num = 0;
	for(int i=0; i<64; i++) {
		if (whitePieces[i] == PAWN) {
			int file = Square::getFile(i);
			int rank = Square::getRank(i);
			BoardMask_t pawnFile = Square::aFile << file;
			BoardMask_t relevantFiles = (
				Square::w(pawnFile) | pawnFile | Square::e(pawnFile)
			);
			BoardMask_t relevantRanks = Square::allSquares >> (rank*8);
			if (((relevantRanks & relevantFiles) & whitePieceMasks[PAWN]) == NO_SQUARE) {
				num++;
			}
		}
	}
	return num;
}

int BoardState::getNumWhiteDoubledPawns() {
	int num = 0;
	for(int i=0; i<8; i++) {
		BoardMask_t pawnFile = Square::aFile << i;
		BoardMask_t pawnsOnFile = (pawnFile & whitePieceMasks[PAWN]);
		if (
			((pawnFile & whitePieceMasks[PAWN]) != NO_SQUARE)
			&& (pawnsOnFile != NO_SQUARE && Square::getIndex(pawnsOnFile) == -1)
		) {
		// If there is at least 1 pawn and the mask does not resolve to a single square
			num++;
		}
	}
	return num;
}

int BoardState::getNumBlackDoubledPawns() {
	int num = 0;
	for(int i=0; i<8; i++) {
		BoardMask_t pawnFile = Square::aFile << i;
		BoardMask_t pawnsOnFile = (pawnFile & blackPieceMasks[PAWN]);
		if (
			((pawnFile & blackPieceMasks[PAWN]) != NO_SQUARE)
			&& (pawnsOnFile != NO_SQUARE && Square::getIndex(pawnsOnFile) == -1)
		) {
		// If there is at least 1 pawn and the mask does not resolve to a single square
			num++;
		}
	}
	return num;
}

int BoardState::getNumWhiteIsolatedPawns() {
	int num = 0;
	for(int i=0; i<8; i++) {
		BoardMask_t pawnFile = Square::aFile << i;
		if (
			((pawnFile & whitePieceMasks[PAWN]) != NO_SQUARE)
			&& (((Square::w(pawnFile) | Square::e(pawnFile)) & whitePieceMasks[PAWN]) == NO_SQUARE)
		) {
		// If there is a pawn on the file and there are no pawns on adjacent files
			num++;
		}
	}
	return num;
}

int BoardState::getNumBlackIsolatedPawns() {
	int num = 0;
	for(int i=0; i<8; i++) {
		BoardMask_t pawnFile = Square::aFile << i;
		if (
			((pawnFile & blackPieceMasks[PAWN]) != NO_SQUARE)
			&& (((Square::w(pawnFile) | Square::e(pawnFile)) & blackPieceMasks[PAWN]) == NO_SQUARE)
		) {
		// If there is a pawn on the file and there are no pawns on adjacent files
			num++;
		}
	}
	return num;
}

int BoardState::getWhiteKingDistanceToEdge() {
	const Square_t whiteKingSquare = getWhiteKingSquare();
	int rank = Square::getRank(whiteKingSquare);
	int file = Square::getFile(whiteKingSquare);
	int distanceToEWEdge = file > 3 ? (7-file) : file;
	int distanceToNSEdge = rank > 3 ? (7-rank) : rank;
	return std::min(distanceToEWEdge,distanceToNSEdge);
}

int BoardState::getBlackKingDistanceToEdge() {
	const Square_t blackKingSquare = getBlackKingSquare();
	int rank = Square::getRank(blackKingSquare);
	int file = Square::getFile(blackKingSquare);
	int distanceToEWEdge = file > 3 ? (7-file) : file;
	int distanceToNSEdge = rank > 3 ? (7-rank) : rank;
	return std::min(distanceToEWEdge,distanceToNSEdge);
}

int BoardState::getTotalAttacksOnRegionByColor(const BoardMask_t& bm, const Color_t& c) {
	if (c) {
		return getTotalAttacksOnRegionByWhite(bm);
	} else {
		return getTotalAttacksOnRegionByBlack(bm);
	}
}

int BoardState::getTotalAttacksOnRegionByWhite(const BoardMask_t& bm) {
	int total = 0;
	for (int i=0; i<64; i++) {
		if (whitePieces[i] != NOPIECE) {
			total += Square::getNumSquares(visibility[i] & bm);
		}
	}
	return total;
}

int BoardState::getTotalAttacksOnRegionByBlack(const BoardMask_t& bm) {
	int total = 0;
	for (int i=0; i<64; i++) {
		if (blackPieces[i] != NOPIECE) {
			total += Square::getNumSquares(visibility[i] & bm);
		}
	}
	return total;
}

int BoardState::getTotalMobility(const Color_t& c) {
	if (c) {
		return getWhiteTotalMobility();
	} else {
		return getBlackTotalMobility();
	}
}

int BoardState::getWhiteTotalMobility() {
	int total = 0;
	for (int i=0; i<64; i++) {
		if (whitePieces[i] != NOPIECE && blackPieces[i] != KING) {
			total += Square::getNumSquares(visibility[i]);
		}
	}
	return total;
}

int BoardState::getBlackTotalMobility() {
	int total = 0;
	for (int i=0; i<64; i++) {
		if (blackPieces[i] != NOPIECE && blackPieces[i] != KING) {
			total += Square::getNumSquares(visibility[i]);
		}
	}
	return total;
}

void BoardState::clearHistory() {
	moveHistory.clear();
	boardStateHistory.clear();
}

BoardState::~BoardState() {
	
}
}
