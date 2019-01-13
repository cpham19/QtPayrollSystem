#include "mainwindow.h"
#include <QApplication>
#include "globals.h"
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ps->setNameOfCompany("Company #1");
    ps->addEmployee("E1", "Calvin", "Pham", "Male", "Software Engineer", "1234 Fake Street", "Fake City", "California", "12345", 40.5, 40);
    ps->addEmployee("E2", "Paul", "French", "Male", "Software Engineer", "1234 Fake Street", "Fake City", "California", "12316", 12, 45);

    w.setUpValidators();
    w.refreshList();

    QString qName = "Payroll System of " + ps->getNameOfCompany();

    w.setWindowTitle(qName);
    w.show();

    return a.exec();
}
