#include "keylogger.hpp"

KeyLogger::KeyLogger(const QString &filename, QObject *parent)
    : QObject(parent) {
  m_file.setFileName(filename);
}

bool KeyLogger::write(const QStringList &data) {
  if (!open())
    return false;

  QString tmpData = data.join(",") + "\n";
  m_file.write(tmpData.toUtf8());

  return close();
}

bool KeyLogger::open() {
  if (m_file.open(QIODevice::Append))
    return true;
  return false;
}

bool KeyLogger::close() {
  m_file.close();
  return true;
}
