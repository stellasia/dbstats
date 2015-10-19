#ifndef DIALOGNEWCONNECTION_H
#define DIALOGNEWCONNECTION_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DialogNewConnection : public QDialog
{
    Q_OBJECT

 public:
    DialogNewConnection(QWidget *parent = 0);
    QString get_dbhost();
    QString get_dbport();
    QString get_dbname();
    QString get_dbuser();
    QString get_dbpasswd();
    
 public slots:
     bool openConnection();

 private:
    QPushButton *ok;
    QPushButton *cancel;
    QLineEdit *edit_dbhost;
    QLineEdit *edit_dbport;
    QLineEdit *edit_dbname;
    QLineEdit *edit_dbuser;
    QLineEdit *edit_dbpasswd;


};

#endif
