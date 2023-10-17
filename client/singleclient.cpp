#include "singleclient.h"

SingletonClient::~SingletonClient()
{
    socket->close();
}

SingletonClient::SingletonClient()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 33333);
    connect(socket, &QTcpSocket::readyRead, this, &SingletonClient::slot_readFromServer);
    qDebug() << "Клиент запущен";
    qDebug() << "Состояние сокета: " << socket->isOpen();
}

void SingletonClient::slot_readFromServer()
{
    QString data;
    QStringList datas;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readAll());
    }
    qDebug() << "Данные с сервера: " << data << '\n';
    if (data.size() > 0) {
        datas = data.split("\n");
        for (int i = 0; i < datas.size(); i++) {
            emit this->serverAnswer(datas[i]);
        }
    }
}

bool SingletonClient::sendToServer(QString answer)
{
    socket->write((answer+QString("\n")).toUtf8());
    return 0;
}
