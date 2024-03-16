#ifndef CHESSSTYLEDIALOG_H
#define CHESSSTYLEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QIcon>
#include <vector>
#include <string>

extern std::vector<std::string> ChessBoardThemes;

struct ChessStyleSettings {
	std::string boardTheme;
	bool partyMode;
};

class ChessStyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChessStyleDialog(QWidget* parent = 0);
    ~ChessStyleDialog();
	
private:
	int defaultBoardThemeIndex = 0;
	bool defaultPartyModeState = false;
	Qt::CheckState defaultPartyModeCheckState = Qt::Unchecked;
	std::string selectedBoardTheme;
	bool partyModeState;
	QComboBox* boardThemeDropdown;
	QCheckBox* partyModeCheckBox;
	const QIcon getDropdownIcon(std::string theme);
	
private slots:
	void boardThemeChanged(int index);
	void partyModeChanged(int state);
	void okButtonClicked();
	void resetDefaultsButtonClicked();
	
signals:
	void chessStylesChanged(const ChessStyleSettings& settings);
};

#endif // CHESSSTYLEDIALOG_H 