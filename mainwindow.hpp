#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QList>
#include <QLabel>
#include <QLineEdit>

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
  
private:
  QString dataFromInput(const int index);
  void setDataToOutput(const int index, const QString& data);
  
public:
    QString getCorrectDataFromHex(const QString& filename);

private:
  QList<QLabel*> outputs;
  QList<QLineEdit*> inputs;
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
