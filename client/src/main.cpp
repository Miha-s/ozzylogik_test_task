#include <QCoreApplication>
#include "TcpClient.h"
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  if (argc < 4) {
    qWarning() << "Usage: " << argv[0] << " <host> <port> <file>";
    return 1;
  }

  QString host = argv[1];
  quint16 port = QString(argv[2]).toUShort();
  QString filePath = argv[3];

  TcpClient client(host, port, filePath);

  QObject::connect(&client, &TcpClient::sessionFinished,
                   [&app]() { app.quit(); });

  return app.exec();
}
