#ifndef CHESSPROMOTIONSELECTIONSQUAREWIDGET_H
#define CHESSPROMOTIONSELECTIONSQUAREWIDGET_H

#include "ChessCore.h"

#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QEnterEvent>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QResizeEvent>

class ChessPromotionSelectionSquareWidget : public QLabel
{
    Q_OBJECT

public:
    explicit ChessPromotionSelectionSquareWidget(int targetSize_, QWidget* parent = 0);
    Square_t getSquare();
	QPixmap* getPiecePix();
	Piece_t getPiece_t();
	void setPieceData(QPixmap* pix, const Piece_t& p_);
    ~ChessPromotionSelectionSquareWidget();
	
private:
	int targetSize;
	bool hoveringSquare = false;
	QPixmap unhoveredPixmap;
	QPixmap hoveredPixmap;
	QPixmap* piecePix;
	Piece_t p;
	void resetPixmap();
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
};

#endif // CHESSSQUAREWIDGET_H 