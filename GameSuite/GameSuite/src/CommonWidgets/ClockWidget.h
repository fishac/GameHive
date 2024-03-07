#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget> 
#include <QLabel>
#include <QStackedLayout>
#include <QTimer>
#include <QElapsedTimer>
#include <QTimerEvent>

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(QWidget* parent = 0);
    ~ClockWidget();
	void initializeClockValues(int startingMillis);
	void setIncrementMillis(int incrementMillis_);
	int getTotalMillisRemaining();
	void initializeDisplay();
	void updateDisplay(int millisRemaining);
	void setInFirstMoveBuffer();
	void unsetInFirstMoveBuffer();
	void startClock();
	void pauseClock();
	
private:
	QTimer* timer;
	QElapsedTimer* elapsedTimer;
	QLabel* minutesDisplay;
	QLabel* secondsDisplay;
	QLabel* millisDisplay;
	QLabel* semicolonDisplay;
	QLabel* decimalDisplay;
	QLabel* clockDisplay;
	QLabel* firstMoveBufferInfoDisplay;
	QLabel* firstMoveBufferSecondsDisplay;
	QStackedLayout* layout;
	char minutesDisplayArr[3];
	char secondsDisplayArr[3];
	char millisDisplayArr[2];
	char clockDisplayArr[8];
	char firstMoveBufferSecondsDisplayArr[2];
	int minutesRemainingDisplay;
	int secondsRemainingDisplay;
	int millisRemainingDisplay;
	int totalMillisRemaining;
	int firstMoveBufferMillisRemaining;
	int incrementMillis;
	bool active = false;
	bool inFirstMoveBuffer = true;
	long long int elapsedMillis;
	void onTimerTick();
	void incrementTime();
	
signals:
	void outOfTime();
};

#endif // CLOCKWIDGET_H