#include <iostream>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QSqlRecord>
#include <QFileDialog>
#include <QDir>

#include "TStyle.h"
#include "TGraph.h" 
#include "TAxis.h" 

#include "mainwindow.h"
#include "dialognewconnection.h"
#include "dialognewplot.h"
#include "histitem.h"


MainWindow::MainWindow() {
    
    initMenu();
    
    query_panel = new QueryPanel;
    stats_panel = new StatsPanel;

    connect(query_panel, 
	    SIGNAL(modelUpdated(QSqlQueryModel *)), 
	    this, 
	    SLOT(onModelUpdate(QSqlQueryModel *)));

    plotConfig = new HistList;
    plotView = new TQtWidget(0, "");
    showPlotButton = new QPushButton(tr("Show/Update plot"));
    addPlotButton = new QPushButton(tr("Add Plot"));

    connect(showPlotButton, SIGNAL(clicked()), this, SLOT(showPlot()));
    connect(addPlotButton, SIGNAL(clicked()), this, SLOT(addPlot()));

    QWidget *centralWidget = new QWidget;

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(query_panel);
    leftLayout->addWidget(stats_panel);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(plotConfig);
    QHBoxLayout *plot_config = new QHBoxLayout;
    plot_config->addWidget(addPlotButton);
    plot_config->addWidget(showPlotButton);
    rightLayout->addLayout(plot_config);
    rightLayout->addWidget(plotView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("DBStats: visualize your data!"));

}

void MainWindow::initMenu() {
    QMenu *file;
    file = menuBar()->addMenu(tr("&File"));

    QAction *connectDB = new QAction(tr("Database connection"), this);
    file->addAction(connectDB);
    connect(connectDB, SIGNAL(triggered()), this, SLOT(connect2db()));
    file->addSeparator();

    QAction *save_project_as = new QAction(tr("Save Project As"), this);
    file->addAction(save_project_as);
    connect(save_project_as, SIGNAL(triggered()), this, SLOT(saveProjectAs()));

    QAction *save_project = new QAction(tr("Save Project"), this);
    file->addAction(save_project);
    connect(save_project, SIGNAL(triggered()), this, SLOT(saveProject()));

    QAction *save_plot_as = new QAction(tr("Save Plot As"), this);
    file->addAction(save_plot_as);
    connect(save_plot_as, SIGNAL(triggered()), this, SLOT(savePlotAs()));
    file->addSeparator();

    QAction *quit = new QAction(tr("Quit"), this);
    quit->setShortcut(tr("CTRL+Q"));
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

}

void MainWindow::connect2db() {
    DialogNewConnection *dialog = new DialogNewConnection(this);
    if (dialog->exec()) {
        dbhost = dialog->get_dbhost();
        dbport = dialog->get_dbport().toInt();
        dbname=dialog->get_dbname();
        dbuser=dialog->get_dbuser();
        dbpasswd=dialog->get_dbpasswd();
        if (createConnection())
	    query_panel->unlock();
	else
	    query_panel->lock();
    }
}

void MainWindow::showPlot() {
    gStyle->SetOptTitle(0);
    plotView->GetCanvas()->cd(); 
    for (unsigned int i = 0; i<objectsToPlot.size(); i++) {
	if (i==0)
	    objectsToPlot[i]->Draw("AP");
	else
	    objectsToPlot[i]->Draw("P same");
    }
    plotView->GetCanvas()->Update(); 
}

bool MainWindow::createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(dbhost);
    db.setPort(dbport);
    db.setDatabaseName(dbname);
    db.setUserName(dbuser);
    db.setPassword(dbpasswd);
    if (!db.open()) {
	QMessageBox::critical(0, tr("Cannot open database"),
			      tr("Unable to establish a connection to your database, "
				 "please check the parameters. \r\n"
				 "Click Cancel to exit."), QMessageBox::Cancel);
	return false;
    }
    return true;
}

void MainWindow::saveProjectAs() {
    QMessageBox::warning(0, tr("Not yet implemented"),
			 tr("This action is not yet possible."), 
			 QMessageBox::Ok);
}

void MainWindow::saveProject() {
    QMessageBox::warning(0, tr("Not yet implemented"),
			 tr("This action is not yet possible."), 
			 QMessageBox::Ok);
}

void MainWindow::savePlotAs() {
    QString filename = QFileDialog::getSaveFileName(this, 
						    tr("Select a file..."), 
						    QDir::homePath()
						    );
    if (filename == "")
	return;
    plotView->GetCanvas()->SaveAs(filename.toStdString().c_str()); 
}

void MainWindow::addPlot() {
    if (!model)
	return;

    DialogNewPlot *dialog = new DialogNewPlot(model);
    if (dialog->exec()) {
	QString plot_type = dialog->get_plot_type();
	QString x_variable = dialog->get_x_variable();
	QString y_variable = dialog->get_y_variable();
	//QString line_color = dialog->get_line_color();

	if (plot_type=="Histogram")
	    create_new_histogram(x_variable);
	else if (plot_type=="Scatter")
	    create_new_scatter(x_variable, y_variable);

	//addPlotButton();
    }

    HistItem *item1 = new HistItem(plotConfig, "Coucou", "Bisosu", false);
    plotConfig->addItem(item1);

}


void MainWindow::create_new_histogram(QString x_variable) {

}

void MainWindow::create_new_scatter(QString x_variable, QString y_variable) {
    int Nobs = model->rowCount();
    double xvalues[Nobs];
    double yvalues[Nobs];
    for (int i = 0; i < Nobs; ++i) {
        double x = model->record(i).value(x_variable).toDouble();
        double y = model->record(i).value(y_variable).toDouble();
    	xvalues[i] = x;
    	yvalues[i] = y;
    }
    TGraph *mygraph; 
    mygraph  = new TGraph(Nobs,xvalues,yvalues); 
    mygraph->SetMarkerStyle(20); 
    mygraph->GetXaxis()->SetTitle(x_variable.toStdString().c_str());
    mygraph->GetYaxis()->SetTitle(y_variable.toStdString().c_str());
    objectsToPlot.push_back(mygraph);
}


void MainWindow::onModelUpdate(QSqlQueryModel *model) {
    stats_panel->onModelUpdate(model);
}
