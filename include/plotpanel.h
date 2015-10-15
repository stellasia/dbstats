#ifndef PLOTPANEL_H
#define PLOTPANEL_H

#include <QWidget>
#include <QSqlQueryModel>

#include "plotconfigsubpanel.h"
#include "plotdrawingsubpanel.h"


class PlotPanel : public QWidget
{
    Q_OBJECT

public:
    PlotPanel(QWidget *parent = 0);

public slots:
    void onModelUpdate(QSqlQueryModel *);

private:
    QSqlQueryModel *model;
    PlotConfigSubpanel *config_sub_panel;
    PlotDrawingSubpanel *drawing_sub_panel;

};

#endif
