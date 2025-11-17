#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QList>
#include <QTcpSocket>

class Server : public QObject {
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QList<QTcpSocket*> clients;
    quint16 randomPort;
};

#endif // SERVER_H
