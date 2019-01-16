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
    CompanyTabWidget *company = new CompanyTabWidget(companiesTabWidget);
    counter++;
    QString name = "Company #" + QString::number(counter);
    company->ps->setNameOfCompany(name);
    companiesTabWidget->addTab(company, name);
    companiesTabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 100px;}");
}
