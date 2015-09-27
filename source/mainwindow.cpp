#include <iostream>

#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLabel>

#include "TGraph.h" 

#include "mainwindow.h"
#include "dialognewconnection.h"


MainWindow::MainWindow() {
    
    initMenu();
    
    queryEdit = new QPlainTextEdit;
    queryEdit->setPlainText("select * from products ");
    queryEdit->setReadOnly(true);
    resultView = new QTableView;
    runQueryButton = new QPushButton(tr("Run"));
    QLabel *label_querylimit = new QLabel(tr("Limit"));
    queryLimit = new QLineEdit;
    queryLimit->setValidator( new QIntValidator(0, 1000000, this) );
    queryLimit->setText("1000");
    plotConfig = new QPlainTextEdit;
    plotConfig->setPlainText("Configure plots here");
    plotView = new TQtWidget(0, "");
    showPlotButton = new QPushButton(tr("Plot"));

    connect(runQueryButton, SIGNAL(clicked()), this, SLOT(runQuery()));
    connect(showPlotButton, SIGNAL(clicked()), this, SLOT(showPlot()));

    QWidget *centralWidget = new QWidget;

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(queryEdit);
    QHBoxLayout *config = new QHBoxLayout;
    config->addWidget(label_querylimit);
    config->addWidget(queryLimit);
    config->addWidget(runQueryButton);
    leftLayout->addLayout(config);
    leftLayout->addWidget(resultView);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(plotConfig);
    rightLayout->addWidget(showPlotButton);
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
	    queryEdit->setReadOnly(false);
	else
	    queryEdit->setReadOnly(true);
    }
}

void MainWindow::runQuery() {
    QString query = queryEdit->toPlainText();

    int limit = queryLimit->text().toInt();
    if (limit > 0)
	query = QString(query + " LIMIT %1").arg(limit);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    //std::cout << model->rowCount() << std::endl;
    resultView->setModel(model);
}

void MainWindow::showPlot() {
    plotView->GetCanvas()->cd(); 
    TGraph *mygraph; 
    float x[3] = {1,2,3}; 
    float y[3] = {1.5, 3.0, 4.5}; 
    mygraph  = new TGraph(3,x,y); 
    mygraph->SetMarkerStyle(20); 
    mygraph->Draw("AP"); 
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
