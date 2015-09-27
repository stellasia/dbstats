#ifndef DIALOGNEWPLOT_H
#define DIALOGNEWPLOT_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQueryModel>

enum PLOTTYPE
{
	SCATTER,
	HIST2D,
	HIST
};
 

class DialogNewPlot : public QDialog
{
    Q_OBJECT
    
 public:
    DialogNewPlot(QSqlQueryModel *model, QWidget *parent = 0);
    QString get_plot_type();
    QString get_x_variable();
    QString get_y_variable();

 public slots:
     void changePlotType(int index);

 private:
    QPushButton *ok;
    QPushButton *cancel;
    QComboBox *combo_plot_type;
    QComboBox *combo_x_variable;
    QComboBox *combo_y_variable;
    QSqlQueryModel *model;

};

#endif
