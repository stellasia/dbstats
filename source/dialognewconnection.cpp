#include <iostream>

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>

#include "dialognewconnection.h"


DialogNewConnection::DialogNewConnection(QWidget *parent) {

    QLabel *label_dbhost = new QLabel(tr("Host"));
    edit_dbhost = new QLineEdit;
    edit_dbhost->setText("localhost");
    QLabel *label_dbport = new QLabel(tr("Port"));
    edit_dbport = new QLineEdit;
    edit_dbport->setValidator( new QIntValidator(0, 100000, this) );
    edit_dbport->setText("5432");
    QLabel *label_dbname = new QLabel(tr("Database name"));
    edit_dbname = new QLineEdit;
    edit_dbname->setText("dbstats");
    QLabel *label_dbuser = new QLabel(tr("Username"));
    edit_dbuser = new QLineEdit;
    edit_dbuser->setText("postgres");
    QLabel *label_dbpasswd = new QLabel(tr("Password"));
    edit_dbpasswd = new QLineEdit;
    edit_dbpasswd->setEchoMode(QLineEdit::Password);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 250);
    layout->addWidget(label_dbhost, 0, 0);
    layout->addWidget(edit_dbhost, 0, 1);
    layout->addWidget(label_dbport, 1, 0);
    layout->addWidget(edit_dbport, 1, 1);
    layout->addWidget(label_dbname, 2, 0);
    layout->addWidget(edit_dbname, 2, 1);
    layout->addWidget(label_dbuser, 3, 0);
    layout->addWidget(edit_dbuser, 3, 1);
    layout->addWidget(label_dbpasswd, 4, 0);
    layout->addWidget(edit_dbpasswd, 4, 1);

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(ok);
    buttons->addWidget(cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttons);
    setLayout(mainLayout);

    setWindowTitle(tr("Database connection informations"));

}


QString DialogNewConnection::get_dbhost() {
    return edit_dbhost->text();
}
QString DialogNewConnection::get_dbport() {
    return edit_dbport->text();
}
QString DialogNewConnection::get_dbname() {
    return edit_dbname->text();
}
QString DialogNewConnection::get_dbuser() {
    return edit_dbuser->text();
}
QString DialogNewConnection::get_dbpasswd() {
    return edit_dbpasswd->text();
}
