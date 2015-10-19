//#include <iostream>

#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

#include "plotdrawingsubpanel.h"


PlotDrawingSubpanel::PlotDrawingSubpanel(QWidget *parent) {

    canvas = new TQtWidget(0, "");
    reset_canvas_button = new QPushButton(tr("Reset"));
    save_canvas_as_button = new QPushButton(tr("Save As"));

    // connect(reset_canvas_button, SIGNAL(clicked()),
    // 	    this, SLOT(resetCanvas()));
    connect(reset_canvas_button, SIGNAL(clicked()), canvas, SLOT(Refresh()));
    connect(save_canvas_as_button, SIGNAL(clicked()),
	    this, SLOT(saveCanvasAs()));

    QHBoxLayout *blayout = new QHBoxLayout;
    blayout->addWidget(reset_canvas_button);
    blayout->addWidget(save_canvas_as_button);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(canvas);
    vlayout->addLayout(blayout);

    setLayout(vlayout);
}

void PlotDrawingSubpanel::resetCanvas() {
    canvas->Refresh();
}

void PlotDrawingSubpanel::saveCanvasAs() {
    QString filename = QFileDialog::getSaveFileName(this, 
    						    tr("Select a file..."), 
    						    QDir::homePath()
    						    );
    if (filename == "")
    	return;
    canvas->GetCanvas()->SaveAs(filename.toStdString().c_str()); 
}


void PlotDrawingSubpanel::draw(TObject *obj, QString option) {
    if (obj) {
	canvas->cd();
	obj->Draw(option.toStdString().c_str());
	canvas->Refresh();
	update();
    }
    else {
	QMessageBox::critical(0, tr("Error"),
			      tr("Plot could not be created...!"), 
			      QMessageBox::Ok);
    }
}
