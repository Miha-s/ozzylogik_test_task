#include "TcpClient.h"
#include <QCoreApplication>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

TcpClient::TcpClient(const QString &host, quint16 port, const QString &filePath,
                     QObject *parent)
    : QObject(parent), m_socket(new QTcpSocket(this)), m_file_path(filePath) {
  m_socket->connectToHost(host, port);
  m_socket->setParent(this);

  connect(m_socket, &QTcpSocket::connected, this, &TcpClient::sendFile);
  connect(m_socket, &QTcpSocket::errorOccurred, this, &TcpClient::handleSocketError);
  connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::readResponse);
  connect(this, &TcpClient::responseReady, this, &TcpClient::parseResponse);
}

void TcpClient::sendFile() {
  QFile file(m_file_path);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Failed to open file:" << m_file_path;
    finish(1);
    return;
  }

  QByteArray fileData = file.readAll();
  file.close();

  quint32 size = fileData.size();

  QByteArray sizePrefix;
  QDataStream sizeStream(&sizePrefix, QIODevice::WriteOnly);
  sizeStream.setByteOrder(QDataStream::BigEndian);
  sizeStream << size;

  m_socket->write(sizePrefix);
  m_socket->write(fileData);
  m_socket->flush();
}

void TcpClient::readResponse() {
  if (m_reading_header) {
    if (m_socket->bytesAvailable() < sizeof(quint32)) {
      // Not enough data to read the size yet, return and wait for more data
      return;
    }

    QDataStream sizeStream(m_socket);

    sizeStream.setByteOrder(QDataStream::BigEndian);
    sizeStream >> m_response_size;
    m_reading_header = false;
  }

  QByteArray response = m_socket->read(m_socket->bytesAvailable());
  if (response.size() != m_response_size) {
    // not finished reading file
    return;
  }
  emit responseReady(response);

  m_reading_header = true;
}

void TcpClient::parseResponse(QByteArray response) {
  QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

  if (!jsonResponse.isObject()) {
    qDebug() << "Invalid JSON format! Expected a JSON object.";
    finish(1);
    return;
  }

  QJsonObject responseObject = jsonResponse.object();

  if (responseObject.contains("words_count") &&
      responseObject["words_count"].isDouble()) {
    qDebug() << "words_count: " << responseObject["words_count"].toDouble();
  }

  if (responseObject.contains("unique_words_count") &&
      responseObject["unique_words_count"].isDouble()) {
    qDebug() << "unique_words_count: "
             << responseObject["unique_words_count"].toDouble();
  }

  if (responseObject.contains("longest_unique_words_sequence") &&
      responseObject["longest_unique_words_sequence"].isDouble()) {
    qDebug() << "longest_unique_words_sequence: "
             << responseObject["longest_unique_words_sequence"].toDouble();
  }

  finish();
}

void TcpClient::handleSocketError(QAbstractSocket::SocketError socketError) {
  qDebug() << "Socket Error:" << m_socket->errorString();
  finish(1);
}

void TcpClient::finish(int code) {
  if (m_socket->isOpen())
    m_socket->close();
  emit sessionFinished(code);
}
