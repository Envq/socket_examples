#ifndef SERVERUDP_H
#define SERVERUDP_H

#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>


class ServerUDP : public QObject {
    Q_OBJECT

  public:
    explicit ServerUDP(QObject* parent = 0);
    ~ServerUDP();

    void init(const QString& address, unsigned port);


  private:
    const QHostAddress _address = QHostAddress::LocalHost;
    const unsigned     _port    = 2000;
    QUdpSocket*        _socket;

    void _processRequest(const QNetworkDatagram& request);


  public slots:
    void readyRead();


  signals:
    void finished();
};


#endif  // SERVERUDP_H
