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
    QString addr1 = "1.hex";
    QString addr2 = "2.hex";
    QString addr3 = "3.hex";
    QString addr4 = "4.hex";
    QString addr5 = "5.hex";
    QString addr6 = "6.hex";
    QString addr7 = "7.hex";
    QString addr8 = "8.hex";
    QString addr9 = "9.hex";
    QString addr10 = "10.hex";
    QString addr11 = "11.hex";
    QString addr12 = "12.hex";
    QString addr13 = "13.hex";
    QString addr14 = "14.hex";
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
    QString addr3 = "0x08080116";
    QString addr4 = "0x08080124";
    QString addr5 = "0x08080132";
    QString addr6 = "0x08080140";
    QString addr7 = "0x08080148";
    QString addr8 = "0x08080156";
    QString addr9 = "0x08080164";
    QString addr10 = "0x08080172";
    QString addr11 = "0x08080180";
    QString addr12 = "0x08080188";
    QString addr13 = "0x08080196";
    QString addr14 = "0x08080204";
};


struct addrSec
{
    QString addr1 = "0x08080104";
    QString addr2 = "0x08080112";
    QString addr3 = "0x08080120";
    QString addr4 = "0x08080128";
    QString addr5 = "0x08080136";
    QString addr6 = "0x08080144";
    QString addr7 = "0x08080152";
    QString addr8 = "0x08080160";
    QString addr9 = "0x08080168";
    QString addr10 = "0x08080176";
    QString addr11 = "0x08080184";
    QString addr12 = "0x08080192";
    QString addr13 = "0x08080200";
    QString addr14 = "0x08080208";
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
  double hex2double(const std::string& hex);
  std::string double2hex(double d);
  void readData();
  void writeData(int num, double data);
  bool testConnect();
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
};
#endif // MAINWINDOW_HPP
