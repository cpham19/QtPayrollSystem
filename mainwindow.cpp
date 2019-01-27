#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "companytabwidget.h"
#include "globals.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    loadData();
}

MainWindow::~MainWindow()
{
    delete this;
}

void MainWindow::loadData() {
    QDir dir;

    QString fileName = "firstnames.txt";
    QString path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile firstNamesFile(path);

    if (firstNamesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&firstNamesFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          firstNames.push_back(line);
       }
       firstNamesFile.close();
    }

    qDebug() << "Loaded" << (int) firstNames.size() << "first names from " + fileName;

    fileName = "lastnames.txt";
    path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile lastNamesFile(path);

    if (lastNamesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&lastNamesFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          lastNames.push_back(line);
       }
       lastNamesFile.close();
    }

    qDebug() << "Loaded" << (int) lastNames.size() << "last names from " + fileName;

    fileName = "streets.txt";
    path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile streetsFile(path);

    if (streetsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&streetsFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          streets.push_back(line);
       }
       streetsFile.close();
    }

    qDebug() << "Loaded" << (int) streets.size() << "streets from " + fileName;

    fileName = "streetsuffixes.txt";
    path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile streetSuffixesFile(path);

    if (streetSuffixesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&streetSuffixesFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          streetSuffixes.push_back(line);
       }
       streetSuffixesFile.close();
    }

    qDebug() << "Loaded" << (int) streetSuffixes.size() << "street suffixes from " + fileName;

    fileName = "states.txt";
    path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile statesFile(path);

    if (statesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&statesFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          states.push_back(line);
       }
       statesFile.close();
    }

    qDebug() << "Loaded" << (int) states.size() << "states from " + fileName;

    fileName = "cities.txt";
    path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile citiesFile(path);

    if (citiesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&citiesFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          cities.push_back(line);
       }
       citiesFile.close();
    }

    qDebug() << "Loaded" << (int) cities.size() << "cities from " + fileName;

    fileName = "zipcodes.txt";
    path = dir.homePath() + "/Documents/QApplication/" + fileName;
    QFile zipcodesFile(path);

    if (zipcodesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&zipcodesFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          zipcodes.push_back(line);
       }
       zipcodesFile.close();
    }

    qDebug() << "Loaded" << (int) zipcodes.size() << "zipcodes from " + fileName;
}

void MainWindow::setupUi(QMainWindow *MainWindow) {
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

    // Main Tab Widget
    companiesTabWidget = new QTabWidget(centralWidget);
    companiesTabWidget->setObjectName(QString::fromUtf8("companiesTabWidget"));
    companiesTabWidget->setTabsClosable(true);
    companiesTabWidget->setCurrentIndex(-1);
    companiesTabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 120px;}");
    connect(companiesTabWidget, &QTabWidget::tabBarDoubleClicked, this, &MainWindow::onTabBarDoubleClicked);
    connect(companiesTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

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

void MainWindow::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Payroll System", nullptr));
    actionAuthor->setText(QApplication::translate("MainWindow", "Author", nullptr));
    actionNew_Company->setText(QApplication::translate("MainWindow", "New Company", nullptr));
    menuAbout->setTitle(QApplication::translate("MainWindow", "About", nullptr));
    menuNew->setTitle(QApplication::translate("MainWindow", "New", nullptr));
} // retranslateUi

void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Author");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Created by <a href='https://github.com/cpham19'>Calvin Pham</a>");
    msgBox.exec();
}

void MainWindow::on_actionNew_Company_triggered()
{
    counter++;
    QString name = "Company#" + QString::number(counter);
    CompanyTabWidget *company = new CompanyTabWidget(companiesTabWidget, name);
    company->setObjectName(name);
    companiesTabWidget->addTab(company, name);
}

void MainWindow::onTabBarDoubleClicked(int index)
{
    // Get the widget at the tab
    CompanyTabWidget *tabWidget = (CompanyTabWidget *) companiesTabWidget->widget(index);

    // Dialog to rename company
    bool ok = true;
    QString newName = QInputDialog::getText (
                this, tr ("Change Company Name"),
                tr ("Insert New Company Name"),
                QLineEdit::Normal,
                "",
                &ok);

    companiesTabWidget->setTabText(index, newName);
    tabWidget->ps->setNameOfCompany(newName);
    tabWidget->nameOfCompanyLabel->setText("Company Name: " + tabWidget->ps->getNameOfCompany());
}

void MainWindow::closeTab(int index) {
    companiesTabWidget->removeTab(index);
}
