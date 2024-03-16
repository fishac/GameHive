#include <QVBoxLayout>

#include "ChessPromotionSelectionWidget.h"
#include "ChessCore.h"

ChessPromotionSelectionWidget::ChessPromotionSelectionWidget(
    QPixmap& wRpix_,
    QPixmap& wNpix_,
    QPixmap& wBpix_,
    QPixmap& wQpix_,
    QPixmap& bRpix_,
    QPixmap& bNpix_,
    QPixmap& bBpix_,
    QPixmap& bQpix_,
    int targetSize_,
    QWidget* parent
) :
    QWidget(parent),
    wRpix(wRpix_),
    wNpix(wNpix_),
    wBpix(wBpix_),
    wQpix(wQpix_),
    bRpix(bRpix_),
    bNpix(bNpix_),
    bBpix(bBpix_),
    bQpix(bQpix_),
    targetSize(targetSize_-2)
{
    setVisible(true);
    setMaximumSize(targetSize,targetSize*4);
    setMinimumSize(targetSize,targetSize*4);
    topSquare = new ChessPromotionSelectionSquareWidget(targetSize, this);
    secondSquare = new ChessPromotionSelectionSquareWidget(targetSize, this);
    thirdSquare = new ChessPromotionSelectionSquareWidget(targetSize, this);
    bottomSquare = new ChessPromotionSelectionSquareWidget(targetSize, this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(topSquare);
    layout->addWidget(secondSquare);
    layout->addWidget(thirdSquare);
    layout->addWidget(bottomSquare);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void ChessPromotionSelectionWidget::openPromotionSelection(
    const QRect& promotionSquareGeom,
    const Color_t& promotingColor
) {
    int yOffset = promotingColor ? 0 : -3*promotionSquareGeom.height();
    move(
        promotionSquareGeom.x(),
        promotionSquareGeom.y() + yOffset
    );

    topSquare->setPieceData(getTopSquarePixmap(promotingColor),getTopSquarePiece(promotingColor));
    secondSquare->setPieceData(getSecondSquarePixmap(promotingColor),getSecondSquarePiece(promotingColor));
    thirdSquare->setPieceData(getThirdSquarePixmap(promotingColor),getThirdSquarePiece(promotingColor));
    bottomSquare->setPieceData(getBottomSquarePixmap(promotingColor),getBottomSquarePiece(promotingColor));
    setVisible(true);
}

void ChessPromotionSelectionWidget::closePromotionSelection() {
    setVisible(false);
}

QPixmap* ChessPromotionSelectionWidget::getTopSquarePixmap(const Color_t& promotingColor) {
    return promotingColor ? &wQpix : &bBpix;
}

QPixmap* ChessPromotionSelectionWidget::getSecondSquarePixmap(const Color_t& promotingColor) {
    return promotingColor ? &wNpix : &bRpix;
}

QPixmap* ChessPromotionSelectionWidget::getThirdSquarePixmap(const Color_t& promotingColor) {
    return promotingColor ? &wRpix : &bNpix;
}

QPixmap* ChessPromotionSelectionWidget::getBottomSquarePixmap(const Color_t& promotingColor) {
    return promotingColor ? &wBpix : &bQpix;
}

Piece_t ChessPromotionSelectionWidget::getTopSquarePiece(const Color_t& promotingColor) {
    return promotingColor ? ChessCore::Piece::QUEEN : ChessCore::Piece::BISHOP;
}

Piece_t ChessPromotionSelectionWidget::getSecondSquarePiece(const Color_t& promotingColor) {
    return promotingColor ? ChessCore::Piece::KNIGHT : ChessCore::Piece::ROOK;
}

Piece_t ChessPromotionSelectionWidget::getThirdSquarePiece(const Color_t& promotingColor) {
    return promotingColor ? ChessCore::Piece::ROOK : ChessCore::Piece::KNIGHT;
}

Piece_t ChessPromotionSelectionWidget::getBottomSquarePiece(const Color_t& promotingColor) {
    return promotingColor ? ChessCore::Piece::BISHOP : ChessCore::Piece::QUEEN;
}

void ChessPromotionSelectionWidget::mousePressEvent(QMouseEvent* event) {
    ChessPromotionSelectionSquareWidget* child = static_cast<ChessPromotionSelectionSquareWidget*>(childAt(event->position().toPoint()));
    if (!child) {
        return;
    }
    makePromotionSelection(*(child->getPiecePix()),child->getPiece_t());
    closePromotionSelection();
}

ChessPromotionSelectionWidget::~ChessPromotionSelectionWidget() {
}