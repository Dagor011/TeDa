#include "server.h"
#include <QHostAddress>
#include <QRandomGenerator>
#include <QDebug>
#include<QThread>
Server::Server(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);

    // Попытка привязать сервер к случайному порту
    for (int i = 0; i < 10; i++) {
        randomPort = QRandomGenerator::global()->bounded(1024, 65535);
        if (server->listen(QHostAddress::Any, randomPort)) {
            qDebug() << "Server started on port:" << server->serverPort();
            break;
        } else {
            qDebug() << "Failed to bind to port:" << randomPort;
            QThread::msleep(100);
        }
    }

    if (!server->isListening()) {
        qDebug() << "Failed to start server";
        return;
    }

    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

Server::~Server() {
    server->close();
}

void Server::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clients.append(clientSocket);

    qDebug() << "New client connected";

    // Отправка случайного порта клиенту
    QByteArray data = QString::number(randomPort).toUtf8();
    clientSocket->write(data);

    // Обработка нового соединения
    // ...
}

void Server::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received data: " << data;

        // Отправка сообщения всем клиентам
        for (QTcpSocket *socket : clients) {
            if (socket != clientSocket) {
                socket->write(data);
            }
        }
    }
}
