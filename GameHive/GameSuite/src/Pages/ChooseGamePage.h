#ifndef CHOOSEGAMEPAGE_H
#define CHOOSEGAMEPAGE_H

#include <QWidget> 

class ChooseGamePage : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseGamePage(QWidget* parent = 0);
    ~ChooseGamePage();

signals:
	void chessGameButtonClicked();
	void hexagonChessGameButtonClicked();
	
};

#endif // CHOOSEGAMEPAGE_H 