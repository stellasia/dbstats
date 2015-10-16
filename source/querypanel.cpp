#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QMessageBox>

#include "querypanel.h"


QueryPanel::QueryPanel(QWidget *parent) {

    query_edit = new QPlainTextEdit;
    run_query_button = new QPushButton(tr("Run Query"));
    clear_query_button = new QPushButton(tr("Clear Query"));

    connect(run_query_button, SIGNAL(clicked()), this,  SLOT(runQuery()));
    connect(clear_query_button, SIGNAL(clicked()), this,  SLOT(clearQuery()));

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(query_edit);
    QHBoxLayout *blayout = new QHBoxLayout;
    blayout->addWidget(clear_query_button);
    blayout->addWidget(run_query_button);
    vlayout->addLayout(blayout);

    setLayout(vlayout);

}


void QueryPanel::lock() {
    query_edit->setReadOnly(true); 
}

void QueryPanel::unlock() {
    query_edit->setReadOnly(false); 
}

void QueryPanel::runQuery() {
    QString query = query_edit->toPlainText();

    model = new QSqlQueryModel;
    model->setQuery(query);

    emit modelUpdated(model);
}

void QueryPanel::clearQuery() {
    query_edit->clear();
}
