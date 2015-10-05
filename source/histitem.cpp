#include <QString>
#include <QObject>

#include "histitem.h"


HistItem::HistItem(QWidget *parent, 
		       QString title, QString text, bool opened) {

    button = new QPushButton;
    button->setText(title);

    plaintext = new QPlainTextEdit;
    plaintext->setPlainText(text);

    layout = new QVBoxLayout;
    layout->addWidget(button);
    layout->addWidget(plaintext);

    setLayout(layout);

    is_opened = opened;

    if (!is_opened)
	close();

    connect(button, SIGNAL(clicked()), this, SLOT(toggle()));
}


void HistItem::toggle() {

    if (is_opened) {
	close();
    }
    else {
	open();
    }
}


void HistItem::close() {
    plaintext->hide();	
    is_opened = false;
}


void HistItem::open() {
    plaintext->show();
    is_opened = true;
}
