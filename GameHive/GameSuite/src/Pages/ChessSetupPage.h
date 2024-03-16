#ifndef CHESSSETUPPAGE_H
#define CHESSSETUPPAGE_H

#include <QWidget> 
#include <QComboBox>
#include <map>
#include <QString>
#include <vector>

struct ChessGameSettings {
	bool player1IsEngine;
	bool player2IsEngine;
	int baseTimeMillis;
	int incrementTimeMillis;
};

class ChessSetupPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChessSetupPage(QWidget* parent = 0);
	int getBaseMillis();
	int getIncrementMillis();
    ~ChessSetupPage();
	
private:
	QComboBox* player1Dropdown;
	QComboBox* player2Dropdown;
	QComboBox* baseTimeDropdown;
	QComboBox* incrementDropdown;
	int baseTimeMillis = 0;
	int incrementTimeMillis = 0;
	bool player1IsEngine = false;
	bool player2IsEngine = false;
	std::vector<QString> baseTimeLabels{"1 minute","3 minutes","10 minutes","30 minutes","Unlimited"};
	std::map<const QString,int> baseTimeMap{{"1 minute", 1*60*1000},{"3 minutes", 3*60*1000}, {"10 minutes", 10*60*1000},{"30 minutes", 30*60*1000},{"Unlimited", -1}};
	std::vector<QString> incrementLabels{"0 seconds","1 second","3 seconds","10 seconds","60 seconds"};
	std::map<const QString,int> incrementMap{{"0 seconds",0},{"1 second", 1*1000},{"3 seconds", 3*1000},{"10 seconds", 10*1000},{"60 seconds",60*1000}};

private slots:
	void player1Changed(int index);
	void player2Changed(int index);
	void baseTimeChanged(const QString& text);
	void incrementChanged(const QString& text);
	void startButtonClicked();
	
signals:
	void startGame(const ChessGameSettings& settings);
	
};

#endif // CHESSSETUPPAGE_H 