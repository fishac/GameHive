#include "ChessGamePage.h"
#include "ChessBoardWidget.h"
#include "ClockWidget.h"

#include <QGridLayout>
#include <iostream>

ChessGamePage::ChessGamePage(QWidget *parent) :
    QWidget(parent)
{
	
	board = new ChessBoardWidget(this);
	connect(board,&ChessBoardWidget::player1MadeMove,this,&ChessGamePage::handlePlayer1MadeMove);
	connect(board,&ChessBoardWidget::player2MadeMove,this,&ChessGamePage::handlePlayer2MadeMove);
	connect(board,&ChessBoardWidget::gameOver,this,&ChessGamePage::handleGameOver);
	board->initializeBoardState();
	
	clock1 = new ClockWidget();
	clock2 = new ClockWidget();
	connect(clock1,&ClockWidget::outOfTime,this,&ChessGamePage::handlePlayer1OutOfTime);
	connect(clock2,&ClockWidget::outOfTime,this,&ChessGamePage::handlePlayer2OutOfTime);
	
	QGridLayout* layout = new QGridLayout();
	layout->setColumnStretch(0,1);
	layout->setColumnStretch(5,1);
	layout->setRowStretch(0,1);
	layout->setRowStretch(4,1);
	layout->addWidget(board,1,1,3,3);
	layout->addWidget(clock1,3,4);
	layout->addWidget(clock2,1,4);
	layout->setAlignment(Qt::AlignCenter);
	layout->setSpacing(10);
	
	
	setLayout(layout);
}

void ChessGamePage::handleGameOver() {
	endGame();
}

void ChessGamePage::handlePlayer1MadeMove() {
	if (gameIsOngoing) {
		clock1->pauseClock();
		int player2time = clock2->getTotalMillisRemaining();
		clock2->startClock();
		board->beginPlayer2Move(
			player2time,
			incrementTimeMillis
		);
	}
}

void ChessGamePage::handlePlayer2MadeMove() {
	if (gameIsOngoing) {
		clock2->pauseClock();
		int player1time = clock1->getTotalMillisRemaining();
		clock1->startClock();
		board->beginPlayer1Move(
			player1time,
			incrementTimeMillis
		);
	}
}

void ChessGamePage::handlePlayer1OutOfTime() {
	board->endGame();
	endGame();
}

void ChessGamePage::handlePlayer2OutOfTime() {
	board->endGame();
	endGame();
}

void ChessGamePage::startGame(const ChessGameSettings& settings) {
	baseTimeMillis = settings.baseTimeMillis;
	incrementTimeMillis = settings.incrementTimeMillis;

	board->setPlayer1IsEngine(settings.player1IsEngine);
	board->setPlayer2IsEngine(settings.player2IsEngine);
	board->initializeBoardState(); 
	
	clock1->pauseClock();
	clock2->pauseClock();
	
	clock1->setIncrementMillis(settings.incrementTimeMillis);
	clock2->setIncrementMillis(settings.incrementTimeMillis);
	
	clock1->initializeClockValues(settings.baseTimeMillis);
	clock2->initializeClockValues(settings.baseTimeMillis);
	
	clock1->setInFirstMoveBuffer();
	clock2->setInFirstMoveBuffer();
	
	clock1->initializeDisplay();
	clock2->initializeDisplay();
	
	gameIsOngoing = true;
	clock1->startClock();
	board->beginPlayer1Move(
		settings.baseTimeMillis,
		settings.incrementTimeMillis
	);
}

void ChessGamePage::endGame() {
	gameIsOngoing = false;
	clock1->pauseClock();
	clock2->pauseClock();
}

void ChessGamePage::setChessStyles(const ChessStyleSettings& settings) {
	board->setChessStyles(settings);
}

ChessGamePage::~ChessGamePage()
{
} 
