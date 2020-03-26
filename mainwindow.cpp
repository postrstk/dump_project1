#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->button_connect, &QPushButton::clicked, this, &MainWindow::slotConnect);
  connect(ui->button_read, &QPushButton::clicked, this, &MainWindow::slotRead);
  connect(ui->button_write, &QPushButton::clicked, this, &MainWindow::slotWrite);

  ui->button_read->setEnabled(this->isConnect);
  ui->button_write->setEnabled(this->isConnect);

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

    this->setDataToOutput(i, "00000000");
  }
  writeData(0,12.5);
  readData();
//  testConnect();

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slotRead()
{
    readData();
    QString tmp = getCorrectDataFromHex("my_new1.hex");
    double f = hex2double(tmp.toStdString());
    setDataToOutput(0,QString::number(f));
  // Read some data and write into outputs
}

void MainWindow::slotWrite()
{
  // Write data from inputs
    for (int i = 0; i <14;i++)
    {
        writeData(i,dataFromInput(i).toDouble());
    }
}

void MainWindow::slotConnect()
{
  this->isConnect = true;
  ui->button_read->setEnabled(this->isConnect);
  ui->button_write->setEnabled(this->isConnect);
//    qDebug() << getCorrectDataFromHex("my_new1.hex");
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

void MainWindow::readData()
{
    QString command="ST-LINK_CLI.exe -c UR -Dump ";

    process = new QProcess(this);
    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr1 + " 8 " + nameF.addr1);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr2 + " 8 " + nameF.addr2);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr3 + " 8 " + nameF.addr3);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr4 + " 8 " + nameF.addr4);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr5 + " 8 " + nameF.addr5);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr6 + " 8 " + nameF.addr6);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr7 + " 8 " + nameF.addr7);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr8 + " 8 " + nameF.addr8);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr9 + " 8 " + nameF.addr9);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr10 + " 8 " + nameF.addr10);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr11 + " 8 " + nameF.addr11);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr12 + " 8 " + nameF.addr12);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr13 + " 8 " + nameF.addr13);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

    process->start("cmd.exe",QStringList()<<"/c "+command + addrRead.addr14 + " 8 " + nameF.addr14);
    if(process->waitForFinished())
    {
        qDebug() <<"read";
    }
    process->waitForFinished(-1);
    qDebug() << "Finish read ";

}

void MainWindow::writeData(int num, double data)
{
    std::string hex = double2hex(data);
    qDebug() << QString::fromUtf8(hex.c_str());
    std::string hexS = hex;

    std::string secondHex = hex.erase(8);
    std::string firstHex = hexS.erase(0,8);
    QString comandF;
    QString comandS;
    switch (num) {
    case 0:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr1+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr1+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        qDebug() << comandF;
        qDebug() << comandS;
        break;
    case 1:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr2+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr2+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;
    case 2:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr3+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr3+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 3:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr4+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr4+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 4:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr5+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr5+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 5:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr6+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr6+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 6:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr7+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr7+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 7:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr8+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr8+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 8:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr9+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr9+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 9:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr10+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr10+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 10:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr11+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr11+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 11:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr12+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr12+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 12:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr13+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr13+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    case 13:
        comandF="ST-LINK_CLI.exe -c UR -w32 "+adr1.addr14+" "+"0x"+QString::fromUtf8(firstHex.c_str());
        comandS="ST-LINK_CLI.exe -c UR -w32 "+adr2.addr14+" "+"0x"+QString::fromUtf8(secondHex.c_str());
        break;

    default:
        return;
        break;
    }

    process = new QProcess(this);
    process->start("cmd.exe",QStringList()<<"/c "+comandF);
    if(process->waitForFinished())
    {
        qDebug() <<"Start command "+ comandF;
    }
    process->waitForFinished(-1);
    qDebug() << "Finish command "+comandF;

    process->start("cmd.exe",QStringList()<<"/c "+comandS);
    if(process->waitForFinished())
    {
        qDebug() <<"Start command "+ comandS;
    }
    process->waitForFinished(-1);
    qDebug()<<"Finish command "+comandS;

}


bool MainWindow::testConnect()
{
    process = new QProcess(this);
    process->start("cmd.exe",QStringList() << "/c ST-LINK_CLI.exe -c UR >conection.txt");
    if(process->waitForStarted()){
        qDebug() << "Starting";
    }
    process->waitForFinished(-1);
        qDebug() << "finish";
    delete process;

        //    process->start("ping","mail.ru > test.txt",QProcess::ReadOnly);
}

bool MainWindow::checkSTMConnect(const QStringList &list)
{
  if(list.isEmpty()) {
    return false;
  }
  QRegularExpression re("No target connected");
  foreach(const QString& line, list) {

    QRegularExpressionMatch match = re.match(line);
    if(match.hasMatch()) {
      return false;
    }
  }
  return true;
}

bool MainWindow::checkSTMConnect(const QString &filename)
{
  QStringList fileData;

  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly)) {
    return false;
  }
  while(!file.atEnd()) {
    fileData << file.readLine();
  }

  return this->checkSTMConnect(fileData);
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
