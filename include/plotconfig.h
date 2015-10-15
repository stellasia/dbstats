#ifndef PLOTCONFIG_H
#define PLOTCONFIG_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>

#include <TObject.h>


class PlotConfig : public QWidget
{
    Q_OBJECT

public:
    PlotConfig(QWidget *parent = 0);
    void getObjectOption(TObject *, Option_t *);
    
private slots:
    void plotTypeChanged(int);
    
public slots:
    void onModelUpdate(QSqlQueryModel *);

private:
    QSqlQueryModel *model;
    QComboBox *plot_type_combo;
    QLineEdit *x_min_edit;
    QLineEdit *x_max_edit;
    QLineEdit *y_min_edit;
    QLineEdit *y_max_edit;
    QLineEdit *x_bins_edit;
    QLineEdit *y_bins_edit;
    QComboBox *x_variable_combo;
    QComboBox *y_variable_combo;

    QLineEdit *draw_option_edit;

    /* QHBoxLayout *x_axis_layout; */
    /* QHBoxLayout *y_axis_layout; */

};

#endif
