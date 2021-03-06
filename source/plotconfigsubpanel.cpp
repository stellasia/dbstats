#include <QVBoxLayout>

#include "plotconfigsubpanel.h"


PlotConfigSubpanel::PlotConfigSubpanel (QWidget* parent) : QWidget(parent) {

    plot_config = new PlotConfig(this);
    clear_plot_button = new QPushButton(tr("Clear"), this);
    draw_plot_button = new QPushButton(tr("Draw"), this);

    connect(clear_plot_button, SIGNAL(clicked()),
	    this, SLOT(clearPlot()));
    connect(draw_plot_button, SIGNAL(clicked()),
	    this, SLOT(drawPlot()));

    QHBoxLayout *blayout = new QHBoxLayout;
    blayout->addWidget(clear_plot_button);
    blayout->addWidget(draw_plot_button);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(plot_config);
    vlayout->addLayout(blayout);

    setLayout(vlayout);
}


void PlotConfigSubpanel::onModelUpdate(QSqlQueryModel *pmodel) {
    //model = pmodel;
    plot_config->onModelUpdate(pmodel);
}


void PlotConfigSubpanel::drawPlot() {
    TObject *obj = NULL;
    QString opt = "";

    plot_config->getObjectOption(&obj, &opt);
    
    emit plotChanged(obj, opt);

}

void PlotConfigSubpanel::clearPlot() {

}
