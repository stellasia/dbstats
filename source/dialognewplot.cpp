#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlRecord>

#include "dialognewplot.h"


DialogNewPlot::DialogNewPlot(QSqlQueryModel *model, QWidget *parent) {

    this->model = model;

    QLabel *label_plot_type = new QLabel(tr("Plot type"));
    combo_plot_type = new QComboBox;
    combo_plot_type->insertItem(combo_plot_type->count(), "Histogram", HIST);
    combo_plot_type->insertItem(combo_plot_type->count(), "Scatter", SCATTER);

    connect(combo_plot_type, SIGNAL(currentIndexChanged(int)), 
	    this, SLOT(changePlotType(int)));

    QStringList list=QStringList();
    for (int k=0; k<model->columnCount(); k++) {
	QString columnName = model->record().fieldName( k );
	list << columnName;
    }

    QLabel *label_x_variable = new QLabel(tr("X"));
    combo_x_variable = new QComboBox;
    combo_x_variable->addItems(list);
    QLabel *label_y_variable = new QLabel(tr("Y"));
    combo_y_variable = new QComboBox;
    combo_y_variable->addItems(list);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 250);
    layout->addWidget(label_plot_type, 0, 0);
    layout->addWidget(combo_plot_type, 0, 1);
    layout->addWidget(label_x_variable, 1, 0);
    layout->addWidget(combo_x_variable, 1, 1);
    layout->addWidget(label_y_variable, 2, 0);
    layout->addWidget(combo_y_variable, 2, 1);

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(ok);
    buttons->addWidget(cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttons);
    setLayout(mainLayout);

    setWindowTitle(tr("New plot"));

}


void DialogNewPlot::changePlotType(int index) {
    /*
      if (index == HIST) {
      combo_y_variable->hide();
      //label_y_variable->hide();
      }
      else {
      combo_y_variable->show();
      //label_y_variable->show();
      }
    */
}


QString DialogNewPlot::get_plot_type() {
    return combo_plot_type->currentText();
}


QString DialogNewPlot::get_x_variable() {
    return combo_x_variable->currentText();
}

QString DialogNewPlot::get_y_variable() {
    return combo_y_variable->currentText();
}
