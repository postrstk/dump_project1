#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include "hexparser.hpp"
#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  //  HexParser parser;

  //  parser.openHexFile("my_new1.hex");
  //  parser.setLorawanKeys("3333333333333333", "5555555555555555",
  //                        "77777777777777777777777777777777");
  //  parser.rewriteValue(14, "5555555555555555");

  //  qDebug() << parser.saveHexFile();

  MainWindow w;
  w.show();
  return a.exec();
}
