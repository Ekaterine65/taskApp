#include "client.h"
#include "singleclient.h"
#include <QMessageBox>
#include <QtWidgets>
#include "tasks.h"
#include "ui_tasks.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regform.h"
#include "ui_regform.h"
#include "teachertable.h"
#include "ui_teachertable.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    connect(SingletonClient::getInstance(), &SingletonClient::serverAnswer, this, &Client::parser);
}

Client::~Client()
{

}

void Client::auth(QString login, QString password)
{
    user_login = login;
    user_pass = password;
    SingletonClient::getInstance()->sendToServer("auth " + login + " " + password + "\n");
}

void Client::reg(QString login, QString password, bool studentOrTeacher, QString teacherLogin)
{
    // Если тип учетной записи - преподаватель, то teacherCode пустой, это может вызвать ошибку на сервере
    SingletonClient::getInstance()->sendToServer("reg " + login + " " + password + " " + teacherLogin + " " + QString::number(int(studentOrTeacher)) + "\n");
}

void Client::get_auth(QString key, QString type) {
    if (key == "1") {
        QMessageBox::information(this, "Успешная авторизация", "Вы успешно авторизированы.");
        if (type == "0") {
            tasks::getInstance()->show();
            regForm::getInstance()->hide();
            MainWindow::getInstance()->hide();
        } else {
            regForm::getInstance()->hide();
            MainWindow::getInstance()->hide();
            teacherTable::getInstance()->show();
            SingletonClient::getInstance()->sendToServer("get_stats " + user_login);
        }
    } else {
        Client::getInstance()->user_login = "";
        Client::getInstance()->user_pass = "";
        QMessageBox::critical(this, "Ошибка авторизации", "Авторизация не удалась. Пожалуйста, попробуйте ещё раз.");
    }
}

void Client::get_reg(QString key) {
    if (key == "1") {
        QMessageBox::information(this, "Успешная регистрация", "Вы успешно зарегистрированы.");
        regForm::getInstance()->hide();
    } else {
        QMessageBox::critical(this, "Ошибка регистрации", "Регистрация не удалась. Пожалуйста, попробуйте ещё раз.");
    }
    regForm::getInstance()->ui->loginEdit->setText("");
    regForm::getInstance()->ui->passwordEdit->setText("");
    regForm::getInstance()->ui->teacher_login->setText("");
}

void Client::fill_table(QString stats) {
    QTableWidget *tableWidge = teacherTable::getInstance()->tableWidget;
    QStringList records = stats.split('$', Qt::SkipEmptyParts);

    // Получите существующий QTableWidget из teacherTable
    QTableWidget* tableWidget = teacherTable::getInstance()->tableWidget;

    // Убедитесь, что таблица создана и готова к заполнению
    tableWidget->clear();
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"Логин студента", "Верные попытки", "Неверные попытки", "Результативность"});

    int row = 0;
    for (const QString& record : records) {
        // Разделить запись на отдельные элементы, используя пробел как разделитель
        QStringList fields = record.split(' ', Qt::SkipEmptyParts);

        if (fields.size() == 3) {
            QString username = fields[0];
            QString correctAttempts = fields[1];
            QString incorrectAttempts = fields[2];

            // Рассчитайте результативность
            int totalAttempts = correctAttempts.toInt() + incorrectAttempts.toInt();
            QString effectiveness;
            if (totalAttempts != 0) {
                effectiveness = QString::number(correctAttempts.toInt() * 100 / totalAttempts) + "%";
            } else {
                effectiveness = "N/A";
            }
            // Вставьте данные в соответствующие ячейки таблицы
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(username));
            tableWidget->setItem(row, 1, new QTableWidgetItem(correctAttempts));
            tableWidget->setItem(row, 2, new QTableWidgetItem(incorrectAttempts));
            tableWidget->setItem(row, 3, new QTableWidgetItem(effectiveness));

            row++;
        }
    }
}

void Client::parser(QString serv_answer)
{
    QStringList data = serv_answer.split("-");
    if (data[0] == "auth"){
        get_auth(data[1], data[2]);
    }
    else if (data[0] == "reg"){
        get_reg(data[1]);
    } else if (data[0] == "get_stats") {
        fill_table(data[1]);
    }
}
