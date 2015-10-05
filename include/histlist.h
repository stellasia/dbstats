#ifndef HISTLIST_H
#define HISTLIST_H

#include <QObject>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QPlainTextEdit>
#include <QScrollArea>

#include "histitem.h"


class HistList : public QScrollArea
{
    Q_OBJECT
    
public:
    HistList(QWidget *parent=0); 
    void addItem(HistItem *item);
    void closeAllButOne(HistItem *item);
  
private:
    QVBoxLayout* layout;
    std::vector<HistItem *> *list;

};
  
#endif
