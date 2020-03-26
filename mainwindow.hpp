#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QString>


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
  double hex2double(const std::string& hex);
  std::string double2hex(double d);
public:
    QString getCorrectDataFromHex(const QString& filename);

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
