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

    QAction *actionAuthor;
    QAction *actionNew_Company;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *companiesTabWidget;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QMenu *menuNew;

private slots:
    void on_actionAuthor_triggered();
    void on_actionNew_Company_triggered();
    void onTabBarDoubleClicked(int index);
    void closeTab(int index);
};

#endif // MAINWINDOW_H
