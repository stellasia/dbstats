#ifndef PLOTDRAWINGSUBPANEL_H
#define PLOTDRAWINGSUBPANEL_H

#include <QWidget>
#include <QPushButton>

#include "TQtWidget.h" 


class PlotDrawingSubpanel : public QWidget
{
    Q_OBJECT

public:
    PlotDrawingSubpanel(QWidget *parent = 0);

private slots:
    void resetCanvas();
    void saveCanvasAs();

public slots:
    void draw(TObject *, Option_t *option="");
    
private:
    TQtWidget *canvas;
    QPushButton *reset_canvas_button;
    QPushButton *save_canvas_as_button;

};

#endif
