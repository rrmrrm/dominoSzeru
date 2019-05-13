#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>

class ChatServer : public QTcpServer
{
    Q_OBJECT

    public:
        ChatServer(QObject* parent = nullptr)
        {}

    private slots:
        void readyRead();
        void disconnected();
        void sendUserList();

    protected:
        void incomingConnection(int socketfd);

    private:
        QSet<QTcpSocket*> clients;
        QMap<QTcpSocket*, QString> users;
};

#endif // CHATSERVER_H
