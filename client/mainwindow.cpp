#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regform.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openRegForm_clicked()
{
    regForm::getInstance()->show();
}


void MainWindow::on_authButton_clicked()
{
    Client::getInstance()->user_login = ui->loginEdit->text();
    Client::getInstance()->user_pass = ui->passwordEdit->text();
    Client::getInstance()->auth(ui->loginEdit->text(), ui->passwordEdit->text());
}

void MainWindow::is_auth_suc(bool key)
{

}

