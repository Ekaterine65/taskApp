#include "client.h"
#include "mainwindow.h"
#include "teachertable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client::getInstance();
    teacherTable::getInstance();
    MainWindow::getInstance()->show();
    return a.exec();
}
