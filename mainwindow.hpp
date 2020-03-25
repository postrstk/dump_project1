#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QString>


struct comand
{
    QString  a;
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
