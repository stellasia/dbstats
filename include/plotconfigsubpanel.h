#ifndef PLOTCONFIGSUBPANEL_H
#define PLOTCONFIGSUBPANEL_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QPushButton>


class PlotConfigSubpanel : public QWidget
{
    Q_OBJECT

public:
    PlotConfigSubpanel(QWidget *parent = 0);

private slots:
    void onModelUpdate(QSqlQueryModel *pmodel);
    void drawPlot();
    void clearPlot();

private:
    QSqlQueryModel *model;
    QWidget *w;
    QPushButton *draw_plot_button;
    QPushButton *clear_plot_button;
};

#endif
