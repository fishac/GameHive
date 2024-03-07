#include "ChessBoardWidget.h"
#include "ChessSquareWidget.h"
#include "ChessCore.h"
#include "ChessEngineManager.h"

#include <QGridLayout>
#include <QDrag>
#include <QApplication>
#include <QMimeData>
#include <QCursor>
#include <iostream>

ChessBoardWidget::ChessBoardWidget(QWidget *parent) :
    QWidget(parent),
	wRpix(QIcon(":/resources/pieces/wR.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	wNpix(QIcon(":/resources/pieces/wN.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	wBpix(QIcon(":/resources/pieces/wB.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	wKpix(QIcon(":/resources/pieces/wK.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	wQpix(QIcon(":/resources/pieces/wQ.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	wPpix(QIcon(":/resources/pieces/wP.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	bRpix(QIcon(":/resources/pieces/bR.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	bNpix(QIcon(":/resources/pieces/bN.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	bBpix(QIcon(":/resources/pieces/bB.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	bKpix(QIcon(":/resources/pieces/bK.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	bQpix(QIcon(":/resources/pieces/bQ.svg").pixmap(QSize(squareTargetSize,squareTargetSize))),
	bPpix(QIcon(":/resources/pieces/bP.svg").pixmap(QSize(squareTargetSize,squareTargetSize)))
{
	setAcceptDrops(true);
	targetSize = 800;
	squareTargetSize = targetSize/8;
	setMaximumSize(targetSize,targetSize);
	setMinimumSize(targetSize,targetSize);
	QGridLayout* layout = new QGridLayout();
	
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j] = new ChessSquareWidget(squareTargetSize,i,j,this);
		}
	}
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			layout->addWidget(squares[i][j],7-i,j);
		}
	}

	bs = new ChessCore::BoardState();
	
	ChessEngineManager* engineManager = new ChessEngineManager;
	engineManager->moveToThread(&engineManagerThread);
	connect(&engineManagerThread, &QThread::finished, engineManager, &QObject::deleteLater);
	connect(this, &ChessBoardWidget::initializeEngine, engineManager, &ChessEngineManager::initialize);
	connect(this, &ChessBoardWidget::requestEngineMove, engineManager, &ChessEngineManager::computeMove);
	connect(this, &ChessBoardWidget::provideMove, engineManager, &ChessEngineManager::handleProvidedMove);
	connect(engineManager, &ChessEngineManager::engineComputedMove, this, &ChessBoardWidget::handleEngineMove);
	engineManagerThread.start();
	
	layout->setSpacing(0);
	setLayout(layout);

	promotionSelectionWidget = new ChessPromotionSelectionWidget(
 		wRpix,
		wNpix,
		wBpix,
		wQpix,
		bRpix,
		bNpix,
		bBpix,
		bQpix,
		(squares[0][0]->geometry()).width(),
		this
	);
	connect(
		promotionSelectionWidget,
		&ChessPromotionSelectionWidget::makePromotionSelection,
		this,
		&ChessBoardWidget::makePromotionSelection
	);
}

void ChessBoardWidget::setPlayer1IsEngine(bool player1IsEngine_) {
	player1IsEngine = player1IsEngine_;
}

void ChessBoardWidget::setPlayer2IsEngine(bool player2IsEngine_) {
	player2IsEngine = player2IsEngine_;
}

void ChessBoardWidget::beginPlayer1Move(int millisRemaining, int incrementMillis) {
	if (player1IsEngine) {
		suppressBoardSquares();
		requestEngineMove(millisRemaining,incrementMillis);
	}
}

void ChessBoardWidget::beginPlayer2Move(int millisRemaining, int incrementMillis) {
	if (player2IsEngine) {
		suppressBoardSquares();
		requestEngineMove(millisRemaining,incrementMillis);
	}
}

void ChessBoardWidget::handleEngineMove(const ExtendedMove& m) {
	clearRecentlyMovedHighlighting();
	unhighlightCheckSquares();
	squares[ChessCore::Square::getRank(m.to)][ChessCore::Square::getFile(m.to)]->setRecentlyMovedFromOrTo(true);
	squares[ChessCore::Square::getRank(m.from)][ChessCore::Square::getFile(m.from)]->setRecentlyMovedFromOrTo(true);
	if (m.promotionPiece == ChessCore::Piece::NOPIECE) {
		QPixmap* fromPix = squares[ChessCore::Square::getRank(m.from)][ChessCore::Square::getFile(m.from)]->getPiecePix();
		squares[ChessCore::Square::getRank(m.to)][ChessCore::Square::getFile(m.to)]->setPiece(*fromPix);
		squares[ChessCore::Square::getRank(m.from)][ChessCore::Square::getFile(m.from)]->clearPiece();
	} else {
		squares[ChessCore::Square::getRank(m.from)][ChessCore::Square::getFile(m.from)]->clearPiece();
		QPixmap* promotionPix = getPromotionPix(m.promotionPiece);
		squares[ChessCore::Square::getRank(m.to)][ChessCore::Square::getFile(m.to)]->setPiece(*promotionPix);		
	}
	Color_t turnColor = bs->getTurnColor();
	bool madeMove = bs->makeMove(m);
	scanPossibleCheckOrMate();
	unsuppressBoardSquares();
	if (turnColor) {
		player1MadeMove();
	} else {
		player2MadeMove();
	}
}

QPixmap* ChessBoardWidget::getPromotionPix(const Piece_t& p) {
	if (bs->getTurnColor()) {
		switch(p) {
			case ChessCore::Piece::KNIGHT:
				return &wNpix;
			case ChessCore::Piece::BISHOP:
				return &wBpix;
			case ChessCore::Piece::ROOK:
				return &wRpix;
			case ChessCore::Piece::QUEEN:
				return &wQpix;
			default:
				return nullptr;
		}
	} else {
		switch(p) {
			case ChessCore::Piece::KNIGHT:
				return &bNpix;
			case ChessCore::Piece::BISHOP:
				return &bBpix;
			case ChessCore::Piece::ROOK:
				return &bRpix;
			case ChessCore::Piece::QUEEN:
				return &bQpix;
			default:
				return nullptr;
		}
	}
}

void ChessBoardWidget::initializeBoardState() {
	squares[0][0]->setPiece(wRpix);
	squares[0][1]->setPiece(wNpix);
	squares[0][2]->setPiece(wBpix);
	squares[0][3]->setPiece(wQpix);
	squares[0][4]->setPiece(wKpix);
	squares[0][5]->setPiece(wBpix);
	squares[0][6]->setPiece(wNpix);
	squares[0][7]->setPiece(wRpix);	
	squares[1][0]->setPiece(wPpix);
	squares[1][1]->setPiece(wPpix);
	squares[1][2]->setPiece(wPpix);
	squares[1][3]->setPiece(wPpix);
	squares[1][4]->setPiece(wPpix);
	squares[1][5]->setPiece(wPpix);
	squares[1][6]->setPiece(wPpix);
	squares[1][7]->setPiece(wPpix);
	
	squares[7][0]->setPiece(bRpix);
	squares[7][1]->setPiece(bNpix);
	squares[7][2]->setPiece(bBpix);
	squares[7][3]->setPiece(bQpix);
	squares[7][4]->setPiece(bKpix);
	squares[7][5]->setPiece(bBpix);
	squares[7][6]->setPiece(bNpix);
	squares[7][7]->setPiece(bRpix);	
	squares[6][0]->setPiece(bPpix);
	squares[6][1]->setPiece(bPpix);
	squares[6][2]->setPiece(bPpix);
	squares[6][3]->setPiece(bPpix);
	squares[6][4]->setPiece(bPpix);
	squares[6][5]->setPiece(bPpix);
	squares[6][6]->setPiece(bPpix);
	squares[6][7]->setPiece(bPpix);
	
	for(int i=2; i<=5; i++) {
		for (int j=0; j<8; j++) {
			squares[i][j]->clearPiece();
		}
	}

	clearRecentlyMovedHighlighting();
	unhighlightMateSquares();
	unhighlightCheckSquares();
	unsuppressBoardSquares();
	undimBoardSquares();

	delete bs;
	bs = new ChessCore::BoardState();
	
	if (player1IsEngine || player2IsEngine) {
		emit initializeEngine();
	}
}

void ChessBoardWidget::mousePressEvent(QMouseEvent* event) {
	if (promotionSquare == nullptr && !bs->getCheckmateStatus() && !bs->getStalemateStatus()) {
		ChessSquareWidget* child = static_cast<ChessSquareWidget*>(childAt(event->position().toPoint()));
		if (!child) {
			return;
		}
		if (child->isSuppressed()) {
			return;
		}
		if (!bs->isLegalFromSquare(child->getSquare())) {
			return;
		}
		setCursor(Qt::ClosedHandCursor);
		
		draggingPiece = true;
		draggingFromSquare = child;
		dragPix = draggingFromSquare->getPiecePix();
		fromSquare_t = draggingFromSquare->getSquare();
		draggingFromSquare->startDraggingFrom();
		markLegalSquares();

		QDrag *drag = new QDrag(this);
		drag->setPixmap(*dragPix);
		QMimeData* mimeData = new QMimeData;
		drag->setMimeData(mimeData);
		drag->setHotSpot(dragPix->rect().center());
		drag->setDragCursor(QCursor(Qt::ClosedHandCursor).pixmap(),Qt::MoveAction);
		Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
		connect(drag, SIGNAL(destroyed()), this, SLOT(dragDestroyed()) );
	}
}

void ChessBoardWidget::markLegalSquares() {
	std::vector<Square_t> legalToSquares = bs->getLegalMovesFromSquare(fromSquare_t);
	for(auto iter = legalToSquares.begin(); iter != legalToSquares.end(); iter++) {
		squares[ChessCore::Square::getRank(*iter)][ChessCore::Square::getFile(*iter)]->markAsLegal();
	}
}

void ChessBoardWidget::unmarkLegalSquares() {
	std::vector<Square_t> legalToSquares = bs->getLegalMovesFromSquare(fromSquare_t);
	for(auto iter = legalToSquares.begin(); iter != legalToSquares.end(); iter++) {
		squares[ChessCore::Square::getRank(*iter)][ChessCore::Square::getFile(*iter)]->unmarkAsLegal();
	}
}

void ChessBoardWidget::dragMoveEvent(QDragMoveEvent* event)
{
	event->acceptProposedAction();
	ChessSquareWidget* child = static_cast<ChessSquareWidget*>(childAt(event->position().toPoint()));
	if (!child) {
		return;
	} else if (child != draggingToSquare) {
		if (draggingToSquare != nullptr) {
			draggingToSquare->stopDraggingTo();
		}
		if (child != draggingFromSquare && bs->isMoveLegal(fromSquare_t,child->getSquare())) {
			child->startDraggingTo();
			draggingToSquare = child;
		}
	}
}

void ChessBoardWidget::dragEnterEvent(QDragEnterEvent* event) {
	event->acceptProposedAction();
}

void ChessBoardWidget::dropEvent(QDropEvent* event) {
	ChessSquareWidget* child = static_cast<ChessSquareWidget*>(childAt(event->position().toPoint()));
	setCursor(Qt::ArrowCursor);
	draggingPiece = false;
	unmarkLegalSquares();
	if (draggingToSquare != nullptr) {
		draggingToSquare->stopDraggingTo();
		draggingToSquare = nullptr;
	}
	if (!child) {
		return;
	}
	if (bs->isMoveLegal(fromSquare_t,child->getSquare())) {
		clearRecentlyMovedHighlighting();
		unhighlightCheckSquares();
		Color_t currentTurnColor = bs->getTurnColor();
		Square_t toSquare_t = child->getSquare();
		if (bs->moveIsEnPassant(fromSquare_t, child->getSquare())) {
			Square_t enPassantableSquare = bs->getEnPassantCaptureSquare();
			squares[ChessCore::Square::getRank(enPassantableSquare)][ChessCore::Square::getFile(enPassantableSquare)]->clearPiece();
		}
		if (bs->moveIsKSideCastle(fromSquare_t,toSquare_t)) {
			if (currentTurnColor) {
				QPixmap* rookPix = squares[0][7]->getPiecePix();
				squares[0][5]->setPiece(*rookPix);
				squares[0][7]->clearPiece();
			} else {
				QPixmap* rookPix = squares[7][7]->getPiecePix();
				squares[7][5]->setPiece(*rookPix);
				squares[7][7]->clearPiece();
			}
		} else if (bs->moveIsQSideCastle(fromSquare_t,toSquare_t)) {
			if (currentTurnColor) {
				QPixmap* rookPix = squares[0][0]->getPiecePix();
				squares[0][3]->setPiece(*rookPix);
				squares[0][0]->clearPiece();
			} else {
				QPixmap* rookPix = squares[7][0]->getPiecePix();
				squares[7][3]->setPiece(*rookPix);
				squares[7][0]->clearPiece();
			}
		}
		draggingFromSquare->setRecentlyMovedFromOrTo(true);
		draggingFromSquare->stopDraggingFrom();
		child->setRecentlyMovedFromOrTo(true);
		if (!bs->moveRequiresPromotion(fromSquare_t,child->getSquare())) {
			child->setPiece(*dragPix);
			if (player1IsEngine || player2IsEngine) {
				/*
				std::cout << 
					"Providing the engine the player's move from: " 
					<< ChessCore::Square::getString(fromSquare_t) 
					<< ", to: " 
					<< ChessCore::Square::getString(child->getSquare())  
					<< ", turnColor: " 
					<< bs->getTurnColor()
					<< std::endl;
				*/
				emit provideMove({fromSquare_t,child->getSquare(),ChessCore::Piece::NOPIECE});
			}
			bs->makeMove(fromSquare_t,child->getSquare());
			scanPossibleCheckOrMate();
			draggingFromSquare = nullptr;
			dragPix = nullptr;
			fromSquare_t = NO_SQUARE;
			if (currentTurnColor) {
				player1MadeMove();
			} else {
				player2MadeMove();
			}
		} else {
			child->setPiece(*dragPix);
			promotionSelectionWidget->openPromotionSelection(child->geometry(),bs->getTurnColor());
			promotionSquare = child;
			suppressBoardSquares();
			dimBoardSquares();
		}
	} else  {
		draggingFromSquare->cancelDraggingFrom();
		draggingFromSquare = nullptr;
		dragPix = nullptr;
		fromSquare_t = NO_SQUARE;
	}
}

void ChessBoardWidget::clearRecentlyMovedHighlighting() {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->setRecentlyMovedFromOrTo(false);
		}
	}
}

void ChessBoardWidget::dimBoardSquares() {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->dim();
		}
	}
}

void ChessBoardWidget::undimBoardSquares() {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->undim();
		}
	}
}

void ChessBoardWidget::suppressBoardSquares() {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->suppress();
		}
	}
}

void ChessBoardWidget::unsuppressBoardSquares() {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->unsuppress();
		}
	}
}

void ChessBoardWidget::unhighlightCheckSquares() {	
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->unhighlightCheck();
		}
	}
}

void ChessBoardWidget::unhighlightMateSquares() {	
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->unhighlightCheckmate();
			squares[i][j]->unhighlightStalemate();
		}
	}
}

void ChessBoardWidget::dragLeaveEvent(QDragLeaveEvent* event)  {
	if (draggingToSquare != nullptr) {
		draggingToSquare->stopDraggingTo();
		draggingToSquare = nullptr;
	}
}

void ChessBoardWidget::handleInvalidDrop() {
	setCursor(Qt::ArrowCursor);
	draggingPiece = false;
	if (draggingToSquare != nullptr) {
		draggingToSquare->stopDraggingTo();
		draggingToSquare = nullptr;
	}
	draggingFromSquare->cancelDraggingFrom();
	draggingFromSquare = nullptr;
}

void ChessBoardWidget::dragDestroyed() {
	setCursor(Qt::ArrowCursor);
	draggingPiece = false;
	if (draggingFromSquare != nullptr) {
		draggingFromSquare->cancelDraggingFrom();
		draggingFromSquare = nullptr;
	}
}

void ChessBoardWidget::makePromotionSelection(QPixmap& pix, const Piece_t& p) {
	promotionSquare->setPiece(pix);
	Color_t currentTurnColor = bs->getTurnColor();
	bs->makeMoveAndPromote(fromSquare_t,promotionSquare->getSquare(),p);
	if (player1IsEngine || player2IsEngine) {
		emit provideMove({fromSquare_t,promotionSquare->getSquare(),p});
	}
	unsuppressBoardSquares();
	undimBoardSquares();
	promotionSquare->setRecentlyMovedFromOrTo(true);
	promotionSquare = nullptr;
	draggingFromSquare = nullptr;
	dragPix = nullptr;
	fromSquare_t = NO_SQUARE;
	scanPossibleCheckOrMate();
	if (currentTurnColor) {
		player1MadeMove();
	} else {
		player2MadeMove();
	}
}

void ChessBoardWidget::scanPossibleCheckOrMate() {
	if (bs->getCheckmateStatus()) {
		Square_t kingSquare;
		if (bs->getTurnColor()) {
			kingSquare = bs->getWhiteKingSquare();
		} else {
			kingSquare = bs->getBlackKingSquare();
		} 
		squares[ChessCore::Square::getRank(kingSquare)][ChessCore::Square::getFile(kingSquare)]->highlightCheckmate();
		suppressBoardSquares();
		gameOver();
	} else if (bs->getCheckStatus()) {
		Square_t kingSquare;
		if (bs->getTurnColor()) {
			kingSquare = bs->getWhiteKingSquare();
		} else {
			kingSquare = bs->getBlackKingSquare();
		} 
		squares[ChessCore::Square::getRank(kingSquare)][ChessCore::Square::getFile(kingSquare)]->highlightCheck();
	} else if (bs->getStalemateStatus()) {
		Square_t wkingSquare = bs->getWhiteKingSquare();
		Square_t bkingSquare = bs->getBlackKingSquare();
		squares[ChessCore::Square::getRank(wkingSquare)][ChessCore::Square::getFile(wkingSquare)]->highlightStalemate();
		squares[ChessCore::Square::getRank(bkingSquare)][ChessCore::Square::getFile(bkingSquare)]->highlightStalemate();
		suppressBoardSquares();
		gameOver();
	} 
}

void ChessBoardWidget::endGame() {
	undimBoardSquares();
	suppressBoardSquares();
}

void ChessBoardWidget::setChessStyles(const ChessStyleSettings& settings) {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			squares[i][j]->setChessStyles(settings);
		}
	}
}

ChessBoardWidget::~ChessBoardWidget() {
	engineManagerThread.quit();
	engineManagerThread.wait();
} 
