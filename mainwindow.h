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

#include <QTabWidget>
#include <QTabBar>
#include <QInputDialog>
#include <QMouseEvent>

#include <QWidget>
#include <QDialogButtonBox>
#include <QDialog>
#include <QDebug>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *actionAuthor;
    QAction *actionNew_Company;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *companiesTabWidget;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QMenu *menuNew;

    void setupUi(QMainWindow *MainWindow)
       {
           if (MainWindow->objectName().isEmpty()) {
               MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
            }

           MainWindow->resize(1280, 720);
           actionAuthor = new QAction(MainWindow);
           actionAuthor->setObjectName(QString::fromUtf8("actionAuthor"));

           actionNew_Company = new QAction(MainWindow);
           actionNew_Company->setObjectName(QString::fromUtf8("actionNew_Company"));

           // Main widget for our window
           centralWidget = new QWidget(MainWindow);
           centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

           // Grid layout
           gridLayout = new QGridLayout(centralWidget);
           gridLayout->setSpacing(6);
           gridLayout->setContentsMargins(11, 11, 11, 11);
           gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

           // Main Tab Widget and Tab Bar
           //mainTabBar = new MainTabBar();
           companiesTabWidget = new QTabWidget(centralWidget);
           companiesTabWidget->setObjectName(QString::fromUtf8("companiesTabWidget"));
           companiesTabWidget->setTabsClosable(false);
           companiesTabWidget->setCurrentIndex(-1);
           connect(companiesTabWidget, &QTabWidget::tabBarDoubleClicked, this, &MainWindow::onTabBarDoubleClicked);

           gridLayout->addWidget(companiesTabWidget, 0, 0, 1, 1);

           MainWindow->setCentralWidget(centralWidget);

           // Menu Bar
           menuBar = new QMenuBar(MainWindow);
           menuBar->setObjectName(QString::fromUtf8("menuBar"));
           menuBar->setGeometry(QRect(0, 0, 1280, 50));
           menuAbout = new QMenu(menuBar);
           menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
           menuNew = new QMenu(menuBar);
           menuNew->setObjectName(QString::fromUtf8("menuNew"));
           MainWindow->setMenuBar(menuBar);
           menuBar->addAction(menuNew->menuAction());
           menuBar->addAction(menuAbout->menuAction());
           menuAbout->addAction(actionAuthor);
           menuNew->addAction(actionNew_Company);

           retranslateUi(MainWindow);

           QMetaObject::connectSlotsByName(MainWindow);
       } // setupUi

       void retranslateUi(QMainWindow *MainWindow)
       {
           MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Payroll System", nullptr));
           actionAuthor->setText(QApplication::translate("MainWindow", "Author", nullptr));
           actionNew_Company->setText(QApplication::translate("MainWindow", "New Company", nullptr));
           menuAbout->setTitle(QApplication::translate("MainWindow", "About", nullptr));
           menuNew->setTitle(QApplication::translate("MainWindow", "New", nullptr));
       } // retranslateUi

private slots:
    void on_actionAuthor_triggered();
    void on_actionNew_Company_triggered();
    void onTabBarDoubleClicked(int index);
};

#endif // MAINWINDOW_H
