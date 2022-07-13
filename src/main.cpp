#include "mainwindow.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("BrainfuckIDE");
    QCoreApplication::setApplicationVersion("0.0.1");
    MainWindow w;
    w.show();
    return a.exec();
}
