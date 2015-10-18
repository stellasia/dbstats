#ifndef SPINBOX_H
#define SPINBOX_H 

#include <QSpinBox>

class SpinBox : public QSpinBox {

 public:
    SpinBox(int minimum=0, int maximum=99, bool wrapping=false) {
	setMinimum(minimum);
	setMaximum(maximum);
	setWrapping(wrapping);
    }

};

#endif
