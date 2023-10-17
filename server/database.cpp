#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QCoreApplication>
#include <QSqlError>
QSqlDatabase& Database::getInstance()
{
    static QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QString databasePath = QCoreApplication::applicationDirPath() + "/database_file.sqlite";
    database.setDatabaseName(databasePath);

    if (!database.open()) {
        qDebug() << "Ошибка открытия базы данных!";
    } else {
        QSqlQuery query(database);
        query.exec("CREATE TABLE IF NOT EXISTS users "
                   "(username VARCHAR(64), "
                   "password VARCHAR(64), "
                   "type INTEGER, "
                   "correct_ans INTEGER, "
                   "wrong_ans INTEGER, "
                   "login_teacher VARCHAR(64), "
                   "PRIMARY KEY (username))");
        // type: 1 - преподователь, 0 - студент
    }

    return database;
}
