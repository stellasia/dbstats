#include <iostream>

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QSplitter>

#include "mainwindow.h"
#include "dialognewconnection.h"


MainWindow::MainWindow() {
    
    initMenu();
    
    query_panel = new QueryPanel(this);
    stats_panel = new StatsPanel(this);

    connect(query_panel, 
	    SIGNAL(modelUpdated(QSqlQueryModel *)), 
	    this, 
	    SLOT(onModelUpdate(QSqlQueryModel *)));


    plot_panel = new PlotPanel(this);

    // Default behaviour is disabled
    query_panel->setEnabled(false);
    plot_panel->setEnabled(false);

    QSplitter *split1 = new QSplitter;
    split1->setOrientation(Qt::Vertical);
    split1->addWidget(query_panel);
    split1->addWidget(stats_panel);

    QSplitter *split2 = new QSplitter;
    split2->addWidget(split1);
    split2->addWidget(plot_panel);

    setCentralWidget(split2);

    setWindowTitle(tr("DBStats: visualize your data!"));

}

void MainWindow::initMenu() {
    QMenu *file = menuBar()->addMenu(tr("&File"));

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


    QMenu *tools = menuBar()->addMenu(tr("&Tools"));

    QAction *edit_settings = new QAction(tr("Settings"), this);
    tools->addAction(edit_settings);
    connect(edit_settings, SIGNAL(triggered()), this, SLOT(editSettings()));

    QMenu *help = menuBar()->addMenu(tr("&?"));
    QAction *show_help = new QAction(tr("Help"), this);
    help->addAction(show_help);
    connect(show_help, SIGNAL(triggered()), this, SLOT(showHelp()));
    help->addSeparator();

    QAction *show_about = new QAction(tr("About"), this);
    help->addAction(show_about);
    connect(show_about, SIGNAL(triggered()), this, SLOT(showAbout()));

}

void MainWindow::connect2db() {
    DialogNewConnection *dialog = new DialogNewConnection(this);
    if (dialog->exec()) {
	query_panel->setEnabled(true);
	plot_panel->setEnabled(true);
    }
    else {
	query_panel->setEnabled(false);
	plot_panel->setEnabled(false);
    }
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
    // QString filename = QFileDialog::getSaveFileName(this, 
    // 						    tr("Select a file..."), 
    // 						    QDir::homePath()
    // 						    );
    // if (filename == "")
    // 	return;
    // plotView->GetCanvas()->SaveAs(filename.toStdString().c_str()); 
}

void MainWindow::editSettings() {
    QMessageBox::warning(0, tr("Not yet implemented"),
			 tr("This action is not yet possible."), 
			 QMessageBox::Ok);
}

void MainWindow::showHelp() {
    QMessageBox::warning(0, tr("Not yet implemented"),
			 tr("This action is not yet possible."), 
			 QMessageBox::Ok);
}

void MainWindow::showAbout() {
    QMessageBox::about(0, tr("About dbstats"), 
		       tr("dbstats was developed by Estelle Scifo (aka stellasia).\nIt is based on the Qt and ROOT frameworks. "));
}

void MainWindow::onModelUpdate(QSqlQueryModel *model) {
    stats_panel->onModelUpdate(model);
    plot_panel->onModelUpdate(model);
}
