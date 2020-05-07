#include "mainwindow.hpp"

#include <QDebug>
#include <QRegularExpression>
#include <iostream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->button_load_file, &QPushButton::clicked, this,
          &MainWindow::slotLoadFile);
  connect(ui->button_connect, &QPushButton::clicked, this,
          &MainWindow::slotConnect);
  connect(ui->button_write, &QPushButton::clicked, this,
          &MainWindow::slotWrite);

  //  ui->button_connect->setEnabled(this->isConnect);
  ui->button_write->setEnabled(this->isConnect);

  for (int i = 0; i < 14; ++i) {
    this->cbInputs.push_back(ui->centralwidget->findChild<QCheckBox *>(
        "checkBox_" + QString::number(i)));
    this->inputs.push_back(ui->centralwidget->findChild<QLineEdit *>(
        "input_" + QString::number(i)));

    inputs.at(i)->setEnabled(false);
    inputs.at(i)->setStyleSheet(
        "QLineEdit{border:1px solid #757575; background-color: #F0F0F0 } ");

    connect(this->cbInputs.at(i), &QCheckBox::clicked, [=](bool checked) {
      if (checked) {
        inputs.at(i)->setStyleSheet(
            "QLineEdit{border:1px solid #1c1cff; background-color: #FFFFFF } ");
      } else {
        inputs.at(i)->setStyleSheet(
            "QLineEdit{border:1px solid #757575; background-color: #F0F0F0 } ");
      }
      inputs.at(i)->setEnabled(checked);
    });
  }
  qDebug() << this->getAppKey();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::slotRead() {
  readData();

  for (int i = 0; i < this->nameF.addr.size(); ++i) {
    QString tmp = getCorrectDataFromHex(this->nameF.addr[i]);
    qDebug() << tmp;
    double f = hex2double(tmp.toStdString());
    //    setDataToOutput(i, QString::number(f));
    setDataToInput(i, QString::number(f));
  }
}

void MainWindow::slotWrite() {
  // Re-Write values if needed
  for (int i = 0; i < cbInputs.size(); ++i) {
    if (cbInputs.at(i)->isChecked()) {
      QString new_value = inputs.at(i)->text();
      if (new_value.length() > 16) continue;  // error
      while (new_value.length() != 16) new_value = "0" + new_value;
      m_parser.rewriteValue(i + 1, new_value.toUtf8());
    }
  }

  // Set new LORAWAN keys
  QString appEUI = getAppEui();
  QString devEUI = getDevEui();
  QString appKey = getAppKey();
  m_parser.setLorawanKeys(appEUI.toUtf8(), devEUI.toUtf8(), appKey.toUtf8());

  // hexFile - temp file with code to device
  QString hexFile = m_parser.saveHexFile();

  if (hexFile.size() == 0) return;

  //  process = new QProcess(this);

  //  process->start("cmd.exe",
  //                 QStringList()
  //                     << "/c ST-LINK_CLI.exe -c UR -P 88.hex 0x08080100");
  //  if (process->waitForFinished())
  //    qDebug() << "read";

  //  process->waitForFinished(-1);
  //  qDebug() << "Finish read ";

  // write keys for future QR code build
  m_logger.write(QStringList() << appEUI << devEUI << appKey);
  incrementDevEui();
}

void MainWindow::slotConnect() {
  //  testConnect();
  //  bool shit = checkSTMConnect("conection.txt");
  //  if (!shit)
  //    return;

  this->isConnect = true;
  //  ui->button_read->setEnabled(this->isConnect);
  ui->button_write->setEnabled(this->isConnect);
  //    qDebug() << getCorrectDataFromHex("my_new1.hex");
}

void MainWindow::slotLoadFile() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open hex file"), QDir::currentPath(), tr("*.hex"));
  m_parser.openHexFile(fileName);
  auto values = m_parser.getAllValues();
  for (int i = 0; i < values.size(); ++i) {
    qDebug() << "index: " << i << " value: " << values.at(i);
    inputs.at(i)->setText(values.at(i));
  }
}

double MainWindow::hex2double(const std::string &hex) {
  if (hex.size() == 0) {
    std::cout << "Data not read" << std::endl;
  }
  union {
    long long i;
    double d;
  } value;

  value.i = std::stoull(hex, nullptr, 16);
  return value.d;
}

std::string MainWindow::double2hex(double d) {
  union {
    long long i;
    double d;
  } value;

  value.d = d;

  char buf[17];

  snprintf(buf, sizeof(buf), "%016llx", value.i);
  buf[16] = 0;  // make sure it is null terminated.

  return std::string(buf);
}

void MainWindow::readData() {
  process = new QProcess(this);

  process->start("cmd.exe", QStringList() << "/c "
                                          << "del.bat");

  if (process->waitForFinished()) qDebug() << "start dell file";

  process->waitForFinished(-1);
  qDebug() << "all file del";

  QString command = "ST-LINK_CLI.exe -c UR -Dump ";

  process->start("cmd.exe", QStringList() << "/c " + command + addrRead.addr1 +
                                                 " 8 " + nameF.addr[0]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr2.toUtf8() +
                                                 " 8 " + nameF.addr[1]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr3.toUtf8() +
                                                 " 8 " + nameF.addr[2]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr4.toUtf8() +
                                                 " 8 " + nameF.addr[3]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr5.toUtf8() +
                                                 " 8 " + nameF.addr[4]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr6.toUtf8() +
                                                 " 8 " + nameF.addr[5]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr7.toUtf8() +
                                                 " 8 " + nameF.addr[6]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr8.toUtf8() +
                                                 " 8 " + nameF.addr[7]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr9.toUtf8() +
                                                 " 8 " + nameF.addr[8]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr10.toUtf8() +
                                                 " 8 " + nameF.addr[9]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr11.toUtf8() +
                                                 " 8 " + nameF.addr[10]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr12.toUtf8() +
                                                 " 8 " + nameF.addr[11]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr13.toUtf8() +
                                                 " 8 " + nameF.addr[12]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";

  process->start("cmd.exe", QStringList() << "/c " + command +
                                                 addrRead.addr14.toUtf8() +
                                                 " 8 " + nameF.addr[13]);
  if (process->waitForFinished()) qDebug() << "read";

  process->waitForFinished(-1);
  qDebug() << "Finish read ";
}

void MainWindow::writeData(int num, double data) {
  std::string hex = double2hex(data);
  qDebug() << QString::fromUtf8(hex.c_str());
  std::string hexS = hex;

  std::string secondHex = hex.erase(8);
  std::string firstHex = hexS.erase(0, 8);
  QString comandF;
  QString comandS;
  switch (num) {
    case 0:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr1 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr1 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;
    case 1:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr2 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr2 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;
    case 2:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr3 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr3 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 3:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr4 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr4 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 4:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr5 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr5 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 5:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr6 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr6 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 6:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr7 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr7 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 7:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr8 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr8 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 8:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr9 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr9 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 9:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr10 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr10 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 10:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr11 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr11 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 11:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr12 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr12 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 12:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr13 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr13 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    case 13:
      comandF = "ST-LINK_CLI.exe -c UR -w32 " + adr1.addr14 + " " + "0x" +
                QString::fromUtf8(firstHex.c_str());
      comandS = "ST-LINK_CLI.exe -c UR -w32 " + adr2.addr14 + " " + "0x" +
                QString::fromUtf8(secondHex.c_str());
      break;

    default:
      return;
      break;
  }

  process = new QProcess(this);
  process->start("cmd.exe", QStringList() << "/c " + comandF);
  if (process->waitForFinished()) {
    qDebug() << "Start command " + comandF;
  }
  process->waitForFinished(-1);
  qDebug() << "Finish command " + comandF;

  process->start("cmd.exe", QStringList() << "/c " + comandS);
  if (process->waitForFinished()) {
    qDebug() << "Start command " + comandS;
  }
  process->waitForFinished(-1);
  qDebug() << "Finish command " + comandS;
}

bool MainWindow::testConnect() {
  process = new QProcess(this);
  process->start("cmd.exe", QStringList()
                                << "/c ST-LINK_CLI.exe -c UR >conection.txt");
  if (process->waitForStarted()) {
    qDebug() << "Starting";
  }
  process->waitForFinished(-1);
  qDebug() << "finish";
  delete process;

  //    process->start("ping","mail.ru > test.txt",QProcess::ReadOnly);
}

bool MainWindow::checkSTMConnect(const QStringList &list) {
  if (list.isEmpty()) {
    return false;
  }
  QRegularExpression re("No target connected|No ST-LINK detected!");
  foreach (const QString &line, list) {
    QRegularExpressionMatch match = re.match(line);
    if (match.hasMatch()) {
      return false;
    }
  }
  return true;
}

bool MainWindow::checkSTMConnect(const QString &filename) {
  QStringList fileData;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    return false;
  }
  while (!file.atEnd()) {
    fileData << file.readLine();
  }

  return this->checkSTMConnect(fileData);
}

QByteArray MainWindow::solveCheckSum(QByteArray &arr) {
  QByteArray work = QByteArray::fromHex(arr);

  char sum = 0;
  foreach (char c, work)
    sum += c;

  sum = -sum;

  return QByteArray::fromRawData(&sum, 1).toHex().toUpper();
}

QByteArray MainWindow::buildOutputLine(QByteArray &data, int &offset) {
  // Start code
  QByteArray startRet = ":";
  QByteArray ret;

  // Byte count
  QByteArray tmp = QString::number(data.length() / 2, 16).toUpper().toUtf8();
  if (tmp.length() == 1) tmp = "0" + tmp;
  ret.push_back(tmp);

  // Address
  tmp = QString::number(offset, 16).toUpper().toUtf8();
  while (tmp.length() < 4) tmp.push_front("0");
  ret.push_back(tmp);
  offset += data.length() / 2;
  //    while(offset.length() < 4)
  //        offset.push_front("0");

  // Record Type
  ret.push_back("00");

  // Data
  ret.push_back(data);

  // CRC
  QByteArray crc = solveCheckSum(ret);

  ret.push_back(crc);

  // end of line
  startRet.push_back(ret);
  startRet.push_back("\r\n");

  return startRet.toUpper();
}

QString MainWindow::getAppKey() {
  QDateTime dt;
  QString ret;
  QRandomGenerator gen;
  ret = QString::number(dt.currentDateTime().toMSecsSinceEpoch()) +
        QString::number(dt.currentDateTime().toMSecsSinceEpoch());
  while (ret.length() < 32) {
    int value = gen.bounded(0, 9);
    ret = ret + QString::number(value);
  }
  return ret;
}

QString MainWindow::getDevEui() { return ui->input_deveui->text(); }

void MainWindow::incrementDevEui() {
  QString first = ui->input_deveui->text().mid(0, 8);
  QString second = ui->input_deveui->text().mid(9, 8);

  if (second.toUpper() == "FFFFFFFF") {
    uint tmp = first.toUInt(nullptr, 16);
    tmp++;
    first.setNum(tmp, 16);
    while (first.size() != 8) first = "0" + first;
    second = "00000000";
  } else {
    uint tmp = second.toUInt(nullptr, 16);
    tmp++;
    second.setNum(tmp, 16);
    while (second.size() != 8) second = "0" + second;
  }

  ui->input_deveui->setText(first.toUpper() + second.toUpper());
}

QString MainWindow::getAppEui() { return ui->input_appeui->text(); }

QString MainWindow::formatDataFromDouble(const double value) {
  QString ret = "";
  ret = QString::fromStdString(this->double2hex(value));
  while (ret.length() < 16) {
    ret = "0" + ret;
  }

  QString retT;
  for (int i = 0; i < ret.length() - 1; i += 2) {
    retT.push_front(ret.at(i + 1));
    retT.push_front(ret.at(i));
  }
  return retT;
}

bool MainWindow::buildOutputFile(const QString &filename) {
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly)) return false;

  //    :02 00 00 04 08 01 F2
  file.write(QByteArray(":020000040808EA\r\n"));

  qDebug() << "h";
  int offset = 256;
  int i = 0;
  while (i < 14) {
    QString rawData = "";
    int k = 0;
    while (i < 14 && k < 4) {
      rawData += this->formatDataFromDouble(dataFromInput(i).toDouble());
      i++;
      k++;
    }

    QByteArray tmp = rawData.toUtf8();
    QByteArray formatData = buildOutputLine(tmp, offset);
    file.write(formatData);
  }
  //  for(int i = 0; i < 14; ++i) {
  //      double data = dataFromInput(i).toDouble();
  ////      QByteArray newRow = buildOutputLine(data, offset);
  //      file.write(newRow);
  //  }

  file.write(QByteArray(":00000001FF"));
  file.close();
  return true;
}

QString MainWindow::dataFromInput(const int index) {
  return this->inputs.at(index)->text();
}

void MainWindow::setDataToOutput(const int index, const QString &data) {
  this->outputs.at(index)->setText(data);
}

void MainWindow::setDataToInput(const int index, const QString &data) {
  this->inputs.at(index)->setText(data);
  emit this->inputs.at(index)->textChanged(data);
}

QString MainWindow::getCorrectDataFromHex(const QString &filename) {
  QString ret = "";
  QString rawData = "";
  QStringList fileData;

  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File cant open:" << filename;
    return ret;
  }
  while (!file.atEnd()) {
    fileData << file.readLine();
  }

  file.close();

  if (fileData.length() != 3) {
    return ret;
  }

  rawData = fileData.at(1);
  rawData = rawData.remove(0, 9);
  rawData = rawData.remove(rawData.length() - 3, 3);

  for (int i = 0; i < rawData.length() - 1; i += 2) {
    ret.push_front(rawData.at(i + 1));
    ret.push_front(rawData.at(i));
  }

  return ret;
}
