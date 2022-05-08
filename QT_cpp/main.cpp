#include "clientudp.h"
#include "serverudp.h"

#include <QCoreApplication>


int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    bool heap = 0;
    if (heap) {
        qDebug() << "heap allocation";
        auto server = new ServerUDP();
        QObject::connect(server, SIGNAL(finished()), server,
                         SLOT(deleteLater()));
        QObject::connect(server, SIGNAL(finished()), &app, SLOT(quit()),
                         Qt::QueuedConnection);
        server->init("127.0.0.1", 2000);
        return app.exec();

    } else {
        qDebug() << "stack allocation";
        ServerUDP server;
        QObject::connect(&server, SIGNAL(finished()), &app, SLOT(quit()),
                         Qt::QueuedConnection);
        server.init("127.0.0.1", 2000);
        return app.exec();
    }
}
