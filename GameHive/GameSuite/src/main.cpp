#include "gamesuitewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameSuiteWindow gsw;
    gsw.show();

    return app.exec();
} 
