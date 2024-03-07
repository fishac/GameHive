#include "ChessStyleDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <string>
#include <QSize>
#include <QSizePolicy>

std::vector<std::string> ChessBoardThemes = { "Wood", "Grayscale" };

ChessStyleDialog::ChessStyleDialog(QWidget* parent) :
    QDialog(parent)
{
	QFont labelFont("Arial",18);
	QFont dropdownFont("Arial",20);
	
	QLabel* boardThemeLabel = new QLabel("Board Theme", this);
	boardThemeLabel->setFont(labelFont);
	boardThemeDropdown = new QComboBox(this);
	boardThemeDropdown->setInsertPolicy(QComboBox::InsertAtBottom);
	boardThemeDropdown->setStyleSheet("combobox-popup: 0; padding-left: 10px; padding-top: 5px; padding-bottom: 5px; padding-right: 5px;");
	for (std::string themeName : ChessBoardThemes) {
		QIcon themeIcon = getDropdownIcon(themeName);	
		boardThemeDropdown->addItem(themeIcon,QString::fromStdString(themeName));
	}
	boardThemeDropdown->setFont(dropdownFont);
	boardThemeDropdown->setIconSize(QSize(40,40));
	connect(boardThemeDropdown,&QComboBox::currentIndexChanged,this,&ChessStyleDialog::boardThemeChanged);
	
	QLabel* partyModeLabel = new QLabel("Party Mode", this);
	partyModeLabel->setFont(labelFont);
	partyModeCheckBox = new QCheckBox(this);
	partyModeCheckBox->setFont(dropdownFont);
	//partyModeCheckBox->setStyleSheet("QCheckBox::indicator { width:25px; height: 25px;}");
	connect(partyModeCheckBox,&QCheckBox::stateChanged,this,&ChessStyleDialog::partyModeChanged);
	
	QPushButton* okButton = new QPushButton("OK",this);
	okButton->setIcon(QIcon());
	okButton->setFont(labelFont);
	okButton->setDefault(true);
	connect(okButton, &QPushButton::clicked, this, &ChessStyleDialog::okButtonClicked);
	
	QPushButton* resetDefaultsButton = new QPushButton("Reset Defaults",this);
	resetDefaultsButton->setIcon(QIcon());
	resetDefaultsButton->setFont(labelFont);
	connect(resetDefaultsButton, &QPushButton::clicked, this, &ChessStyleDialog::resetDefaultsButtonClicked);
	
	boardThemeDropdown->setCurrentIndex(defaultBoardThemeIndex);
	partyModeCheckBox->setCheckState(defaultPartyModeCheckState);
	
	QFormLayout* layout = new QFormLayout();
	layout->addRow(boardThemeLabel,boardThemeDropdown);
	layout->addRow(partyModeLabel,partyModeCheckBox);
	layout->addRow(resetDefaultsButton,okButton);

	setLayout(layout);
	setWindowTitle("Chess Style");
	setFixedSize(sizeHint());
}

const QIcon ChessStyleDialog::getDropdownIcon(std::string theme) {
	std::string basepath(":/resources/squares/");
	std::string filepath("/theme.svg");
	return QIcon(QString::fromStdString(basepath + theme + filepath));
}

void ChessStyleDialog::boardThemeChanged(int index) {
	selectedBoardTheme = ChessBoardThemes[index];
}

void ChessStyleDialog::partyModeChanged(int state) {
	partyModeState = (state == 0);
}

void ChessStyleDialog::okButtonClicked() {
	close();
	const ChessStyleSettings settings = { selectedBoardTheme, partyModeState };
	emit chessStylesChanged(settings);
}

void ChessStyleDialog::resetDefaultsButtonClicked() {
	close();
	boardThemeDropdown->setCurrentIndex(defaultBoardThemeIndex);
	partyModeCheckBox->setCheckState(defaultPartyModeCheckState);
	const ChessStyleSettings settings = { ChessBoardThemes[defaultBoardThemeIndex], defaultPartyModeState };
	emit chessStylesChanged(settings);
}

ChessStyleDialog::~ChessStyleDialog()
{
} 
