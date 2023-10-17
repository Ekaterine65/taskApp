#include "database.h"
#include <QByteArray>
#include <QDebug>
#include <QBuffer>
#include <QSqlQuery>
#include <QDataStream>
#include <vector>
#include <QSqlError>


QByteArray reg(QString username, QString password, QString loginTeacher, int type)
{
    qDebug() << username << " " << password << " " << loginTeacher << " " << type;
    QSqlDatabase& db = Database::getInstance();
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password, type, login_teacher, correct_ans, wrong_ans) VALUES (?, ?, ?, ?, 0,0)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(type);
    query.addBindValue(loginTeacher);
    if (query.exec()) {
        return QByteArray("reg-1");
    } else {
        qDebug() << query.lastError();
        return QByteArray("reg-0");
    }
}

QByteArray login(QString username, QString password)
{
    QSqlDatabase& db = Database::getInstance();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    if (query.exec() && query.next()) {
        return QByteArray("auth-1");
    } else {
        qDebug() << query.lastError();
        return QByteArray("auth-0");
    }
}



QByteArray parse(QString request)
{
   QStringList req = request.left(request.length() - 2).split(" ");

    if (req[0] == "reg") {
        return reg(req[1], req[2], req[3], req[4].toInt());
    } else if (req[0] == "auth") {
        return login(req[1], req[2]);
    } else {
        return QByteArray("0");
    }
}
