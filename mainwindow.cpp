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
