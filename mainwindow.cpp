#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "companytabwidget.h"
#include "globals.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
    delete this;
}

void MainWindow::on_actionAuthor_triggered()
{
    QLabel *author = new QLabel();
    author->setWindowFlags(Qt::Window);
    author->setText("THIS WAS WRITTEN BY CALVIN");
    author->setAttribute(Qt::WA_DeleteOnClose);
    author->show();
}

void MainWindow::on_actionNew_Company_triggered()
{
    QString name = "Company#" + QString::number(counter);
    CompanyTabWidget *company = new CompanyTabWidget(companiesTabWidget, name);
    company->setObjectName(name);
    companiesTabWidget->addTab(company, name);
    companiesTabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 100px;}");
    counter++;
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
