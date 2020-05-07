#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include "hexparser.hpp"
#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  //  QString ba("00FFFFFF");
  //  qDebug() << ba;
  //  uint tmp = ba.toUInt(nullptr, 16);
  //  qDebug() << tmp;
  //  tmp++;
  //  qDebug() << tmp;
  //  ba.setNum(tmp, 16);
  //  while (ba.size() != 8) ba = "0" + ba;
  //  qDebug() << ba.toUpper();

  MainWindow w;
  w.show();
  return a.exec();
}
