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
    QUdpSocket* _socket;

    void _processRequest(const QNetworkDatagram& request);


  public slots:
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onReadyRead();


  signals:
    void finished();
};


#endif  // SERVERUDP_H
