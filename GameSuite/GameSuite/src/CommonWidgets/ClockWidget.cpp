#include "ClockWidget.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QSizePolicy>
#include <QSize>
#include <QFont>
#include <QDateTime>
#include <QSpacerItem>
#include <QSizePolicy>

ClockWidget::ClockWidget(QWidget *parent) :
    QWidget(parent)
{
	setMaximumSize(300,100);
	setMinimumSize(300,100);
	
	timer = new QTimer(this);
	elapsedTimer = new QElapsedTimer();
	timer->setInterval(100);
	timer->setTimerType(Qt::PreciseTimer);
	connect(timer,&QTimer::timeout,this,&ClockWidget::onTimerTick);
	
	
	minutesDisplay = new QLabel("00");
	minutesDisplay->setFont(QFont("Consolas",30,QFont::Black));
	secondsDisplay = new QLabel("00");
	secondsDisplay->setFont(QFont("Consolas",30,QFont::Black));
	millisDisplay = new QLabel("0");
	millisDisplay->setFont(QFont("Consolas",20));
	semicolonDisplay = new QLabel(":");
	semicolonDisplay->setFont(QFont("Consolas",30,QFont::Black));
	decimalDisplay = new QLabel(".");
	decimalDisplay->setFont(QFont("Consolas",20));
	
	
	QHBoxLayout* clockLayout = new QHBoxLayout();
	clockLayout->addWidget(minutesDisplay);
	clockLayout->addWidget(semicolonDisplay);
	clockLayout->addWidget(secondsDisplay);
	clockLayout->addWidget(decimalDisplay);
	clockLayout->addWidget(millisDisplay);
	clockLayout->setAlignment(Qt::AlignBottom);
	clockLayout->addStretch();
	QWidget* clockContainer = new QWidget();
	clockContainer->setLayout(clockLayout);
	
	firstMoveBufferInfoDisplay = new QLabel("Grace period: ");
	firstMoveBufferInfoDisplay->setFont(QFont("Consolas",20));
	firstMoveBufferSecondsDisplay = new QLabel("00");
	firstMoveBufferSecondsDisplay->setFont(QFont("Consolas",20,QFont::Black));
	
	QHBoxLayout* firstMoveBufferLayout = new QHBoxLayout();
	firstMoveBufferLayout->addWidget(firstMoveBufferInfoDisplay);
	firstMoveBufferLayout->addWidget(firstMoveBufferSecondsDisplay);
	firstMoveBufferLayout->setSpacing(0);
	firstMoveBufferLayout->addStretch();
	QWidget* firstMoveBufferContainer = new QWidget();
	firstMoveBufferContainer->setLayout(firstMoveBufferLayout);
	
	QLabel* unlimitedLabel = new QLabel("Unlimited time");
	unlimitedLabel->setFont(QFont("Consolas",20,QFont::Black));
	
	layout = new QStackedLayout();
	layout->addWidget(firstMoveBufferContainer);
	layout->addWidget(clockContainer);
	layout->addWidget(unlimitedLabel);
	setLayout(layout);
}

void ClockWidget::initializeClockValues(int startingMillis) {
	totalMillisRemaining = startingMillis;
	firstMoveBufferMillisRemaining = 5000;
}

void ClockWidget::initializeDisplay() {
	if (totalMillisRemaining == -1) {
		layout->setCurrentIndex(2);
	} else {
		setInFirstMoveBuffer();
		updateDisplay(firstMoveBufferMillisRemaining);
	}
}

void ClockWidget::incrementTime() {
	totalMillisRemaining += incrementMillis;
}

void ClockWidget::setIncrementMillis(int incrementMillis_) {
	incrementMillis = incrementMillis_;
}

int ClockWidget::getTotalMillisRemaining() {
	return totalMillisRemaining;
}

void ClockWidget::setInFirstMoveBuffer() {
	inFirstMoveBuffer = true;
	layout->setCurrentIndex(0);
}

void ClockWidget::unsetInFirstMoveBuffer() {
	inFirstMoveBuffer = false;
	layout->setCurrentIndex(1);
}

void ClockWidget::updateDisplay(int millisRemaining) {
	if (inFirstMoveBuffer) {
		secondsRemainingDisplay = millisRemaining / 1000;
		snprintf(firstMoveBufferSecondsDisplayArr,3,"%02d",secondsRemainingDisplay);
		firstMoveBufferSecondsDisplay->setText(firstMoveBufferSecondsDisplayArr);
	} else {
		minutesRemainingDisplay = millisRemaining / 1000 / 60;
		secondsRemainingDisplay = (millisRemaining - minutesRemainingDisplay*1000*60) / 1000;
		millisRemainingDisplay = (millisRemaining - minutesRemainingDisplay*1000*60 - secondsRemainingDisplay*1000);
		
		snprintf(minutesDisplayArr,3,"%02d",minutesRemainingDisplay);
		minutesDisplay->setText(minutesDisplayArr);
		
		snprintf(secondsDisplayArr,3,"%02d",secondsRemainingDisplay);
		secondsDisplay->setText(secondsDisplayArr);
		
		snprintf(millisDisplayArr,2,"%1d",millisRemainingDisplay);
		millisDisplay->setText(millisDisplayArr);
	}
	update();
}

void ClockWidget::startClock() {
	if (totalMillisRemaining != -1) {
		timer->start();
		elapsedTimer->start();
	}
}

void ClockWidget::pauseClock() {
	if (totalMillisRemaining != -1) {
		elapsedMillis = elapsedTimer->elapsed();
		timer->stop();
		if (inFirstMoveBuffer) {
			unsetInFirstMoveBuffer();
		} else {
			incrementTime();
			totalMillisRemaining -= elapsedMillis;
		}
		updateDisplay(totalMillisRemaining);
	}
}

void ClockWidget::onTimerTick() {
	if (totalMillisRemaining != -1) {
		elapsedMillis = timer->interval();
		timer->start();
		elapsedTimer->start();
		if (inFirstMoveBuffer) {
			firstMoveBufferMillisRemaining -= elapsedMillis;
			if (firstMoveBufferMillisRemaining <= 0) {
				unsetInFirstMoveBuffer();
				totalMillisRemaining -= firstMoveBufferMillisRemaining;
				updateDisplay(totalMillisRemaining);
			} else {
				updateDisplay(firstMoveBufferMillisRemaining);
			}
		} else {
			totalMillisRemaining -= elapsedMillis;
			updateDisplay(totalMillisRemaining);
		}
		if (totalMillisRemaining <= 0) {
			timer->stop();
			emit outOfTime();
		}
	}
}

ClockWidget::~ClockWidget()
{
} 
