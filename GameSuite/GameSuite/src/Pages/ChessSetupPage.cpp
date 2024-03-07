#include "ChessSetupPage.h"

#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <iostream>

ChessSetupPage::ChessSetupPage(QWidget *parent) :
    QWidget(parent)
{
	QFont dropdownFont("Arial",20);
	QFont labelFont("Arial", 18);
	
	QLabel* player1Label = new QLabel("Player 1",this); 
	player1Label->setFont(labelFont);
	player1Dropdown = new QComboBox(this);
	player1Dropdown->setInsertPolicy(QComboBox::InsertAtBottom);
	player1Dropdown->addItem("Human player");
	player1Dropdown->addItem("Engine");
	player1Dropdown->setFont(dropdownFont);
	player1Dropdown->setStyleSheet("combobox-popup: 0; padding-left: 10px; padding-top: 5px; padding-bottom: 5px; padding-right: 10px;");
	connect(player1Dropdown,&QComboBox::currentIndexChanged,this,&ChessSetupPage::player1Changed);
	
	QLabel* player2Label = new QLabel("Player 2",this); 
	player2Label->setFont(labelFont);
	player2Dropdown = new QComboBox(this);
	player2Dropdown->setInsertPolicy(QComboBox::InsertAtBottom);
	player2Dropdown->addItem("Human player");
	player2Dropdown->addItem("Engine");
	player2Dropdown->setFont(dropdownFont);
	player2Dropdown->setStyleSheet("combobox-popup: 0; padding-left: 10px; padding-top: 5px; padding-bottom: 5px; padding-right: 10px;");
	connect(player2Dropdown,&QComboBox::currentIndexChanged,this,&ChessSetupPage::player2Changed);
	
	QLabel* baseTimeLabel = new QLabel("Base Time",this); 
	baseTimeLabel->setFont(labelFont);
	baseTimeDropdown = new QComboBox(this);
	baseTimeDropdown->setInsertPolicy(QComboBox::InsertAtBottom);
	for(QString entry : baseTimeLabels) {
		baseTimeDropdown->addItem(entry);
	}
	baseTimeDropdown->setFont(dropdownFont);
	baseTimeDropdown->setStyleSheet("combobox-popup: 0; padding-left: 10px; padding-top: 5px; padding-bottom: 5px; padding-right: 10px;");
	connect(baseTimeDropdown,&QComboBox::currentTextChanged,this,&ChessSetupPage::baseTimeChanged);
	
	QLabel* incrementTimeLabel = new QLabel("Increment Time",this); 
	incrementTimeLabel->setFont(labelFont);
	incrementDropdown = new QComboBox(this);
	incrementDropdown->setInsertPolicy(QComboBox::InsertAtBottom);
	for(QString entry : incrementLabels) {
		incrementDropdown->addItem(entry);
	}
	incrementDropdown->setFont(dropdownFont);
	incrementDropdown->setStyleSheet("combobox-popup: 0; padding-left: 10px; padding-top: 5px; padding-bottom: 5px; padding-right: 10px;");
	connect(incrementDropdown,&QComboBox::currentTextChanged,this,&ChessSetupPage::incrementChanged);
	
	QPushButton* startGameButton = new QPushButton("Start Game");
	startGameButton->setStyleSheet("padding-left: 15px; padding-right: 15px;");
	startGameButton->setFont(QFont("Arial",20));
	connect(startGameButton,&QPushButton::clicked,this,&ChessSetupPage::startButtonClicked);
	
	player1Dropdown->setCurrentIndex(0);
	player2Dropdown->setCurrentIndex(0);
	baseTimeDropdown->setCurrentIndex(3);
	incrementDropdown->setCurrentIndex(4);
	
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow(player1Label,player1Dropdown);
	formLayout->addRow(player2Label,player2Dropdown);
	formLayout->addRow(baseTimeLabel,baseTimeDropdown);
	formLayout->addRow(incrementTimeLabel,incrementDropdown);
	
	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->addLayout(formLayout,1,1,1,3);
	gridLayout->addWidget(startGameButton,2,2);
	gridLayout->setColumnStretch(0,1);
	gridLayout->setColumnStretch(4,1);
	gridLayout->setRowStretch(0,1);
	gridLayout->setRowStretch(3,1);
	
	setLayout(gridLayout);
}

void ChessSetupPage::player1Changed(int index) {
	player1IsEngine = (index == 1); 
}

void ChessSetupPage::player2Changed(int index) {
	player2IsEngine = (index == 1);  
}

void ChessSetupPage::baseTimeChanged(const QString& text) {
	baseTimeMillis = baseTimeMap[text];
	if (baseTimeMillis == -1) {
		incrementDropdown->setEnabled(false);
	} else if (!incrementDropdown->isEditable()) {
		incrementDropdown->setEnabled(true);
	}
}

void ChessSetupPage::incrementChanged(const QString& text) {
	incrementTimeMillis = incrementMap[text];
}

void ChessSetupPage::startButtonClicked() {
	const ChessGameSettings settings = { player1IsEngine, player2IsEngine, baseTimeMillis, incrementTimeMillis };
	emit startGame(settings);
}

ChessSetupPage::~ChessSetupPage()
{
} 
