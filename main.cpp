#include "mainwindow.h"
#include <QApplication>
//#include "globals.h"
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString qName = "Payroll System";
    w.setWindowTitle(qName);
    w.show();

    return a.exec();
}
