#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class ServerTCP : public QObject {
    Q_OBJECT

  public:
    explicit ServerTCP(QObject* parent = 0);
    ~ServerTCP();

    void init(const QString& address, unsigned port);


  private:
    QTcpServer*        _server;
    QList<QTcpSocket*> _sockets;

    void _processRequest(const QByteArray& data, QTcpSocket* socket);


  public slots:
    void onNewConnection();
    void onAcceptError(QAbstractSocket::SocketError serverError);
    void onSocketErrorOccurred(QAbstractSocket::SocketError socketError);
    void onSocketReadyRead();


  signals:
    void finished();
};


#endif  // SERVERTCP_H
