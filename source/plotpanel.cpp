#include <QVBoxLayout>

#include <TObject.h>

#include "plotpanel.h"


PlotPanel::PlotPanel(QWidget *parent) : QWidget(parent) {

    config_sub_panel = new PlotConfigSubpanel(this);
    drawing_sub_panel= new PlotDrawingSubpanel(this);

    connect(config_sub_panel,
	    SIGNAL(plotChanged(TObject *, QString)),
	    this,
	    SLOT(onPlotChange(TObject *, QString)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(config_sub_panel);
    mainLayout->addWidget(drawing_sub_panel);
    setLayout(mainLayout);

}


void PlotPanel::onModelUpdate(QSqlQueryModel *pmodel) {
    //model = pmodel;
    config_sub_panel->onModelUpdate(pmodel);
}


void PlotPanel::onPlotChange(TObject *obj, QString opt) {
    drawing_sub_panel->draw(obj, opt);
}


void PlotPanel::lock() {
    config_sub_panel->setEnabled(false);
} 

void PlotPanel::unlock() {
    config_sub_panel->setEnabled(true);
} 
