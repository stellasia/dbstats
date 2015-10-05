#ifndef HISTITEM_H
#define HISTITEM_H

#include <QObject>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QPlainTextEdit>


class HistItem : public QWidget
{
    Q_OBJECT
    
public:
    HistItem(QWidget *parent, QString title, QString text, bool is_opened=false); 
    void addWidget(QWidget *widget);
 
public slots:
    void toggle();
    void open();
    void close();
 
private:
    QVBoxLayout* layout;
    bool is_opened;
    QPushButton *button;
    QPlainTextEdit *plaintext;

};
  
#endif
