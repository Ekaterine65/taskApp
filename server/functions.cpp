#include "database.h"
#include <QByteArray>
#include <QDebug>
#include <QBuffer>
#include <QSqlQuery>
#include <QDataStream>
#include <vector>
#include <QSqlError>

std::string is_it_a_teacher(QString username);

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
        return QByteArray("reg-1\n");
    } else {
        qDebug() << query.lastError();
        return QByteArray("reg-0\n");
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
        std::string s = "auth-1-" + is_it_a_teacher(username) + "\n";
        return QByteArray::fromStdString(s);
    } else {
        qDebug() << query.lastError();
        return QByteArray("auth-0-0\n");
    }
}

QByteArray get_answer(QString username, QString password, QString is_it_correct)
{
    QSqlDatabase& db = Database::getInstance();
    QSqlQuery query(db);
    if (is_it_correct == "1") {
        query.prepare("UPDATE users SET correct_ans = correct_ans + 1 WHERE username = ? and password = ?");
    } else {
        query.prepare("UPDATE users SET wrong_ans = wrong_ans + 1 WHERE username = ? and password = ?");
    }
    query.addBindValue(username);
    query.addBindValue(password);
    if (query.exec() && query.next()) {
        return QByteArray("answer-1\n");
    } else {
        qDebug() << query.lastError();
        return QByteArray("answer-0\n");
    }
}

std::string is_it_a_teacher(QString username) {
    QSqlDatabase& db = Database::getInstance();
    QSqlQuery query(db);
    query.prepare("SELECT type FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    query.next();
    if (query.value("type").toInt() == 1) {
        return "1";
    } else {
        return "0";
    }
}

QByteArray get_stats(QString username) {
    QSqlDatabase& db = Database::getInstance();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE login_teacher = ?");
    query.addBindValue(username);
    if (!query.exec()) {
        qDebug() << query.lastError();
    }
    QString ans = "get_stats-";
    while (query.next()) {
        ans += query.value("username").toString() + " " + query.value("correct_ans").toString() + " " + query.value("wrong_ans").toString() + "$";
    }
    if (ans[ans.size()-1] == '$') {
        ans.chop(1);
    }
    ans += "\n";
    return QByteArray(ans.toUtf8());
}


QByteArray parse(QString request)
{
    QStringList req = request.trimmed().split(" ");

    for (auto now : req) {
        qDebug() << now << "\n";
    }
    if (req[0] == "reg") {
        return reg(req[1], req[2], req[3], req[4].toInt());
    } else if (req[0] == "auth") {
        return login(req[1], req[2]);
    } else if (req[0] == "answer") {
        return get_answer(req[1],req[2],req[3]);
    } else if (req[0] == "get_stats") {
        return get_stats(req[1]);
    } else {
        return QByteArray("0");
}
}
