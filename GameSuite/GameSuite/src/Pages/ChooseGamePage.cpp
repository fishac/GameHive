#include "ChooseGamePage.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QSizePolicy>
#include <QSize>
#include <QFont>

ChooseGamePage::ChooseGamePage(QWidget *parent) :
    QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	resize(530,530);
	QPushButton* chessGameButton = new QPushButton(this);
	chessGameButton->setIcon(QIcon(":/resources/knight.ico"));
	chessGameButton->setIconSize(QSize(256,256));
	chessGameButton->setToolTip("Chess");
	connect(chessGameButton, &QPushButton::clicked, this, &ChooseGamePage::chessGameButtonClicked);
	chessGameButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	
	QPushButton* hexagonChessGameButton = new QPushButton(this);
	hexagonChessGameButton->setIcon(QIcon(":/resources/hexagonknight.ico"));
	hexagonChessGameButton->setIconSize(QSize(256,256));
	hexagonChessGameButton->setToolTip("Hexagon Chess");
	connect(hexagonChessGameButton, &QPushButton::clicked, this, &ChooseGamePage::hexagonChessGameButtonClicked);
	hexagonChessGameButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	
	QGridLayout* layout = new QGridLayout();
	layout->setColumnStretch(0,1);
	layout->addWidget(chessGameButton,1,1);
	layout->addWidget(hexagonChessGameButton,1,2);
	layout->setColumnStretch(3,1);
	setLayout(layout);
	resize(550,550);
}

ChooseGamePage::~ChooseGamePage()
{
} 
