#include "ChessPromotionSelectionSquareWidget.h"

#include <QApplication>
#include <QIcon>
#include <QSize>
#include <QPainter>

ChessPromotionSelectionSquareWidget::ChessPromotionSelectionSquareWidget(int targetSize_, QWidget *parent) :
    QLabel(parent),
	targetSize(targetSize_),
	unhoveredPixmap(QIcon(":/resources/squares/PromotionSelection/unhovered.svg").pixmap(targetSize_,targetSize_)),
	hoveredPixmap(QIcon(":/resources/squares/PromotionSelection/hovered.svg").pixmap(targetSize_,targetSize_))
{
	setAcceptDrops(false);
	setScaledContents(true);
}

void ChessPromotionSelectionSquareWidget::setPieceData(QPixmap* pix, const Piece_t& p_) {
	piecePix = pix;
	p = p_;
	resetPixmap();
}

Piece_t ChessPromotionSelectionSquareWidget::getPiece_t() {
	return p;
}

QPixmap* ChessPromotionSelectionSquareWidget::getPiecePix() {
	return piecePix;
}

void ChessPromotionSelectionSquareWidget::resetPixmap() {
	QPixmap result(targetSize,targetSize);
	result.fill(Qt::transparent); 
	{
		QPainter painter(&result);
		if (hoveringSquare) {
			painter.drawPixmap(0, 0, hoveredPixmap);
		} else {
			painter.drawPixmap(0, 0, unhoveredPixmap);
		}
		painter.drawPixmap(0, 0, *piecePix);
	}
	setPixmap(result);
}

void ChessPromotionSelectionSquareWidget::enterEvent(QEnterEvent* event) {
	hoveringSquare = true;
	//setCursor(Qt::PointingHandCursor);
	resetPixmap();
}

void ChessPromotionSelectionSquareWidget::leaveEvent(QEvent* event) {
	hoveringSquare = false;
	//setCursor(Qt::ArrowCursor);
	resetPixmap();
}

ChessPromotionSelectionSquareWidget::~ChessPromotionSelectionSquareWidget()
{
} 
