#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlError>
#include <QGroupBox>
#include <QSqlQuery>
#include <QTextCursor>

#include "querypanel.h"


QueryPanel::QueryPanel(QWidget *parent) : QWidget(parent) {

    QGroupBox *gb = new QGroupBox(tr("SQL query"));
    query_edit = new QPlainTextEdit(this);
    query_edit->setPlainText(tr("-- You must connect to a database to start writing a query.\n --(File > Database connection) \n --Or see the help menu.\n\n"));
    query_edit->setObjectName("query_edit");

    highlighter = new SqlSyntaxHighlighter(query_edit->document());

    run_query_button = new QPushButton(tr("Run Query"), this);
    run_query_button->setObjectName("run_query_button");
    clear_query_button = new QPushButton(tr("Clear Query"), this);
    clear_query_button->setObjectName("clear_query_button");

    connect(run_query_button, SIGNAL(clicked()), this,  SLOT(runQuery()));
    connect(clear_query_button, SIGNAL(clicked()), this,  SLOT(clearQuery()));

    QVBoxLayout *vl = new QVBoxLayout;
    vl->addWidget(query_edit);
    gb->setLayout(vl);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(gb);
    QHBoxLayout *blayout = new QHBoxLayout;
    blayout->addWidget(clear_query_button);
    blayout->addWidget(run_query_button);
    vlayout->addLayout(blayout);

    setLayout(vlayout);

    // QObjectList pList = this->children();
    // for (int i =0; i<pList.size(); i++)
    // 	std::cout << pList.at(i)->objectName().toStdString() << std::endl;

    //this->lock();

}


void QueryPanel::runQuery() {
    QString q = query_edit->toPlainText();
    QSqlQuery query (q);
	
    if (! query.isSelect())  {
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


void QueryPanel::changeEvent(QEvent * e) {
    if (e->type() == QEvent::EnabledChange) {
	if (isEnabled()) {
	    query_edit->setFocus();
	    QTextCursor cursor(query_edit->textCursor());
	    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	    query_edit->setTextCursor(cursor);
	}
    }
    e->accept();
}
