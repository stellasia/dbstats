#include <QVBoxLayout>
//#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

#include "plotdrawingsubpanel.h"


PlotDrawingSubpanel::PlotDrawingSubpanel(QWidget *parent) {

    canvas = new TQtWidget(0, "");
    reset_canvas_button = new QPushButton(tr("Reset"));
    save_canvas_as_button = new QPushButton(tr("Save As"));

    connect(reset_canvas_button, SIGNAL(clicked()),
	    this, SLOT(resetCanvas()));
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
    //canvas->GetCanvas()->ResetDrawn();
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


void PlotDrawingSubpanel::draw(TObject *obj, Option_t *option) {
    canvas->GetCanvas()->cd();
    if (obj) {
	// obj->SetLineWidth(2);
	// obj->SetLineColor(kBlue);
	obj->Draw("COLZ");
    }
    canvas->GetCanvas()->Update();
}
