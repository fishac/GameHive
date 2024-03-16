#include "GameSuiteWindow.h"
#include "ChooseGamePage.h"
#include "ChessGamePage.h"

#include <QStackedLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>

GameSuiteWindow::GameSuiteWindow(QWidget *parent) :
    QMainWindow(parent)
{
	setAcceptDrops(true);
    initializeWindow();
	initializeMenuBar();
	initializeWindowContent();
}

void GameSuiteWindow::initializeWindow() {
	resize(800,800);
	setWindowTitle("Game Suite");
	setWindowIcon(QIcon(":/resources/icon.ico"));
}

void GameSuiteWindow::initializeMenuBar() {
	initializeMenuActions();
	initializeMenuItems();
}
	
void GameSuiteWindow::initializeMenuActions() {
	newGameAct = new QAction("New Game", this);
	newGameAct->setStatusTip("Start a new game");
	connect(newGameAct, &QAction::triggered, this, &GameSuiteWindow::createNewGame);
	
	chessStyleAct = new QAction("Chess Style", this);
	chessStyleAct->setStatusTip("Choose a chess style");
	connect(chessStyleAct, &QAction::triggered, this, &GameSuiteWindow::changeChessStyles);
	
	aboutAct = new QAction("About", this);
	aboutAct->setStatusTip("About Game Suite");
	connect(aboutAct, &QAction::triggered, this, &GameSuiteWindow::openAbout);
}

void GameSuiteWindow::initializeMenuItems() {
	gameMenu = menuBar()->addMenu("Game");
    gameMenu->addAction(newGameAct);
	
	preferencesMenu = menuBar()->addMenu("Preferences");
    preferencesMenu->addAction(chessStyleAct);
	
	helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAct);
}

void GameSuiteWindow::createNewGame() {
	mainLayout->setCurrentIndex(0);
}

void GameSuiteWindow::changeChessStyles() {
	chessStyleDialog->exec();
}

void GameSuiteWindow::handleChessStylesChanged(const ChessStyleSettings& settings) {
	chessGamePage->setChessStyles(settings);
}

void GameSuiteWindow::openAbout() {
	aboutDialog->exec();
}

void GameSuiteWindow::initializeWindowContent() {
	chessStyleDialog = new ChessStyleDialog(this);
	connect(chessStyleDialog,&ChessStyleDialog::chessStylesChanged,this,&GameSuiteWindow::handleChessStylesChanged);
	
	aboutDialog = new AboutDialog(this);
	
	chooseGamePage = new ChooseGamePage(this);
	connect(chooseGamePage,&ChooseGamePage::chessGameButtonClicked,this,&GameSuiteWindow::openChessGameSettings);
	connect(chooseGamePage,&ChooseGamePage::hexagonChessGameButtonClicked,this,&GameSuiteWindow::openHexagonChessGameSettings);
	
	chessSetupPage = new ChessSetupPage(this);
	connect(chessSetupPage,&ChessSetupPage::startGame,this,&GameSuiteWindow::startChessGame);
	chessGamePage = new ChessGamePage(this);
	
	QStackedLayout* layout = new QStackedLayout();
	mainLayout = layout;
	mainLayout->addWidget(chooseGamePage);
	mainLayout->addWidget(chessSetupPage);
	mainLayout->addWidget(chessGamePage);
	
	centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
	centralWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	setCentralWidget(centralWidget);
}

void GameSuiteWindow::openChessGameSettings() {
	mainLayout->setCurrentIndex(1);
}

void GameSuiteWindow::startChessGame(const ChessGameSettings& settings) {
	mainLayout->setCurrentIndex(2);
	chessGamePage->startGame(settings);
}

void GameSuiteWindow::openHexagonChessGameSettings() {
}

GameSuiteWindow::~GameSuiteWindow()
{
} 
