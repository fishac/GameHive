#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include <string>
#include <vector>
#include <array>

#include "Types.h" 
#include "Square.h"
#include "Piece.h"
#include "Move.h"
#include "BoardStateRecord.h"

namespace ChessCore {
class BoardState {
public:
	~BoardState();
	BoardState();
	BoardState(const bool& setupDefaultStartingPosition);
	BoardState(const std::string& FEN);
	BoardState(const BoardState& bs);
	bool setFEN(const std::string& FEN);
	std::string toFEN();
	void setDefaultStartingState();
	void clearBoard();
	bool getTurnColor();
	bool makeMove(const Square_t& from, const Square_t& to);
	//bool makeMove(const Move& m);
	bool makeMoveAndPromote(const Square_t& from, const Square_t& to, const Piece_t& promotion_piece);
	//bool makeMoveAndPromote(const Move& m, const Piece_t& promotion_piece);
	bool makeMove(const ExtendedMove& m);
	void updateLegality();
	bool isMoveLegal(const Square_t& from, const Square_t& to);
	bool isMoveLegal(const Move& m);
	bool isMoveLegal(const ExtendedMove& m);
	bool getCheckStatus();
	bool getCheckmateStatus();
	bool getStalemateStatus();
	bool isDrawByRepitition();
	bool isDrawByInsufficientMaterial();
	std::vector<Move> getLegalMoves();
	std::vector<ExtendedMove> getLegalExtendedMoves();
	std::vector<Square_t> getWhitePawnSquares();
	std::vector<Square_t> getBlackPawnSquares();
	std::vector<Square_t> getWhiteKnightSquares();
	std::vector<Square_t> getBlackKnightSquares();
	std::vector<Square_t> getWhiteBishopSquares();
	std::vector<Square_t> getBlackBishopSquares();
	std::vector<Square_t> getWhiteRookSquares();
	std::vector<Square_t> getBlackRookSquares();
	std::vector<Square_t> getWhiteQueenSquares();
	std::vector<Square_t> getBlackQueenSquares();
	const std::array<Piece_t,64>& getWhitePieces();
	const std::array<Piece_t,64>& getBlackPieces();
	Square_t getWhiteKingSquare();
	Square_t getBlackKingSquare();
	const int& getNumWhitePawns();
	const int& getNumWhiteKnights();
	const int& getNumWhiteBishops();
	const int& getNumWhiteRooks();
	const int& getNumWhiteQueens();
	const int& getNumBlackPawns();
	const int& getNumBlackKnights();
	const int& getNumBlackBishops();
	const int& getNumBlackRooks();
	const int& getNumBlackQueens();
	const BoardMask_t& getWhitePawnMask();
	const BoardMask_t& getWhiteKnightMask();
	const BoardMask_t& getWhiteBishopMask();
	const BoardMask_t& getWhiteRookMask();
	const BoardMask_t& getWhiteQueenMask();
	const BoardMask_t& getBlackPawnMask();
	const BoardMask_t& getBlackKnightMask();
	const BoardMask_t& getBlackBishopMask();
	const BoardMask_t& getBlackRookMask();
	const BoardMask_t& getBlackQueenMask();
	void reportPieceSquares();
	void reportCastleRights();
	//void reportInternalState();
	int getHalfmoveClock();
	int getMoveNumber();
	int getActivePly();
	MoveRecord getLastMoveRecord();
	bool isLegalFromSquare(const Square_t& s);
	std::vector<Square_t> getLegalMovesFromSquare(const Square_t& s);
	bool moveRequiresPromotion(const Square_t& from, const Square_t& to);
	bool moveRequiresPromotion(const Move& m);
	bool moveRequiresPromotion(const ExtendedMove& m);
	bool moveIsEnPassant(const Square_t& from, const Square_t& to);
	bool moveIsEnPassant(const Move& m);
	bool moveIsEnPassant(const ExtendedMove& m);
	bool moveIsCapture(const Square_t& from, const Square_t& to);
	bool moveIsCapture(const Move& m);
	bool moveIsCapture(const ExtendedMove& m);
	bool moveIsCastle(const Square_t& from, const Square_t& to);
	bool moveIsCastle(const Move& m);
	bool moveIsCastle(const ExtendedMove& m);
	bool moveIsKSideCastle(const Square_t& from, const Square_t& to);
	bool moveIsKSideCastle(const Move& m);
	bool moveIsKSideCastle(const ExtendedMove& m);
	bool moveIsQSideCastle(const Square_t& from, const Square_t& to);
	bool moveIsQSideCastle(const Move& m);
	bool moveIsQSideCastle(const ExtendedMove& m);
	Square_t getEnPassantableSquare();
	Square_t getEnPassantCaptureSquare();
	bool undoMove();
	bool isRewound();
	void rewindToStart();
	void rewindOneMove();
	void fastForwardOneMove();
	void fastForwardToPresent();
	void setViewingPly(const int& plyNumber);
	MoveRecord getActivePreviousMoveRecord();
	//bool activeStateEquals(BoardState& bs);
	Piece_t getPieceOnSquare(const Square_t& s);
	Piece_t getPieceOnSquareIndex(const int& sq_idx);
	Color_t getColorOnSquare(const Square_t& s);
	bool getKingsideCastleRights(const Color_t& c);
	bool getQueensideCastleRights(const Color_t& c);
	uint64_t getZobristBoardHash();
	bool moveGivesCheck(const ExtendedMove& m);
	bool moveGivesCheck(const Square_t& from, const Square_t& to);
	bool moveCapturesPiece(const ExtendedMove& m, const Piece_t& p);
	bool moveIsNearPromotion(const Square_t& from, const Square_t& to);
	bool moveIsNearPromotion(const ExtendedMove& m);
	int getNumWhitePassedPawns();
	int getNumBlackPassedPawns();
	int getNumWhiteDoubledPawns();
	int getNumBlackDoubledPawns();
	int getNumWhiteIsolatedPawns();
	int getNumBlackIsolatedPawns();
	int getWhiteKingDistanceToEdge();
	int getBlackKingDistanceToEdge();
	int getTotalAttacksOnRegionByColor(const BoardMask_t& bm, const Color_t& c);
	int getTotalAttacksOnRegionByWhite(const BoardMask_t& bm);
	int getTotalAttacksOnRegionByBlack(const BoardMask_t& bm);
	int getTotalMobility(const Color_t& c);
	int getWhiteTotalMobility();
	int getBlackTotalMobility();
	void clearHistory();
protected: 
	void makeLegalMove(const Square_t& from, const Square_t& to);
	void makeLegalMoveAndPromote(const Square_t& from, const Square_t& to, const Piece_t& promotion_piece);
	void makeLegalExtendedMove(const ExtendedMove& m);
	void makeNullMove();
private:
	std::array<Piece_t,64>& getPieces(const Color_t& c);
	BoardMask_t& getPiecesMask(const Color_t& c);
	BoardMask_t& getPieceMask(const Color_t& c, const Piece_t& p);
	std::array<int,6>& getNumPieces(const Color_t& c);
	Square_t& getKingSquare(const Color_t&);
	BoardMask_t& getDefendedPiecesMask(const Color_t& c);
	BoardMask_t& getPossibleDefendedPiecesMask(const Color_t& c);
	void toggleTurnColor();
	void setEnPassantableSquare(const Square_t& sq);
	void setPawnVisibilities();
	void setNonPawnVisibilities();
	void setWhitePawnVisibility(const int& sq_idx);
	void setBlackPawnVisibility(const int& sq_idx);
	void setKnightVisibility(const Color_t& c, const int& sq_idx);
	void setBishopVisibility(const Color_t& c, const int& sq_idx);
	void setRookVisibility(const Color_t& c, const int& sq_idx);
	void setQueenVisibility(const Color_t& c, const int& sq_idx);
	void setKingVisibility(const Color_t& c, const int& sq_idx);
	void scanDirection(const Color_t& perspectiveColor, const Square_t& from, const bool& scanningEastWest, Square_t (*direction)(const Square_t&));
	void updateLegalMoves();
	Square_t getPinningPiece(const Square_t& sq);
	void reduceKingVisibilityAttackedSquares();
	void reduceVisibility(const Color_t& c);
	void reduceVisibilityFromSquare(const Color_t& c, const int& sq_idx);
	void reduceVisibilityStopCheck(const int& sq_idx, const Square_t& kingAttacker);
	void checkForKingAttackers();
	bool isPiecePinned(const Square_t& sq);
	void setLegalMoves();
	void initializeDefaultWhitePieces();
	void initializeDefaultBlackPieces();
	void initializeDerivativeData();
	void initializeMoveGenerationArrays();
	void initializeZobristBoardHash();
	void clearAllPieces();
	void clearVisibility();
	void clearXRayVisibility();
	void clearLegalMoves();
	void clearKingAttackers();
	void clearPinningPieces();
	void clearPossibleDefendedPieces();
	void clearDefendedPiecesMask();
	void clearKingPierceSquare();
	void removePiece(const Color_t& c, const Square_t& sq, MoveRecord* mr);
	void removePiece(const Color_t& c, const Square_t& sq);
	void addPiece(const Color_t& c, const Square_t& sq, const Piece_t& p);
	void updateCheckStatus();
	void updateCheckmateStatus();
	void updateStalemateStatus();
	void appendBoardStateHistory();
	void movePiece(const Square_t& from, const Square_t& to, const Piece_t& p, MoveRecord* mr);
	void movePieceForce(const Square_t& from, const Square_t& to, const Piece_t& p);
	void promotePawn(const Square_t& from, const Square_t& to, const Piece_t& promotionPiece, MoveRecord* mr);
	Piece_t getPiece(const Square_t& sq, const Color_t& c);
	BoardMask_t getVisibilityMask(const Color_t&);
	BoardMask_t getLegalMovesMask();
	void appendLegalMoves(const int& from_idx, std::vector<Move>& moves);
	void appendLegalExtendedMoves(const int& from_idx, std::vector<ExtendedMove>& moves);
	void revokeKSideCastleRights(const Color_t& c, MoveRecord* mr);
	void revokeQSideCastleRights(const Color_t& c, MoveRecord* mr);
	void restoreKSideCastleRights(const Color_t& c);
	void restoreQSideCastleRights(const Color_t& c);
	bool moveGivesCheck_(const Square_t& from, const Square_t& to);
	bool moveGivesCheck(const Square_t& to, const Piece_t& p, const Color_t& c);
	bool whitePawnGivesCheck(const Square_t& sq);
	bool blackPawnGivesCheck(const Square_t& sq);
	bool knightGivesCheck(const Square_t& sq, const Color_t& c);
	bool directionGivesCheck(const Square_t& to, const Color_t& c, Square_t (*direction)(const Square_t&));
	bool bishopGivesCheck(const Square_t& sq, const Color_t& c);
	bool rookGivesCheck(const Square_t& sq, const Color_t& c);
	bool queenGivesCheck(const Square_t& sq, const Color_t& c);
	std::array<Piece_t,64> whitePieces;
	std::array<Piece_t,64> blackPieces;
	std::array<int,6> numWhitePieces;
	std::array<int,6> numBlackPieces;
	std::array<BoardMask_t,6> whitePieceMasks;
	std::array<BoardMask_t,6> blackPieceMasks;
	Square_t whiteKingSquare;
	Square_t blackKingSquare;
	std::array<BoardMask_t,64> xRayVisibility;
	std::array<BoardMask_t,64> legalMoves;
	std::array<BoardMask_t,64> possibleDefendedPieces;
	std::array<BoardMask_t,64> pinningPieces;
	std::array<BoardMask_t,64> visibility;
	BoardMask_t whitePiecesMask;
	BoardMask_t blackPiecesMask;
	BoardMask_t whiteDefendedPiecesMask;
	BoardMask_t blackDefendedPiecesMask;
	std::vector<Square_t> kingAttackers;
	BoardMask_t whitePossibleDefendedPiecesMask;
	BoardMask_t blackPossibleDefendedPiecesMask;
	std::array<bool,2> kSideCastleRights;
	std::array<bool,2> qSideCastleRights;
	std::vector<MoveRecord> moveHistory;
	std::vector<BoardStateRecord> boardStateHistory;
	//BoardMask_t attackedPiecesMask;
	Square_t kingPierceSquare;
	Square_t enPassantableSquare;
	Color_t turnColor;
	bool checkStatus;
	bool checkmateStatus;
	bool stalemateStatus;
	int halfmoveClock;
	int moveNumber;
	int activePly;
	int totalPlies;
	uint64_t zobristBoardHash;
};
}

#endif // BOARDSTATE_H 