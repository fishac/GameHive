#ifndef CHESSPROMOTIONSELECTIONWIDGET_H
#define CHESSPROMOTIONSELECTIONWIDGET_H

#include <QRect>
#include <QPixmap>

#include "ChessCore.h"
#include "ChessPromotionSelectionSquareWidget.h"

class ChessPromotionSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessPromotionSelectionWidget(
	    QPixmap& wRpix_,
	    QPixmap& wNpix_,
	    QPixmap& wBpix_,
	    QPixmap& wQpix_,
	    QPixmap& bRpix_,
	    QPixmap& bNpix_,
	    QPixmap& bBpix_,
	    QPixmap& bQpix_,
	    int targetSize_,
	    QWidget* parent = 0
	);
    void openPromotionSelection(const QRect& promotionSquareGeom, const Color_t& promotingColor);
    ~ChessPromotionSelectionWidget();
	
private:
	QPixmap wRpix;
	QPixmap wNpix;
	QPixmap wBpix;
	QPixmap wQpix;
	QPixmap bRpix;
	QPixmap bNpix;
	QPixmap bBpix;
	QPixmap bQpix;
	int targetSize;
	ChessPromotionSelectionSquareWidget* topSquare;
	ChessPromotionSelectionSquareWidget* secondSquare;
	ChessPromotionSelectionSquareWidget* thirdSquare;
	ChessPromotionSelectionSquareWidget* bottomSquare;
	void closePromotionSelection();
	void mousePressEvent(QMouseEvent* event) override;
	QPixmap* getTopSquarePixmap(const Color_t& promotingColor);
	QPixmap* getSecondSquarePixmap(const Color_t& promotingColor);
	QPixmap* getThirdSquarePixmap(const Color_t& promotingColor);
	QPixmap* getBottomSquarePixmap(const Color_t& promotingColor);
	Piece_t getTopSquarePiece(const Color_t& promotingColor);
	Piece_t getSecondSquarePiece(const Color_t& promotingColor);
	Piece_t getThirdSquarePiece(const Color_t& promotingColor);
	Piece_t getBottomSquarePiece(const Color_t& promotingColor);

signals:
	void makePromotionSelection(QPixmap& pix, const Piece_t& p);
};

#endif // CHESSPROMOTIONSELECTIONWIDGET_H 