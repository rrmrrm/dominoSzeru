#include <QCoreApplication>

#include "ChatServer.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    ChatServer *server = new ChatServer();
    // Will call incomingConnection() on new client connections.
    bool success = server->listen(QHostAddress::Any, 4200);
    if(!success)
    {
        qFatal("Could not listen on port 4200.");
    }

    qDebug() << "Ready";

    return app.exec();
}
