
#ifndef __PROXY_H_
#define __PROXY_H_

#include <QtNetwork>


class CProxy: protected QTcpServer
{
    Q_OBJECT
public:
    CProxy( QObject * parent = 0, const QString & listenHost = QString(), 
                                  quint16 listenPort = 26001, 
                                  const QString & connectHost = "10.8.0.2", 
                                  quint16 connectPort = 26001 );
    ~CProxy();

    bool isListening() const;
    void deleteLater();
private slots:
    void slotNewConnection();
    void slotDisconnected();
    void slotHostDataAvailable();
    void slotClientDataAvailable();
private:
    void removePair( QTcpSocket * s );

    QHash<QTcpSocket*, QTcpSocket*> m_hostKey;
    QHash<QTcpSocket*, QTcpSocket*> m_clientKey;
    QString m_clientHost;
    quint16 m_clientPort;
    QByteArray m_buffer;
};



#endif

