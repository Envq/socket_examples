#include "serverudp.h"

#include <QDebug>


ServerUDP::ServerUDP(QObject* parent) : QObject(parent) {
    _socket = new QUdpSocket(this);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this,
            SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
}


ServerUDP::~ServerUDP() {
    qDebug() << "delete ServerUDP";
    _socket->close();
    delete _socket;
}


void ServerUDP::init(const QString& address, unsigned port) {
    bool success = _socket->bind(QHostAddress(address), port);
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


void ServerUDP::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    qCritical() << "onErrorOccurred" << socketError;
    emit finished();
}


void ServerUDP::onReadyRead() {
    // all datagrams arrived before this function is finished will be executed
    // immediately without waiting for a new call to this function
    while (_socket->hasPendingDatagrams()) {
        QNetworkDatagram request = _socket->receiveDatagram();
        _processRequest(request);
    }
}


void ServerUDP::_processRequest(const QNetworkDatagram& request) {
    // get request and address
    auto clientAddr = request.senderAddress().toString().toStdString().c_str();
    int  clientPort = request.senderPort();
    QByteArray data = request.data();
    // process request
    QString message(data);
    qDebug().nospace() << "[" << clientAddr << ":" << clientPort
                       << "]: " << message;
    if (message == "close") {
        emit finished();
    } else {
        // send reply
        _socket->writeDatagram(request.makeReply(data));
    }
}
