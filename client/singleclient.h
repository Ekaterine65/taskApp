#ifndef SINGLECLIENT_H
#define SINGLECLIENT_H

#include <QString>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>
#include <QObject>

#include "singleton.h"

class SingletonClient : public QObject, public Singleton<SingletonClient>
{
    friend class Singleton<SingletonClient>;
    Q_OBJECT
private:
    QTcpSocket* socket;
    SingletonClient();
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;

public:
    bool sendToServer(QString);
    ~SingletonClient();

private slots:
    void slot_readFromServer();

signals:
    void serverAnswer(QString);

};

#endif // SINGLECLIENT_H
