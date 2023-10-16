#include "client.h"
#include "singleclient.h"
#include <QMessageBox>

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

void Client::get_auth(QString key) {
    if (key == "1") {
        QMessageBox::information(this, "Успешная авторизация", "Вы успешно авторизированы.");
    } else {
        QMessageBox::critical(this, "Ошибка авторизации", "Авторизация не удалась. Пожалуйста, попробуйте ещё раз.");
    }
}

void Client::get_reg(QString key) {
    if (key == "1") {
        QMessageBox::information(this, "Успешная регистрация", "Вы успешно зарегистрированы.");
    } else {
        QMessageBox::critical(this, "Ошибка регистрации", "Регистрация не удалась. Пожалуйста, попробуйте ещё раз.");
    }
}

void Client::parser(QString serv_answer)
{
    QStringList data = serv_answer.split("-");
    if (data[0] == "auth")
        get_auth(data[1]);
    else if (data[0] == "reg")
        get_reg(data[1]);
}
