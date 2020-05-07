#include "hexparser.hpp"

#include <QDebug>

HexParser::HexParser() {}

bool HexParser::openHexFile(const QString &fileName) {
  QFile dataFile(fileName);
  if (!dataFile.open(QIODevice::ReadOnly)) {
    return false;
  }

  QString tmpData = dataFile.readAll();
  dataFile.close();

  QVector<QString> tmpVecData = tmpData.split(QRegExp("[\r\n]")).toVector();
  foreach (auto node, tmpVecData) {
    if (node.length() == 0) continue;
    m_hexData.push_back(node.toUtf8());
    if (node == ":020000040808EA") {
      m_valueSectionIndex = m_hexData.size() - 1;
    }
  }
  //    qDebug() << m_hexData;
}

QString HexParser::saveHexFile(const QString &fileName) {
  QFile dataFile(fileName);
  if (!dataFile.open(QIODevice::WriteOnly)) {
    return "";
  }

  foreach (auto row, m_hexData) { dataFile.write(row.toUpper() + "\r\n"); }

  dataFile.close();
  return fileName;
}

void HexParser::rewriteValue(int value_index, const QByteArray &new_value) {
  if (m_valueSectionIndex == -1) return;

  int index_to_rewrite =
      m_valueSectionIndex +
      (value_index % 4 == 0 ? value_index / 4 - 1 : value_index / 4) + 1;
  int index_place_into_str = value_index % 4 == 0 ? 3 : value_index % 4 - 1;
  index_place_into_str *= 16;
  index_place_into_str += 8;
  QByteArray work = m_hexData.at(index_to_rewrite);
  work = work.remove(index_place_into_str + 1, 16);
  work = work.insert(index_place_into_str + 1, new_value);
  m_hexData[index_to_rewrite] = work;
  resolveCRC(index_to_rewrite);
}

void HexParser::setLorawanKeys(const QByteArray &appEUI,
                               const QByteArray &devEUI,
                               const QByteArray &appKey) {
  m_appEUI = appEUI;
  m_devEUI = devEUI;
  m_appKey = appKey;
  rewriteDevEUI();
  rewriteAppEui();
  rewriteAppKey();
}

QVector<QString> HexParser::getAllValues() {
  QVector<QString> ret;

  for (int i = 1; i <= 14; i++) {
    int index_to_rewrite =
        m_valueSectionIndex + (i % 4 == 0 ? i / 4 - 1 : i / 4) + 1;
    int index_place_into_str = i % 4 == 0 ? 3 : i % 4 - 1;
    index_place_into_str *= 16;
    index_place_into_str += 8;
    QString work = m_hexData.at(index_to_rewrite);
    work = work.mid(index_place_into_str + 1, 16);
    ret.push_back(work);
  }
  return ret;
}

void HexParser::resolveCRC(int index) {
  QByteArray work = QByteArray::fromHex(m_hexData.at(index));
  work = work.remove(work.length() - 1, 1).toHex();

  char sum = 0;
  foreach (char c, work)
    sum += c;

  sum = -sum;

  work.push_front(":");
  work.push_back(QByteArray::fromRawData(&sum, 1).toHex().toUpper());
  m_hexData[index] = work;
}

void HexParser::rewriteDevEUI() {
  int index_to_rewrite = m_valueSectionIndex + 5;

  int index_place_into_str = 8;
  QByteArray work = m_hexData.at(index_to_rewrite);
  work = work.remove(index_place_into_str + 1, 16);
  work = work.insert(index_place_into_str + 1, m_devEUI);
  m_hexData[index_to_rewrite] = work;
  resolveCRC(index_to_rewrite);
}

void HexParser::rewriteAppEui() {
  int index_to_rewrite = m_valueSectionIndex + 5;

  int index_place_into_str = 24;
  QByteArray work = m_hexData.at(index_to_rewrite);
  work = work.remove(index_place_into_str + 1, 16);
  work = work.insert(index_place_into_str + 1, m_appEUI);
  m_hexData[index_to_rewrite] = work;
  resolveCRC(index_to_rewrite);
}

void HexParser::rewriteAppKey() {
  int index_to_rewrite = m_valueSectionIndex + 5;
  int index_place_into_str = 40;

  QByteArray work = m_hexData.at(index_to_rewrite);
  work = work.remove(index_place_into_str + 1, 32);
  work = work.insert(index_place_into_str + 1, m_appKey);
  m_hexData[index_to_rewrite] = work;
  resolveCRC(index_to_rewrite);
}
