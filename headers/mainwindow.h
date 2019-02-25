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
#include <QFileDialog>
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
    void createFolder();
    QString getCurrentTimeStamp();

    QAction *actionOpenFile;
    QAction *actionNewCompany;
    QAction *actionAuthor;
    QAction *actionViewMainLog;
    QAction *openFile;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *companiesTabWidget;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QMenu *menuFile;
    QMenu *menuMainLog;

private slots:
    void on_actionAuthor_triggered();
    void on_actionNewCompany_triggered();
    void on_actionOpenFile_triggered();
    void on_actionViewMainLog_triggered();
    void onTabBarDoubleClicked(int index);
    void closeTab(int index);
};

#endif // MAINWINDOW_H
