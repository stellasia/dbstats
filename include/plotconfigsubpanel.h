#ifndef PLOTCONFIGSUBPANEL_H
#define PLOTCONFIGSUBPANEL_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QPushButton>

#include <TObject.h>

#include "plotconfig.h"


class PlotConfigSubpanel : public QWidget
{
    Q_OBJECT

public:
    PlotConfigSubpanel(QWidget *parent = 0);

private slots:
    void drawPlot();
    void clearPlot();

public slots:
    void onModelUpdate(QSqlQueryModel *pmodel);

signals:
    void plotChanged(TObject *, QString);

private:
    QSqlQueryModel *model;
    PlotConfig *plot_config;
    QPushButton *draw_plot_button;
    QPushButton *clear_plot_button;
};

#endif
