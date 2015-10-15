#ifndef STATSPANEL_H
#define STATSPANEL_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QTabWidget>
#include <QTableView>


class StatsPanel : public QWidget
{
    Q_OBJECT

public:
    StatsPanel(QWidget *parent = 0);

public slots:
    void onModelUpdate(QSqlQueryModel *);

private:
    QSqlQueryModel *model;
    QTabWidget *tabs;
    QTableView *result_view ;
    QWidget *stat_view;

};

#endif
