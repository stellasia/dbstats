#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSqlQueryModel>

#include "querypanel.h"
#include "statspanel.h"
#include "plotpanel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void initMenu();

private slots:
    void connect2db();
    void saveProjectAs();
    void saveProject();
    void savePlotAs();
    void onModelUpdate(QSqlQueryModel *);

private:
    QSqlQueryModel *model;
    QueryPanel *query_panel;
    StatsPanel *stats_panel;
    PlotPanel *plot_panel;
    
};

#endif
