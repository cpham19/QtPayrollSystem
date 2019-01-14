#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAuthor_triggered();
    void on_actionNew_Company_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
