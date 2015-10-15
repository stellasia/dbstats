#include <QVBoxLayout>

#include <TObject.h>

#include "plotpanel.h"


PlotPanel::PlotPanel(QWidget *parent) {

    config_sub_panel = new PlotConfigSubpanel;
    drawing_sub_panel= new PlotDrawingSubpanel;

    connect(config_sub_panel,
	    SIGNAL(plotChanged(TObject *, Option_t *)),
	    this,
	    SLOT(onPlotChange(TObject *, Option_t *)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(config_sub_panel);
    mainLayout->addWidget(drawing_sub_panel);
    setLayout(mainLayout);

}


void PlotPanel::onModelUpdate(QSqlQueryModel *pmodel) {
    //model = pmodel;
    config_sub_panel->onModelUpdate(pmodel);
}


void PlotPanel::onPlotChange(TObject *obj, Option_t *opt) {
    drawing_sub_panel->draw(obj, "");
}
