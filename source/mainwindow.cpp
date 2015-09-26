#include <QtWidgets>
#include <QSqlQueryModel>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    createConnection();

    queryEdit = new QPlainTextEdit;
    resultView = new QTableView;
    runQueryButton = new QPushButton(tr("Run"));

    connect(runQueryButton, SIGNAL(clicked()), this, SLOT(runQuery()));

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(queryEdit);
    mainLayout->addWidget(runQueryButton);
    mainLayout->addWidget(resultView);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("DBStats: visualize your data!"));

}


void MainWindow::runQuery() {

    QString query = queryEdit->toPlainText();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);

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
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
			      qApp->tr("Unable to establish a connection to your database, "
				       "please check the parameters. \r\n"
				       "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}
