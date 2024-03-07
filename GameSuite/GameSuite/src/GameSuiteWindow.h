#ifndef GAMESUITEWINDOW_H
#define GAMESUITEWINDOW_H

#include "AboutDialog.h"
#include "ChooseGamePage.h"
#include "ChessSetupPage.h"
#include "ChessGamePage.h"
#include "ChessStyleDialog.h"

#include <QMainWindow>
#include <QStackedLayout>
#include <QMenuBar>
#include <QAction>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

class GameSuiteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameSuiteWindow(QWidget* parent = 0);
    ~GameSuiteWindow();

private:
	QStackedLayout* mainLayout = nullptr;
    QWidget* centralWidget;
	QMenu* gameMenu;
    QMenu* preferencesMenu;
	QMenu* helpMenu;
    QAction* newGameAct;
    QAction* chessStyleAct;
    QAction* aboutAct;
	AboutDialog* aboutDialog;
	ChessStyleDialog* chessStyleDialog;
	ChooseGamePage* chooseGamePage;
	ChessSetupPage* chessSetupPage;
	ChessGamePage* chessGamePage;
	void initializeWindow();
    void initializeWindowContent();
	void initializeMenuBar();
	void initializeMenuActions();
	void initializeMenuItems();
	
private slots:
	void createNewGame();
	void changeChessStyles();
	void handleChessStylesChanged(const ChessStyleSettings& settings);
	void openAbout();
	void openChessGameSettings();
	void startChessGame(const ChessGameSettings& settings);
	void openHexagonChessGameSettings();
};

#endif // GAMESUITEWINDOW_H 
