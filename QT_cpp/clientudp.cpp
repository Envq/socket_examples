#include "clientudp.h"

#include <QDebug>


ClientUDP::ClientUDP(QObject* parent) : QObject(parent) {
    _socket = new QUdpSocket(this);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


ClientUDP::~ClientUDP() {
    qDebug() << "delete ClientUDP";
    _socket->close();
    delete _socket;
}


void ClientUDP::init(const QString& address, unsigned port) {
    // Try to connect to Server
    _socket->connectToHost(address, port);
    if (!_socket->waitForConnected(500)) {
        qWarning().nospace()
            << "Can't connect on: " << address.toStdString().c_str() << ":"
            << port;
        emit finished();
    }
}


void ClientUDP::send(const QString& message) {
    _socket->write(message.toUtf8());
    if (!_socket->waitForBytesWritten()) {
        qWarning() << "Error in sending:" << message;
    }
    if (message == "close") {
        emit finished();
    }
}


void ClientUDP::readyRead() {
    // all datagrams arrived before this function is finished will be executed
    // immediately without waiting for a new call to this function
    while (_socket->hasPendingDatagrams()) {
        QNetworkDatagram reply = _socket->receiveDatagram();
        _processReply(reply);
    }
}


void ClientUDP::_processReply(const QNetworkDatagram& reply) {
    // get reply
    QByteArray data = reply.data();
    // process reply
    QString message(data);
    qDebug() << ">" << message;
}
