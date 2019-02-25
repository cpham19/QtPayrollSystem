#include "headers/mainwindow.h"
#include "headers/companytabwidget.h"
#include "headers/globals.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    createFolder();
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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) maleFirstNames.size()) + " first names from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) femaleFirstNames.size()) + " first names from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) lastNames.size()) + " last names from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) jobs.size()) + " jobs from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) streets.size()) + " streets from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) streetSuffixes.size()) + " street suffixes from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) states.size()) + " states from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) cities.size()) + " cities from " + fileName + ".");

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
    mainLog->append(getCurrentTimeStamp() + " Loaded " + QString::number((int) zipcodes.size()) + " zipcodes from " + fileName + ".");
}

void MainWindow::setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty()) {
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    }

    MainWindow->resize(1280, 720);

    // Menu Bar Actions
    actionAuthor = new QAction(MainWindow);
    actionAuthor->setObjectName(QString::fromUtf8("actionAuthor"));

    actionNewCompany = new QAction(MainWindow);
    actionNewCompany->setObjectName(QString::fromUtf8("actionNewCompany"));

    actionOpenFile = new QAction(MainWindow);
    actionOpenFile->setObjectName(QString::fromUtf8(("actionOpenFile")));

    actionViewMainLog = new QAction(MainWindow);
    actionViewMainLog->setObjectName(QString::fromUtf8("actionViewMainLog"));

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

    // mainLog Widget
    mainLog = new QTextEdit();
    mainLog->setReadOnly(true);
    mainLog->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

    MainWindow->setCentralWidget(centralWidget);

    // Menu Bar
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 1280, 50));

    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));

    menuAbout = new QMenu(menuBar);
    menuAbout->setObjectName(QString::fromUtf8("menuAbout"));

    menuMainLog = new QMenu(menuBar);
    menuMainLog->setObjectName(QString::fromUtf8("menuMainLog"));

    MainWindow->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuAbout->menuAction());
    menuBar->addAction(menuMainLog->menuAction());

    menuAbout->addAction(actionAuthor);

    menuFile->addAction(actionOpenFile);
    menuFile->addAction(actionNewCompany);

    menuMainLog->addAction(actionViewMainLog);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void MainWindow::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Payroll System", nullptr));
    actionAuthor->setText(QApplication::translate("MainWindow", "Author", nullptr));
    actionNewCompany->setText(QApplication::translate("MainWindow", "New Company", nullptr));
    actionViewMainLog->setText(QApplication::translate("MainWindow", "View Log", nullptr));
    actionOpenFile->setText(QApplication::translate("MainWindow", "Open File", nullptr));
    menuAbout->setTitle(QApplication::translate("MainWindow", "About", nullptr));
    menuMainLog->setTitle(QApplication::translate("MainWindow", "Log", nullptr));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
} // retranslateUi

void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Author");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Created by <a href='https://github.com/cpham19'>Calvin Pham</a>");
    msgBox.exec();
}

void MainWindow::on_actionNewCompany_triggered()
{
    counter++;
    QString name = "Company#" + QString::number(counter);
    CompanyTabWidget *company = new CompanyTabWidget(companiesTabWidget, name);
    company->setObjectName(name);
    companiesTabWidget->addTab(company, name);
    mainLog->append(getCurrentTimeStamp() + " Added a new company '" + name + "'.");
}

void MainWindow::on_actionViewMainLog_triggered()
{
    mainLog->resize(400, 400);
    mainLog->setWindowTitle("Log");
    mainLog->show();
}

void MainWindow::on_actionOpenFile_triggered() {
    QString path = qApp->applicationDirPath() + "/csv";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File"), path,tr("Comma-Separated Values File (*.csv);;All Files (*)"));

    if (fileName.isEmpty()) {
        return;
    }
    else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QTextStream in(&file);

        int lineNumber = 1;
        CompanyTabWidget *company = new CompanyTabWidget(companiesTabWidget, "Temp Name");
        QString nameOfTab;

        while (!in.atEnd())
        {
           QString line = in.readLine();

           if (lineNumber == 2) {
               QStringList list = line.split(",");
               QString nameOfCompany = list[0];
               QString numberOfEmployees = list[1];
               QString amountPaid = list[2];

               nameOfTab = list[0];
               company->setObjectName(nameOfCompany);
               company->ps->setNameOfCompany(nameOfCompany);
               company->ps->setTotalAmount(amountPaid.toDouble());
           }
           else if (lineNumber >= 6) {
               QStringList list = line.split(",");

               company->addEmployeeByQStringList(list);
           }

           lineNumber++;
        }
        file.close();

        company->update();
        companiesTabWidget->addTab(company, nameOfTab);
        mainLog->append(getCurrentTimeStamp() + " Loaded a company '" + nameOfTab + "' from " + fileName + ".");
        counter++;
    }
}

void MainWindow::onTabBarDoubleClicked(int index) {
    // Get the widget at the tab
    CompanyTabWidget *tabWidget = (CompanyTabWidget *) companiesTabWidget->widget(index);

    // DiamainLog to rename company
    bool ok = true;
    QString newName = QInputDialog::getText (
                this, tr ("Change Company Name"),
                tr ("Insert New Company Name"),
                QLineEdit::Normal,
                tabWidget->ps->getNameOfCompany(),
                &ok);

    if (ok && !newName.isEmpty()) {
        mainLog->append(getCurrentTimeStamp() + " Renaming company '" + tabWidget->ps->getNameOfCompany() + "' to " + "'" + newName +"'.");
        companiesTabWidget->setTabText(index, newName);
        tabWidget->ps->setNameOfCompany(newName);
        tabWidget->nameOfCompanyLabel->setText("Company Name: " + tabWidget->ps->getNameOfCompany());
    }
}

void MainWindow::createFolder() {
    if (!QDir(qApp->applicationDirPath() + "/csv").exists()) {
        QDir().mkdir(qApp->applicationDirPath() + "/csv");
    }
}

void MainWindow::closeTab(int index) {
    // Get the widget at the tab
    CompanyTabWidget *tabWidget = (CompanyTabWidget *) companiesTabWidget->widget(index);
    tabWidget->stopTimer();

    companiesTabWidget->removeTab(index);

    mainLog->append(getCurrentTimeStamp() + " Closed Tab#" + QString::number(index));
}

QString MainWindow::getCurrentTimeStamp() {
    QString timestamp = "[" + QDateTime::currentDateTime().toString() + "]";
    return timestamp;
}
