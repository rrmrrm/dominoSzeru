#ifndef SERVER_H
#define SERVER_H


#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>

class server : public QTcpServer
{
    Q_OBJECT

    public:
        server(QObject* parent = nullptr)
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


#endif // SERVER_H
