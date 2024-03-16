#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include "ChessCore.h"
#include "ChessEngine.h"
#include "ChessStyleDialog.h"
#include "ChessSquareWidget.h"
#include "ChessPromotionSelectionWidget.h"

#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QPoint>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QThread>

class ChessBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoardWidget(QWidget* parent = 0);
	void initializeBoardState();
	void handleInvalidDrop();
	void setChessStyles(const ChessStyleSettings& settings);
	void setPlayer1IsEngine(bool player1IsEngine_);
	void setPlayer2IsEngine(bool player2IsEngine_);
	void beginPlayer1Move(int millisRemaining, int incrementMillis);
	void beginPlayer2Move(int millisRemaining, int incrementMillis);
    ~ChessBoardWidget();

private:
	QThread engineManagerThread;
	int targetSize = 800;
	int squareTargetSize = 100;
	bool draggingPiece = false;
	int dragStartRank;
	int dragStartFile;
	ChessCore::BoardState* bs;
	ChessEngine* eng;
	ChessPromotionSelectionWidget* promotionSelectionWidget = nullptr;
	ChessSquareWidget* draggingFromSquare = nullptr;
	ChessSquareWidget* draggingToSquare = nullptr;
	ChessSquareWidget* promotionSquare = nullptr;
	ChessSquareWidget* squares[8][8];
	QPixmap wRpix;
	QPixmap wNpix;
	QPixmap wBpix;
	QPixmap wKpix;
	QPixmap wQpix;
	QPixmap wPpix;
	QPixmap bRpix;
	QPixmap bNpix;
	QPixmap bBpix;
	QPixmap bKpix;
	QPixmap bQpix;
	QPixmap bPpix;
	QPoint dragStartPosition;
	QPixmap* dragPix;
	Square_t fromSquare_t = NO_SQUARE;
	bool player1IsEngine = false;
	bool player2IsEngine = false;
	QPixmap* getPromotionPix(const Piece_t& p);
	void markLegalSquares();
	void unmarkLegalSquares();
	void clearRecentlyMovedHighlighting();
	void dimBoardSquares();
	void undimBoardSquares();
	void suppressBoardSquares();
	void unsuppressBoardSquares();
	void scanPossibleCheckOrMate();
	void unhighlightCheckSquares();
	void unhighlightMateSquares();
	void mousePressEvent(QMouseEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void dragLeaveEvent(QDragLeaveEvent* event) override;
	
public slots:
	void endGame();
	
signals:
	void player1MadeMove();
	void player2MadeMove();
	void gameOver();
	void initializeEngine();
	void requestEngineMove(int millisRemaining, int incrementMillis);
	void provideMove(const ExtendedMove& m);
	
private slots:
	void dragDestroyed();
	void makePromotionSelection(QPixmap& pix, const Piece_t& p);
	void handleEngineMove(const ExtendedMove& m);
};

#endif // CHESSBOARDWIDGET_H 