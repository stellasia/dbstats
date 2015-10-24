/**
 */

#include <QApplication>
#include <QPlastiqueStyle>

#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    app.setStyle(new QPlastiqueStyle);

    // QFont font;
    // font.setFamily("Sans Serif");
    // font.setPointSize(12);
    // app.setFont(font);
    MainWindow mainWin;
    mainWin.showMaximized();
    return app.exec();
}

