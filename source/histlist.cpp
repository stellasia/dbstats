#include <QString>
#include <QObject>

#include "histlist.h"


HistList::HistList(QWidget *parent) {
    this->setWidgetResizable(true);
    QWidget *w = new QWidget(this);

    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);

    w->setLayout(layout);
    this->setWidget(w);

    list = new std::vector<HistItem*>();
}


void HistList::addItem(HistItem *item) {
    list->push_back(item);
    layout->addWidget(item);
    closeAllButOne(item);
}


void HistList::closeAllButOne(HistItem *item) {
    for (unsigned int k = 0; k<list->size(); k++) {
	HistItem *it = list->at(k);
	if (it == item)
	    item->open();
	else
	    item->close();
    }
}
