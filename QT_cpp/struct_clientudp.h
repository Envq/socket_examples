#ifndef STRUCTCLIENTUDP
#define STRUCTCLIENTUDP

#include <QAbstractSocket>
#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>


struct RequestData {
    quint32 a;
    quint32 b;
};

struct ReplyData {
    qint32 f0;
    qint32 f1;
    qint32 f2;
    qint32 f3;
    qint32 f4;
    qint32 f5;
};


class StructClientUDP : public QObject {
    Q_OBJECT

  public:
    explicit StructClientUDP(QObject* parent = 0);
    ~StructClientUDP();

    void init(const QString& address, unsigned port);
    void send(const RequestData& request);


  private:
    QUdpSocket* _socket;

    void _processReply(const QNetworkDatagram& reply);


  public slots:
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onReadyRead();


  signals:
    void finished();
};


#endif  // STRUCTCLIENTUDP
