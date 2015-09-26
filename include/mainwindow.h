#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTableView>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    static bool createConnection();

private slots:
    void runQuery();

private:
  QPlainTextEdit *queryEdit;
  QTableView *resultView;
  QPushButton *runQueryButton;

};
