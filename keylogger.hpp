#ifndef KEYLOGGER_HPP
#define KEYLOGGER_HPP

#include <QObject>
#include <QStringList>
#include <QFile>

class KeyLogger : public QObject
{
    Q_OBJECT
public:
    explicit KeyLogger(const QString& filename, QObject *parent = nullptr);
    bool write(const QStringList& data );
private:
    bool open();
    bool close();
signals:
private:
    QFile m_file;
};

#endif // KEYLOGGER_HPP
