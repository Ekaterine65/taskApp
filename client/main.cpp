#include "client.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client::getInstance();
    MainWindow::getInstance()->show();
    return a.exec();
}
