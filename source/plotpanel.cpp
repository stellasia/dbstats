#include <QVBoxLayout>
//#include <QMessageBox>
#include "plotpanel.h"


PlotPanel::PlotPanel(QWidget *parent) {

    config_sub_panel = new PlotConfigSubpanel;
    drawing_sub_panel= new PlotDrawingSubpanel;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(config_sub_panel);
    mainLayout->addWidget(drawing_sub_panel);
    setLayout(mainLayout);

}


void PlotPanel::onModelUpdate(QSqlQueryModel *pmodel) {
    model = pmodel;
}
