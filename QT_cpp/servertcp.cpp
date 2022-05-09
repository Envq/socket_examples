#include "servertcp.h"

#include <QDebug>


ServerTCP::ServerTCP(QObject* parent) : QObject(parent) {
    _server = new QTcpServer(this);
    connect(_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(_server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this,
            SLOT(onAcceptError(QAbstractSocket::SocketError)));
}


ServerTCP::~ServerTCP() {
    qDebug() << "delete ServerTCP";
    foreach (auto socket, _sockets) {
        //        qDebug() << "close: [" << socket->peerAddress().toString() <<
        //        ":"
        //                 << socket->peerPort() << "]";
        socket->close();
        delete socket;
    }
    _server->close();
    delete _server;
}


void ServerTCP::init(const QString& address, unsigned port) {
    bool success = _server->listen(QHostAddress(address), port);
    if (!success) {
        qWarning().nospace()
            << "Can't bind on: " << address.toStdString().c_str() << ":"
            << port;
        emit finished();
    } else {
        qDebug().nospace() << "Selected: -> " << address.toStdString().c_str()
                           << ":" << port;
    }
}


void ServerTCP::onNewConnection() {
    while (_server->hasPendingConnections()) {
        auto socket = _server->nextPendingConnection();
        _sockets.append(socket);
        connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
        connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
                this,
                SLOT(onSocketErrorOccurred(QAbstractSocket::SocketError)));
    }
}


void ServerTCP::onAcceptError(QAbstractSocket::SocketError serverError) {
    qCritical() << "acceptError" << serverError;
    emit finished();
}


void ServerTCP::onSocketErrorOccurred(
    QAbstractSocket::SocketError socketError) {
    auto socket = static_cast<QTcpSocket*>(QObject::sender());
    qCritical() << "[" << socket->peerAddress().toString() << ":"
                << socket->peerPort() << "] errorOccurred" << socketError;
    emit finished();
}


void ServerTCP::onSocketReadyRead() {
    auto socket = static_cast<QTcpSocket*>(sender());
    // all message arrived before this function is finished will be executed
    // immediately without waiting for a new call to this function
    while (!socket->atEnd()) {
        auto data = socket->read(1024);
        _processRequest(data, socket);
    }
}


void ServerTCP::_processRequest(const QByteArray& data, QTcpSocket* socket) {
    // process request
    QString message(data);
    qDebug().nospace() << "[" << socket->peerAddress().toString() << ":"
                       << socket->peerPort() << "]: " << message;
    if (message == "close") {
        emit finished();
    } else {
        // send reply
        socket->write(message.toUtf8());
        if (!socket->waitForBytesWritten()) {
            qWarning() << "Error in sending this reply: " << message;
        }
    }
}
