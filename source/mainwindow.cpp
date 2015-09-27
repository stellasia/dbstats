#include <iostream>

//#include <QtWidget>
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QMessageBox>

#include "TQtWidget.h" 
#include "TGraph.h" 
#include "TCanvas.h" 


#include "mainwindow.h"

MainWindow::MainWindow()
{
    createConnection();

    queryEdit = new QPlainTextEdit;
    resultView = new QTableView;
    runQueryButton = new QPushButton(tr("Run"));

    TQtWidget *MyWidget= new TQtWidget(0,"MyWidget"); 
    MyWidget->GetCanvas()->cd(); 
    TGraph *mygraph; 
    float x[3] = {1,2,3}; 
    float y[3] = {1.5, 3.0, 4.5}; 
    mygraph  = new TGraph(3,x,y); 
    mygraph->SetMarkerStyle(20); 
    mygraph->Draw("APL"); 
    MyWidget->GetCanvas()->Update(); 

    connect(runQueryButton, SIGNAL(clicked()), this, SLOT(runQuery()));

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(queryEdit);
    mainLayout->addWidget(runQueryButton);
    mainLayout->addWidget(resultView);
    mainLayout->addWidget(MyWidget);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("DBStats: visualize your data!"));

}


void MainWindow::runQuery() {

    QString query = queryEdit->toPlainText();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

    //std::cout << model->rowCount() << std::endl;

    resultView->setModel(model);
}


bool MainWindow::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("dbstats");
    db.setUserName("postgres");
    db.setPassword("postgres");
    if (!db.open()) {
        QMessageBox::critical(0, tr("Cannot open database"),
				  tr("Unable to establish a connection to your database, "
				       "please check the parameters. \r\n"
				       "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}
