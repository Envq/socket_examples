#include "struct_clientudp.h"

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <iostream>


StructClientUDP::StructClientUDP(QObject* parent) : QObject(parent) {
    _socket = new QUdpSocket(this);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this,
            SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
}


StructClientUDP::~StructClientUDP() {
    qDebug() << "delete StructClientUDP";
    _socket->close();
    delete _socket;
}


void StructClientUDP::init(const QString& address, unsigned port) {
    // This is a convenient way to make the socket remember the address and port
    // and then use write instead of writeDatagram
    _socket->connectToHost(address, port);
    qDebug().nospace() << "Selected: -> " << address.toStdString().c_str()
                       << ":" << port;
    send({0, 130});
}


void StructClientUDP::send(const RequestData& request) {
    QByteArray  buffer;
    QDataStream s(&buffer, QIODevice::WriteOnly);
    s << request.a << request.b;

    _socket->write(buffer);
    if (request.a == 42) {
        emit finished();
    }
}


void StructClientUDP::onErrorOccurred(
    QAbstractSocket::SocketError socketError) {
    qCritical() << "errorOccurred" << socketError;
    emit finished();
}


void StructClientUDP::onReadyRead() {
    // all datagrams arrived before this function is finished will be executed
    // immediately without waiting for a new call to this function
    while (_socket->hasPendingDatagrams()) {
        QNetworkDatagram reply = _socket->receiveDatagram();
        _processReply(reply);
    }
}


void StructClientUDP::_processReply(const QNetworkDatagram& reply) {
    // get reply
    QByteArray rawdata = reply.data();
    // process reply
    ReplyData* d = reinterpret_cast<ReplyData*>(rawdata.data());
    qDebug() << ">" << d->f0 << d->f1 << d->f2 << d->f3 << d->f4 << d->f5;
    // get new message to send
    std::string line;
    std::cout << "Send: ";
    std::cin >> line;
    send({std::stoi(line), 130});
}
