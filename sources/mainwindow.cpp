#include "headers/mainwindow.h"
#include "headers/companytabwidget.h"
#include "headers/globals.h"

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
    QString fileName = "malefirstNames.txt";
    QString path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile maleFirstNamesFile(path);

    if (maleFirstNamesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&maleFirstNamesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            maleFirstNames.push_back(line);
        }
        maleFirstNamesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) maleFirstNames.size()) + " first names from " + fileName + ".");

    fileName = "femalefirstNames.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile femaleFirstNamesFile(path);

    if (femaleFirstNamesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&femaleFirstNamesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            femaleFirstNames.push_back(line);
        }
        femaleFirstNamesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) femaleFirstNames.size()) + " first names from " + fileName + ".");

    fileName = "lastnames.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile lastNamesFile(path);

    if (lastNamesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&lastNamesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            lastNames.push_back(line);
        }
        lastNamesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) lastNames.size()) + " last names from " + fileName + ".");

    fileName = "jobs.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile jobsFile(path);

    if (jobsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&jobsFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            jobs.push_back(line);
        }
        jobsFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) jobs.size()) + " jobs from " + fileName + ".");

    fileName = "streets.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile streetsFile(path);

    if (streetsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&streetsFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            streets.push_back(line);
        }
        streetsFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) streets.size()) + " streets from " + fileName + ".");

    fileName = "streetsuffixes.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile streetSuffixesFile(path);

    if (streetSuffixesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&streetSuffixesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            streetSuffixes.push_back(line);
        }
        streetSuffixesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) streetSuffixes.size()) + " street suffixes from " + fileName + ".");

    fileName = "states.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile statesFile(path);

    if (statesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&statesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            states.push_back(line);
        }
        statesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) states.size()) + " states from " + fileName + ".");

    fileName = "cities.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile citiesFile(path);

    if (citiesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&citiesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            cities.push_back(line);
        }
        citiesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) cities.size()) + " cities from " + fileName + ".");

    fileName = "zipcodes.txt";
    path = qApp->applicationDirPath() + "/txt/" + fileName;
    QFile zipcodesFile(path);

    if (zipcodesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&zipcodesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            zipcodes.push_back(line);
        }
        zipcodesFile.close();
    }
    log->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) zipcodes.size()) + " zipcodes from " + fileName + ".");
}

void MainWindow::setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty()) {
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    }

    MainWindow->resize(1280, 720);

    // Menu Bar Actions
    actionAuthor = new QAction(MainWindow);
    actionAuthor->setObjectName(QString::fromUtf8("actionAuthor"));

    actionNew_Company = new QAction(MainWindow);
    actionNew_Company->setObjectName(QString::fromUtf8("actionNew_Company"));

    actionNew_FiveCompanies = new QAction(MainWindow);
    actionNew_FiveCompanies->setObjectName(QString::fromUtf8("actionNew_FiveCompanies"));

    actionView_Log = new QAction(MainWindow);
    actionView_Log->setObjectName(QString::fromUtf8("actionView_Log"));

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

    // Log Widget
    log = new QTextEdit();
    log->setReadOnly(true);
    log->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

    MainWindow->setCentralWidget(centralWidget);

    // Menu Bar
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 1280, 50));

    menuAbout = new QMenu(menuBar);
    menuAbout->setObjectName(QString::fromUtf8("menuAbout"));

    menuNew = new QMenu(menuBar);
    menuNew->setObjectName(QString::fromUtf8("menuNew"));

    menuLog = new QMenu(menuBar);
    menuLog->setObjectName(QString::fromUtf8("menuLog"));

    MainWindow->setMenuBar(menuBar);
    menuBar->addAction(menuNew->menuAction());
    menuBar->addAction(menuAbout->menuAction());
    menuBar->addAction(menuLog->menuAction());

    menuAbout->addAction(actionAuthor);

    menuNew->addAction(actionNew_Company);
    menuNew->addAction(actionNew_FiveCompanies);

    menuLog->addAction(actionView_Log);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void MainWindow::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Payroll System", nullptr));
    actionAuthor->setText(QApplication::translate("MainWindow", "Author", nullptr));
    actionNew_Company->setText(QApplication::translate("MainWindow", "New Company", nullptr));
    actionNew_FiveCompanies->setText(QApplication::translate("MainWindow", "New Five Companies", nullptr));
    actionView_Log->setText(QApplication::translate("MainWindow", "View Log", nullptr));
    menuAbout->setTitle(QApplication::translate("MainWindow", "About", nullptr));
    menuNew->setTitle(QApplication::translate("MainWindow", "New", nullptr));
    menuLog->setTitle(QApplication::translate("MainWindow", "Log", nullptr));
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
    log->append(getCurrentTimeStamp() + " Added a new company.");
}

void MainWindow::on_actionNew_FiveCompanies_triggered()
{
    for (int i = 1; i <= 5; i++) {
        counter++;
        QString name = "Company#" + QString::number(counter);
        CompanyTabWidget *company = new CompanyTabWidget(companiesTabWidget, name);
        company->setObjectName(name);
        companiesTabWidget->addTab(company, name);
    }
    log->append(getCurrentTimeStamp() + " Added five new companies.");
}

void MainWindow::on_actionView_Log_triggered()
{
    log->resize(400, 400);
    log->show();
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

    log->append(getCurrentTimeStamp() + " Renaming company '" + tabWidget->ps->getNameOfCompany() + "' to " + "'" + newName +"'.");
    companiesTabWidget->setTabText(index, newName);
    tabWidget->ps->setNameOfCompany(newName);
    tabWidget->nameOfCompanyLabel->setText("Company Name: " + tabWidget->ps->getNameOfCompany());
}

void MainWindow::closeTab(int index) {
    companiesTabWidget->removeTab(index);
    log->append(getCurrentTimeStamp() + " Closed Tab#" + QString::number(index));
}

QString MainWindow::getCurrentTimeStamp() {
    QString timestamp = "[" + QDateTime::currentDateTime().toString() + "]";
    return timestamp;
}
