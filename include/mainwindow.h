#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QSqlQueryModel>

#include "TQtWidget.h" 

#include "histlist.h"
#include "querypanel.h"
#include "statspanel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    bool createConnection();
    void initMenu();
    void create_new_histogram(QString x_variable);
    void create_new_scatter(QString x_variable, QString y_variable);

private slots:
    void connect2db();
    void showPlot();
    void saveProjectAs();
    void saveProject();
    void savePlotAs();
    void addPlot();
    void onModelUpdate(QSqlQueryModel *);

private:
    QSqlQueryModel *model;
    QueryPanel *query_panel;
    StatsPanel *stats_panel;

    HistList *plotConfig;
    TQtWidget *plotView;
    QPushButton *showPlotButton;
    QPushButton *addPlotButton;
    
    QString dbhost;
    int dbport;
    QString dbname;
    QString dbuser;
    QString dbpasswd;

    std::vector<TObject*> objectsToPlot;

};

#endif
