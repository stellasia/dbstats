#include <iostream>

#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlRecord>
#include <QFormLayout>

#include "plotconfig.h"
#include "defs.h"


PlotConfig::PlotConfig(QWidget *parent) {
    QGroupBox *plot_type_config = new QGroupBox(tr("Plot type"));
    plot_type_combo = new QComboBox;
    plot_type_combo->insertItem(PLOT_TYPE_NONE, tr("Select a plot type"));
    plot_type_combo->insertItem(PLOT_TYPE_TH1, tr("1D histogram"));
    plot_type_combo->insertItem(PLOT_TYPE_TH2, tr("2D histogram"));
    connect(plot_type_combo, 
	    SIGNAL(currentIndexChanged(int)), 
	    this, SLOT(plotTypeChanged(int)));
    QVBoxLayout *plot_type_layout = new QVBoxLayout;
    plot_type_layout->addWidget(plot_type_combo);
    plot_type_config->setLayout(plot_type_layout);

    QGroupBox *variables_config = new QGroupBox(tr("Variables"));
    x_variable_combo = new QComboBox;
    x_variable_combo->setMaximumSize(x_variable_combo->sizeHint());
    y_variable_combo = new QComboBox;
    y_variable_combo->setMaximumSize(y_variable_combo->sizeHint());
    QFormLayout *variables_layout = new QFormLayout;
    variables_layout->addRow(tr("X:"), x_variable_combo);
    variables_layout->addRow(tr("Y:"), y_variable_combo);
    variables_config->setLayout(variables_layout);

    QGroupBox *axes_config = new QGroupBox(tr("Axes"));
    x_min_edit = new QLineEdit;
    x_max_edit = new QLineEdit;
    x_bins_edit = new QLineEdit;
    y_min_edit = new QLineEdit;
    y_max_edit = new QLineEdit;
    y_bins_edit = new QLineEdit;

    QFormLayout *form_layout = new QFormLayout;
    form_layout->addRow(tr("&Xmin:"), x_min_edit);
    form_layout->addRow(tr("&Xmax:"), x_max_edit);
    form_layout->addRow(tr("&Xbins:"), x_bins_edit);
    form_layout->addRow(tr("&Ymin:"), y_min_edit);
    form_layout->addRow(tr("&Ymax:"), y_max_edit);
    form_layout->addRow(tr("&Ybins:"), y_bins_edit);

    QVBoxLayout *axes_layout = new QVBoxLayout;
    axes_layout->addLayout(form_layout);
    axes_config->setLayout(axes_layout);

    QGroupBox *style_config = new QGroupBox(tr("Style"));
    QFormLayout *style_layout = new QFormLayout;
    // style_layout->addRow(tr("&Line color:"), line_color_combo);
    // style_layout->addRow(tr("&Line style:"), line_color_combo);
    // style_layout->addRow(tr("&Fill color:"), line_color_combo);
    // style_layout->addRow(tr("&Fill style:"), line_color_combo);
    // style_layout->addRow(tr("&Marker color:"), line_color_combo);
    // style_layout->addRow(tr("&Marker style:"), line_color_combo);
    style_config->setLayout(style_layout);

    QGroupBox *draw_option_config = new QGroupBox(tr("Draw option"));
    draw_option_edit = new QLineEdit;
    QFormLayout *draw_option_layout = new QFormLayout;
    draw_option_layout->addRow(tr("Draw option:"), draw_option_edit);
    draw_option_config->setLayout(draw_option_layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(plot_type_config);
    mainLayout->addWidget(variables_config);
    mainLayout->addWidget(axes_config);
    mainLayout->addWidget(style_config);
    mainLayout->addWidget(draw_option_config);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}


void PlotConfig::onModelUpdate(QSqlQueryModel *model) {
    QStringList list=QStringList();
    for (int k=0; k<model->columnCount(); k++) {
	QString columnName = model->record().fieldName( k );
	list << columnName;
    }
    x_variable_combo->addItems(list);
    y_variable_combo->addItems(list);
}

void PlotConfig::plotTypeChanged(int index) {
    if (plot_type_combo->currentIndex() == PLOT_TYPE_TH2) {
	// hide second axis specific informations
	y_variable_combo->show();
	y_bins_edit->show();
    }
    else {
	// show second axis specific informations
	y_variable_combo->hide();
	y_bins_edit->hide();
    }
}


void PlotConfig::getObjectOption(TObject *obj, Option_t *opt) {

}
