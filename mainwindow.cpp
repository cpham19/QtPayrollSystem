#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "companytabwidget.h"
#include "globals.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    CompanyTabWidget *company = new CompanyTabWidget(ui->companiesTabWidget);
    counter++;
    ui->companiesTabWidget->addTab(company, "Company #" + QString::number(counter));
}
