#include "clienttcp.h"

#include <QDebug>
#include <iostream>


ClientTCP::ClientTCP(QObject* parent) : QObject(parent) {
    _socket = new QTcpSocket(this);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this,
            SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
}


ClientTCP::~ClientTCP() {
    qDebug() << "delete ClientTCP";
    _socket->close();
    delete _socket;
}


void ClientTCP::init(const QString& address, unsigned port) {
    _socket->connectToHost(address, port);
    if (!_socket->waitForConnected(500)) {
        qCritical() << "connectToHost error:" + _socket->errorString();
        emit finished();
    } else {
        qDebug().nospace() << "Selected: -> " << address.toStdString().c_str()
                           << ":" << port;
    }
    send("start");
}


void ClientTCP::send(const QString& message) {
    _socket->write(message.toUtf8());
    if (!_socket->waitForBytesWritten()) {
        qWarning() << "Error in sending this request: " << message;
    }
    if (message == "close") {
        emit finished();
    }
}


void ClientTCP::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    qCritical() << "errorOccurred" << socketError;
    emit finished();
}


void ClientTCP::onReadyRead() {
    // all message arrived before this function is finished will be executed
    // immediately without waiting for a new call to this function
    while (!_socket->atEnd()) {
        auto data = _socket->read(1024);
        _processReply(data);
    }
}


void ClientTCP::_processReply(const QByteArray& data) {
    // process reply
    QString message(data);
    qDebug() << ">" << message;
    // get new message to send
    std::string line;
    std::cout << "Send: ";
    std::cin >> line;
    send(QString(line.c_str()));
}
