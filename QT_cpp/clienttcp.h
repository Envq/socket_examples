#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>
#include <QTcpSocket>


class ClientTCP : public QObject {
    Q_OBJECT

  public:
    explicit ClientTCP(QObject* parent = 0);
    ~ClientTCP();

    void init(const QString& address, unsigned port);
    void send(const QString& message);


  private:
    QTcpSocket* _socket;

    void _processReply(const QByteArray& data);


  public slots:
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onReadyRead();


  signals:
    void finished();
};


#endif  // CLIENTTCP_H
