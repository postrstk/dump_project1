#ifndef HEXPARSER_HPP
#define HEXPARSER_HPP

#include <QByteArray>
#include <QFile>
#include <QObject>
#include <QRegExp>
#include <QString>
#include <QVector>

class HexParser {
public:
  HexParser();

  bool openHexFile(const QString &fileName);
  QString saveHexFile(const QString &fileName = ".tmp.hex");
  void rewriteValue(int value_index, const QByteArray &new_value);
  void setLorawanKeys(const QByteArray &appEUI, const QByteArray &devEUI,
                      const QByteArray &appKey);
  QVector<QString> getAllValues();

private:
  void resolveCRC(int index);
  void rewriteDevEUI();
  void rewriteAppEui();
  void rewriteAppKey();

private:
  QVector<QByteArray> m_hexData;
  QByteArray m_appKey;
  QByteArray m_devEUI;
  QByteArray m_appEUI;
  int m_valueSectionIndex;
};

#endif // HEXPARSER_HPP
