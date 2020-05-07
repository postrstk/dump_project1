#ifndef HEXPARSER_HPP
#define HEXPARSER_HPP

#include <QObject>
#include <QByteArray>
#include <QVector>
#include <QFile>
#include <QRegExp>
#include <QString>

class HexParser
{
public:
    HexParser();

    bool openHexFile(const QString& fileName);
    QString saveHexFile(const QString& fileName=".tmp.hex");
    void rewriteValue(int value_index, const QByteArray& new_value);
    void setLorawanKeys(const QByteArray& appEUI, const QByteArray& devEUI, const QByteArray& appKey);

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
