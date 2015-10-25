#include <QVBoxLayout>
//#include <QMessageBox>

#include "statspanel.h"


StatsPanel::StatsPanel(QWidget *parent) : QWidget(parent) {

    tabs = new QTabWidget;
    result_view = new QTableView;
    stat_view = new QWidget;
    tabs->addTab(result_view, tr("Overview"));
    tabs->addTab(stat_view, tr("Stats"));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tabs);

    setLayout(mainLayout);
}


void StatsPanel::onModelUpdate(QSqlQueryModel *pmodel) {
    model = pmodel;
    result_view->setModel(model);
}
