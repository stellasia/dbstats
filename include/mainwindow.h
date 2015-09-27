#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTableView>
#include <QPushButton>
#include <QSqlQueryModel>

#include "TQtWidget.h" 

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    bool createConnection();
    void initMenu();

private slots:
    void connect2db();
    void runQuery();
    void showPlot();
    void saveProjectAs();
    void saveProject();
    void savePlotAs();

private:
    QSqlQueryModel *model;
    QPlainTextEdit *queryEdit;
    QTableView *resultView;
    QPushButton *runQueryButton;
    QLineEdit *queryLimit;
    
    QPlainTextEdit *plotConfig;
    TQtWidget *plotView;
    QPushButton *showPlotButton;
    
    QString dbhost;
    int dbport;
    QString dbname;
    QString dbuser;
    QString dbpasswd;

};

#endif
