#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <QMainWindow>
#include <QStackedWidget>
#include "singleton.h"

class Client : public QMainWindow, public Singleton <Client>
{
    Q_OBJECT

public:
    friend Singleton<Client>;

private:
    Client(QWidget* parent = nullptr);
    ~Client();


public:
    QString user_login;
    QString user_pass;

    void auth(QString login, QString password);

    void reg(QString login, QString password, bool studentOrTeacher, QString teacherLogin);

    void get_reg(QString key);

    void get_auth(QString key);

private slots:
    void parser(QString serv_answer);
};
#endif // MAINWINDOW_H
