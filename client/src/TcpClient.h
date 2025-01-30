#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QFile>
#include <QTcpSocket>
#include <QTextStream>

class TcpClient : public QObject {
  Q_OBJECT

public:
  TcpClient(const QString &host, quint16 port, const QString &filePath,
            QObject *parent = nullptr);

private slots:
  void sendFile();
  void readResponse();
  void parseResponse(QByteArray response);
  void handleSocketError(QAbstractSocket::SocketError socketError);

signals:
  void responseReady(QByteArray response);
  void sessionFinished(int);

private:
  void finish(int code = 0);

private:
  bool m_reading_header = true;
  quint32 m_response_size;

  QTcpSocket *m_socket;
  QString m_file_path;
};


#endif // TCPCLIENT_H
