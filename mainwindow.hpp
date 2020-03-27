#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>

struct nameFile
{
  QList<QString> addr{
  "1.hex", "2.hex", "3.hex", "4.hex",
  "5.hex", "6.hex", "7.hex", "8.hex",
  "9.hex", "10.hex", "11.hex", "12.hex",
  "13.hex", "14.hex"
  };
};

struct addrRead
{
    QString addr1 = "0x08080100";
    QString addr2 = "0x08080108";
    QString addr3 = "0x08080110";
    QString addr4 = "0x08080118";
    QString addr5 = "0x08080120";
    QString addr6 = "0x08080128";
    QString addr7 = "0x08080130";
    QString addr8 = "0x08080138";
    QString addr9 = "0x08080140";
    QString addr10 = "0x08080148";
    QString addr11 = "0x08080150";
    QString addr12 = "0x08080158";
    QString addr13 = "0x08080160";
    QString addr14 = "0x08080168";
};

struct addr
{
    QString addr1 = "0x08080100";
    QString addr2 = "0x08080108";
    QString addr3 = "0x08080110";
    QString addr4 = "0x08080118";
    QString addr5 = "0x08080120";
    QString addr6 = "0x08080128";
    QString addr7 = "0x08080130";
    QString addr8 = "0x08080138";
    QString addr9 = "0x08080140";
    QString addr10 = "0x08080148";
    QString addr11 = "0x08080150";
    QString addr12 = "0x08080158";
    QString addr13 = "0x08080160";
    QString addr14 = "0x08080168";
};


struct addrSec
{
    QString addr1 = "0x08080104";
    QString addr2 = "0x0808010с";
    QString addr3 = "0x08080114";
    QString addr4 = "0x0808011с";
    QString addr5 = "0x08080124";
    QString addr6 = "0x0808012с";
    QString addr7 = "0x08080134";
    QString addr8 = "0x0808013с";
    QString addr9 = "0x08080144";
    QString addr10 = "0x0808014с";
    QString addr11 = "0x08080154";
    QString addr12 = "0x0808015с";
    QString addr13 = "0x08080164";
    QString addr14 = "0x0808016с";
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void slotRead();
  void slotWrite();
  void slotConnect();

  
private:
  QString dataFromInput(const int index);
  void setDataToOutput(const int index, const QString& data);
  void setDataToInput(const int index, const QString& data);
  double hex2double(const std::string& hex);
  std::string double2hex(double d);
  void readData();
  void writeData(int num, double data);
  bool testConnect();
  bool checkSTMConnect(const QStringList& list);
  bool checkSTMConnect(const QString& filename);

public:
    QString getCorrectDataFromHex(const QString& filename);

private:
  QList<QLabel*> outputs;
  QList<QLineEdit*> inputs;
  Ui::MainWindow *ui;
  QProcess *process;
  addr adr1;
  addrSec adr2;
  addrRead addrRead;
  nameFile nameF;
  bool isConnect{false};

};
#endif // MAINWINDOW_HPP
