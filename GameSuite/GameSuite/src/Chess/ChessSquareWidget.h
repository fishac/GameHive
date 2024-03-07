#ifndef CHESSSQUAREWIDGET_H
#define CHESSSQUAREWIDGET_H

#include "ChessStyleDialog.h"
#include "ChessCore.h"

#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QEnterEvent>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QResizeEvent>

class ChessSquareWidget : public QLabel
{
    Q_OBJECT

public:
    explicit ChessSquareWidget(int targetSize_, int rank_, int file_, QWidget* parent = 0);
    Square_t getSquare();
	void setPiece(QPixmap& pix);
	void clearPiece();
	QPixmap* getPiecePix();
	void startDraggingFrom();
	void cancelDraggingFrom();
	void stopDraggingFrom();
	void startDraggingTo();
	void stopDraggingTo();
	void markAsLegal();
	void unmarkAsLegal();
	void suppress();
	void unsuppress();
	bool isSuppressed();
	void dim();
	void undim();
	void setRecentlyMovedFromOrTo(const bool& r);
	void highlightCheck();
	void highlightCheckmate();
	void highlightStalemate();
	void unhighlightCheck();
	void unhighlightCheckmate();
	void unhighlightStalemate();
	void setChessStyles(const ChessStyleSettings& settings);
    ~ChessSquareWidget();

private:
	int rank;
	int file;
	int targetSize;
	Square_t sq;
	bool suppressed = false;
	bool dimmed = false;
	bool recentlyMovedFromOrTo = false;
	bool hasPiece = false;
	bool isMarkedLegal = false;
	bool draggingFrom = false;
	bool draggingTo = false;
	bool checkHighlighted = false;
	bool checkmateHighlighted = false;
	bool stalemateHighlighted = false;
	QPixmap squarePix;
	QPixmap nullPix;
	QPixmap* piecePix;
	void resetPixmap();
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
};

#endif // CHESSSQUAREWIDGET_H 