#ifndef QUERYPANEL_H
#define QUERYPANEL_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QPlainTextEdit>
#include <QPushButton>


class QueryPanel : public QWidget
{
    Q_OBJECT

 public:
    QueryPanel(QWidget *parent = 0);
    void lock();
    void unlock();

 public slots:
     void runQuery();
     void clearQuery();

 signals:
     void modelUpdated(QSqlQueryModel *);

 private:
     QSqlQueryModel *model;
     QPlainTextEdit *query_edit;
     QPushButton *run_query_button;
     QPushButton *clear_query_button;

};

#endif
