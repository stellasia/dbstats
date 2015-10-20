#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlError>

#include "querypanel.h"
#include "sqlsyntaxhighlighter.h"


QueryPanel::QueryPanel(QWidget *parent) {

    query_edit = new QPlainTextEdit;
    run_query_button = new QPushButton(tr("Run Query"));
    clear_query_button = new QPushButton(tr("Clear Query"));

    SqlSyntaxHighlighter *highlighter = new SqlSyntaxHighlighter(query_edit->document());

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
    query = query.trimmed(); // remove blanks at start and end

    if (! query.startsWith("select", Qt::CaseInsensitive))  {
	QMessageBox::critical(0, tr("Not a select!"),
			      "Can only perform a select query, please check yours starts with the 'SELECT' keyword", QMessageBox::Cancel);
	return;
    }

    model = new QSqlQueryModel;
    model->setQuery(query);

    if (model->lastError().isValid()) {
	QMessageBox::critical(0, tr("There might be a problem with your query"),
			      model->lastError().text(), QMessageBox::Cancel);
	return;
    }

    emit modelUpdated(model);
}

void QueryPanel::clearQuery() {
    query_edit->clear();
}
