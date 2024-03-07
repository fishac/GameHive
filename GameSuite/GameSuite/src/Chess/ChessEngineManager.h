#ifndef CHESSENGINEMANAGER_H
#define CHESSENGINEMANAGER_H

#include "ChessCore.h"
#include "ChessEngine.h"

#include <QObject>

class ChessEngineManager : public QObject
{
    Q_OBJECT

public:
    ChessEngineManager();
	void initialize();
	void deinitialize();
    ~ChessEngineManager();

private:
	bool initialized = false;
	ChessEngine* eng;
	
public slots:
	void computeMove(int millisRemaining, int incrementMillis);
	void handleProvidedMove(const ExtendedMove& m);
	
signals:
	void engineComputedMove(ExtendedMove m);
};

#endif // CHESSENGINEMANAGER_H 