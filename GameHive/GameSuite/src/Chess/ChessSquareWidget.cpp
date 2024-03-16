#include "ChessSquareWidget.h"

#include <QApplication>
#include <QIcon>
#include <QSize>
#include <QPainter>

ChessSquareWidget::ChessSquareWidget(int targetSize_, int rank_, int file_, QWidget *parent) :
    QLabel(parent),
	targetSize(targetSize_),
	rank(rank_),
	file(file_),
	sq(ChessCore::Square::getSquare(file_,rank_)),
	squarePix(rank % 2 == file % 2 ? QIcon(":/resources/squares/Wood/darksquare.svg").pixmap(targetSize_,targetSize_): QIcon(":/resources/squares/Wood/lightsquare.svg").pixmap(targetSize_,targetSize_)),
	nullPix(QPixmap())
{
	setAcceptDrops(true);
	clearPiece();
	setScaledContents(true);
}

Square_t ChessSquareWidget::getSquare() {
	return sq;
}

QPixmap* ChessSquareWidget::getPiecePix() {
	return piecePix;
}

void ChessSquareWidget::setPiece(QPixmap& pix) {
	hasPiece = !pix.isNull();
	if (hasPiece) {
		piecePix = &pix;
	}
	resetPixmap();
}

void ChessSquareWidget::clearPiece() {
	hasPiece = false;
	piecePix = nullptr;
	resetPixmap();
}

void ChessSquareWidget::resetPixmap() {
	QPixmap result(targetSize,targetSize);
	result.fill(Qt::transparent); 
	{
		QPainter painter(&result);
		painter.drawPixmap(0, 0, squarePix);
		if (checkmateHighlighted) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(192,0,0,127));
		} else if (stalemateHighlighted) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(255,255,0,127));
		}  else if (recentlyMovedFromOrTo && !checkHighlighted && !draggingTo && !isMarkedLegal) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(85,100,0,127));
		} else if (checkHighlighted && !draggingTo && !isMarkedLegal) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(140,0,140,127));
		}
		if (hasPiece) {
			if (draggingFrom) {
				painter.setOpacity(0.5);
			}
			painter.drawPixmap(0, 0, *piecePix);
		}
		if (draggingTo) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(0,100,0,127));
		} else if (isMarkedLegal) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(0,100,85,127));
		} 
		if (dimmed) {
			painter.setOpacity(1.0);
			painter.fillRect(0,0,targetSize,targetSize,QColor(0,0,0,64));
		}
	}
	setPixmap(result);
}

void ChessSquareWidget::dim() {
	dimmed = true;
	resetPixmap();
}

void ChessSquareWidget::undim() {
	dimmed = true;
	resetPixmap();
}

void ChessSquareWidget::suppress() {
	suppressed = true;
}

void ChessSquareWidget::unsuppress() {
	suppressed = false;
}

bool ChessSquareWidget::isSuppressed() {
	return suppressed;
}

void ChessSquareWidget::setRecentlyMovedFromOrTo(const bool& r) {
	recentlyMovedFromOrTo = r;
	resetPixmap();
}

void ChessSquareWidget::startDraggingFrom() {
	if (!suppressed) {
		if (hasPiece) {
			draggingFrom = true;
			resetPixmap();
		}
	}
}

void ChessSquareWidget::cancelDraggingFrom() {
	if (!suppressed) {
		if (hasPiece) {
			draggingFrom = false;
			resetPixmap();
		}
	}
}

void ChessSquareWidget::stopDraggingFrom() {
	if (!suppressed) {
		if (hasPiece) {
			draggingFrom = false;
			clearPiece();
		}
	}
}

void ChessSquareWidget::enterEvent(QEnterEvent* event) {
	if (!suppressed) {
		if (cursor() != Qt::ClosedHandCursor) {
			if (hasPiece && cursor() != Qt::ClosedHandCursor) {
				setCursor(Qt::OpenHandCursor);
			} else {
				setCursor(Qt::ArrowCursor);
			}
		}
	}
}

void ChessSquareWidget::leaveEvent(QEvent* event) {
	if (!suppressed) {
		if (cursor() != Qt::ClosedHandCursor) {
			setCursor(Qt::ArrowCursor);
		}
	}
}

void ChessSquareWidget::startDraggingTo() {
	if (!suppressed) {
		if (!draggingFrom) {
			draggingTo = true;
			resetPixmap();
		}
	}
}

void ChessSquareWidget::stopDraggingTo() {
	if (!suppressed) {
		if (!draggingFrom) {
			draggingTo = false;
			resetPixmap();
		}
	}
}

void ChessSquareWidget::markAsLegal() {
	if (!suppressed) {
		isMarkedLegal = true;
		resetPixmap();
	}
}

void ChessSquareWidget::unmarkAsLegal() {
	if (!suppressed) {
		isMarkedLegal = false;
		resetPixmap();
	}
}

void ChessSquareWidget::highlightCheck() {
	checkHighlighted = true;
	resetPixmap();
}

void ChessSquareWidget::unhighlightCheck() {
	checkHighlighted = false;
	resetPixmap();
}

void ChessSquareWidget::highlightCheckmate() {
	checkmateHighlighted = true;
	resetPixmap();
}

void ChessSquareWidget::unhighlightCheckmate() {
	checkmateHighlighted = false;
	resetPixmap();
}

void ChessSquareWidget::highlightStalemate() {
	stalemateHighlighted = true;
	resetPixmap();
}

void ChessSquareWidget::unhighlightStalemate() {
	stalemateHighlighted = false;
	resetPixmap();
}

void ChessSquareWidget::setChessStyles(const ChessStyleSettings& settings) {
	std::string basepath(":/resources/squares/");
	std::string lightFilepath("/lightsquare.svg");
	std::string darkFilepath("/darksquare.svg");
	std::string fullpath = (rank % 2 == file % 2) ? basepath + settings.boardTheme + darkFilepath : basepath + settings.boardTheme + lightFilepath;
	
	squarePix = QIcon(QString::fromStdString(fullpath)).pixmap(targetSize,targetSize);
	resetPixmap();
}

ChessSquareWidget::~ChessSquareWidget()
{
} 
