#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTableView>
#include <QPushButton>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
  QPlainTextEdit *queryEdit;
  QTableView *resultView;
  QPushButton *runQueryButton;

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
