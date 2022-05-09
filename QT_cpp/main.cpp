#include "clienttcp.h"
#include "clientudp.h"
#include "servertcp.h"
#include "serverudp.h"
#include "struct_clientudp.h"

#include <QCoreApplication>


int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    bool udp            = 0;
    bool server         = 0;
    bool struct_version = 1;

    if (struct_version) {
        qDebug() << "CLIENT UDP STRUCT VERSION";
        StructClientUDP client;
        QObject::connect(&client, SIGNAL(finished()), &app, SLOT(quit()),
                         Qt::QueuedConnection);
        client.init("127.0.0.1", 2000);
        return app.exec();

    } else {
        if (udp) {
            if (server) {
                qDebug() << "SERVER UDP";
                ServerUDP server;
                QObject::connect(&server, SIGNAL(finished()), &app,
                                 SLOT(quit()), Qt::QueuedConnection);
                server.init("127.0.0.1", 2000);
                return app.exec();
            } else {
                qDebug() << "CLIENT UDP";
                ClientUDP client;
                QObject::connect(&client, SIGNAL(finished()), &app,
                                 SLOT(quit()), Qt::QueuedConnection);
                client.init("127.0.0.1", 2000);
                return app.exec();
            }

        } else {
            if (server) {
                qDebug() << "SERVER TCP";
                ServerTCP server;
                QObject::connect(&server, SIGNAL(finished()), &app,
                                 SLOT(quit()), Qt::QueuedConnection);
                server.init("127.0.0.1", 2001);
                return app.exec();
            } else {
                qDebug() << "CLIENT TCP";
                ClientTCP client;
                QObject::connect(&client, SIGNAL(finished()), &app,
                                 SLOT(quit()), Qt::QueuedConnection);
                client.init("127.0.0.1", 2001);
                return app.exec();
            }
        }
    }
}
