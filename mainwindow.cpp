#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->button_connect, &QPushButton::clicked, this, &MainWindow::slotConnect);
  connect(ui->button_read, &QPushButton::clicked, this, &MainWindow::slotRead);
  connect(ui->button_write, &QPushButton::clicked, this, &MainWindow::slotWrite);
  for(int i = 0; i < 14; ++i) {
    this->outputs.push_back(ui->centralwidget->findChild<QLabel*>("output_"+QString::number(i)));
    this->inputs.push_back(ui->centralwidget->findChild<QLineEdit*>("input_"+QString::number(i)));
    connect(this->inputs.at(i), &QLineEdit::textChanged, [=](const QString& text){
      if (text.isEmpty()) {
        inputs.at(i)->setStyleSheet("QLineEdit{border:1px solid #ff1c1c}");
      }
      else {
        inputs.at(i)->setStyleSheet("QLineEdit{border:1px solid #757575}");
      }
    });
    emit this->inputs.at(i)->textChanged("");
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slotRead()
{
  // Read some data and write into outputs
}

void MainWindow::slotWrite()
{
  // Write data from inputs
}

void MainWindow::slotConnect()
{
    qDebug() << getCorrectDataFromHex("my_new1.hex");
}

double MainWindow::hex2double(const std::string &hex)
{
    union
    {
        long long i;
        double  d;
    } value;

    value.i = std::stoll(hex,nullptr,16);
    return value.d;
}

std::string MainWindow::double2hex(double d)
{
    union
    {
        long long i;
        double    d;
    } value;

   value.d = d;

   char buf[17];

   snprintf (buf,sizeof(buf),"%016llx",value.i);
   buf[16]=0; //make sure it is null terminated.

   return std::string(buf);
}

QString MainWindow::dataFromInput(const int index)
{
  return this->inputs.at(index)->text();
}

void MainWindow::setDataToOutput(const int index, const QString &data)
{
  this->outputs.at(index)->setText(data);
}


QString MainWindow::getCorrectDataFromHex(const QString &filename)
{
  QString ret = "";
  QString rawData = "";
  QStringList fileData;

  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly)) {
    return ret;
  }
  while(!file.atEnd()) {
    fileData << file.readLine();
  }

  file.close();

  if (fileData.length() != 3) {
    return ret;
  }

  rawData = fileData.at(1);
  rawData = rawData.remove(0, 9);
  rawData = rawData.remove(rawData.length() - 3, 3);

  for(int i = 0; i < rawData.length()-1; i+=2) {
    ret.push_front(rawData.at(i+1));
    ret.push_front(rawData.at(i));
  }

  return ret;
}
