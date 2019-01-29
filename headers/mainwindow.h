#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVariant>
#include <QAction>
#include <QGridLayout>
#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QDateTime>

#include <QInputDialog>
#include <QMessageBox>
#include <QMouseEvent>

#include <QWidget>
#include <QDialogButtonBox>
#include <QDialog>
#include <QDebug>

#include <QString>
#include <QDir>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    void loadData();
    QString getCurrentTimeStamp();

    QAction *actionAuthor;
    QAction *actionNew_Company;
    QAction *actionNew_FiveCompanies;
    QAction *actionView_Log;
    QWidget *centralWidget;
    QTextEdit *log;
    QGridLayout *gridLayout;
    QTabWidget *companiesTabWidget;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QMenu *menuNew;
    QMenu *menuLog;

private slots:
    void on_actionAuthor_triggered();
    void on_actionNew_Company_triggered();
    void on_actionNew_FiveCompanies_triggered();
    void on_actionView_Log_triggered();
    void onTabBarDoubleClicked(int index);
    void closeTab(int index);
};

#endif // MAINWINDOW_H
