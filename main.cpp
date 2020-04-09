#include "mainwindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QDateTime>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QDateTime dt;
  QString key;
  key = QString::number(dt.currentDateTime().toMSecsSinceEpoch()) + QString::number(dt.currentDateTime().toMSecsSinceEpoch());
  qDebug() << key;

  MainWindow w;
//  w.show();
  return a.exec();
}
