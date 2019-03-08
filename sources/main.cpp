#include "headers/mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowIcon(QIcon(qApp->applicationDirPath() + "/img/payroll.ico"));
    w.show();

    return a.exec();
}
