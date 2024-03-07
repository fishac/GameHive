#ifndef CHESSGAMEPAGE_H
#define CHESSGAMEPAGE_H

#include "ChessSetupPage.h"
#include "ClockWidget.h"
#include "ChessBoardWidget.h"
#include "ChessStyleDialog.h"

#include <QWidget> 

class ChessGamePage : public QWidget
{
    Q_OBJECT

public:
    explicit ChessGamePage(QWidget* parent = 0);
	void startGame(const ChessGameSettings& settings);
	void endGame();
	void setChessStyles(const ChessStyleSettings& settings);
    ~ChessGamePage();

private:
	ClockWidget* clock1;
	ClockWidget* clock2;
	int baseTimeMillis = 1;
	int incrementTimeMillis = 1;
	ChessBoardWidget* board;
	bool gameIsOngoing = false;
	
private slots:
	void handlePlayer1MadeMove();
	void handlePlayer2MadeMove();
	void handleGameOver();
	void handlePlayer1OutOfTime();
	void handlePlayer2OutOfTime();
};

#endif // CHESSGAMEPAGE_H