/**
 */

#include <QApplication>
#include <QPlastiqueStyle>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    app.setStyle(new QPlastiqueStyle);

    // Open application with the local language
    // (if not found, uses the application language
    // ie English)
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load("languages/" + locale);
    app.installTranslator(&translator);

    // QFont font;
    // font.setFamily("Sans Serif");
    // font.setPointSize(12);
    // app.setFont(font);
    MainWindow mainWin;
    mainWin.showMaximized();
    return app.exec();
}

