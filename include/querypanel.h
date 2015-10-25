#ifndef QUERYPANEL_H
#define QUERYPANEL_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QEvent>

#include "sqlsyntaxhighlighter.h"


class QueryPanel : public QWidget
{
    Q_OBJECT

 public:
    QueryPanel(QWidget *parent = 0);

 public slots:
     void runQuery();
     void clearQuery();
     void changeEvent(QEvent * );

 signals:
     void modelUpdated(QSqlQueryModel *);

 private:
     QSqlQueryModel *model;
     QPlainTextEdit *query_edit;
     QPushButton *run_query_button;
     QPushButton *clear_query_button;
     SqlSyntaxHighlighter *highlighter;
     
};

#endif
