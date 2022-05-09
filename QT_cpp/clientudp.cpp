#include "clientudp.h"

#include <QDebug>
#include <iostream>


ClientUDP::ClientUDP(QObject* parent) : QObject(parent) {
    _socket = new QUdpSocket(this);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this,
            SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
}


ClientUDP::~ClientUDP() {
    qDebug() << "delete ClientUDP";
    _socket->close();
    delete _socket;
}


void ClientUDP::init(const QString& address, unsigned port) {
    // This is a convenient way to make the socket remember the address and port
    // and then use write instead of writeDatagram
    _socket->connectToHost(address, port);
    qDebug().nospace() << "Selected: -> " << address.toStdString().c_str()
                       << ":" << port;
    send("start");
}


void ClientUDP::send(const QString& message) {
    _socket->write(message.toUtf8());
    // Note: QUdpSocket sends data immediately, so there's no need to use
    // waitForBytesWritten
    if (message == "close") {
        emit finished();
    }
}


void ClientUDP::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    qCritical() << "errorOccurred" << socketError;
    emit finished();
}


void ClientUDP::onReadyRead() {
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
    // get new message to send
    std::string line;
    std::cout << "Send: ";
    std::cin >> line;
    send(QString(line.c_str()));
}
