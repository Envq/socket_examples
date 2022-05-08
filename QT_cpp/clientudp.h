#ifndef CLIENTUDP_H
#define CLIENTUDP_H

#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>


class ClientUDP : public QObject {
    Q_OBJECT

  public:
    explicit ClientUDP(QObject* parent = 0);
    ~ClientUDP();

    void init(const QString& address, unsigned port);
    void send(const QString& message);


  private:
    QUdpSocket* _socket;

    void _processReply(const QNetworkDatagram& reply);


  public slots:
    void readyRead();


  signals:
    void finished();
};


#endif  // CLIENTUDP_H
