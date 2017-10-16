#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QThread *aNewThread = new QThread();
    SerialPortWorker *aSerialPortWorker = new SerialPortWorker();
    aSerialPortWorker->setObjectName(UHV2WorkerObjName);
    aSerialPortWorker->moveToThread(aNewThread);

    connect(aNewThread, &QThread::started, aSerialPortWorker, &SerialPortWorker::start);
    connect(this, &MainWindow::Out, aSerialPortWorker, &SerialPortWorker::In);
    connect(aSerialPortWorker, &SerialPortWorker::Out, this, &MainWindow::In);

    QObject::connect(ui->pushButton_CustomTest, &QPushButton::clicked, ui->pushButtonReadP, &QPushButton::click);
    QObject::connect(ui->pushButton_CustomTest, &QPushButton::clicked, ui->pushButtonReadV, &QPushButton::click);
    QObject::connect(ui->pushButton_CustomTest, &QPushButton::clicked, ui->pushButtonReadI, &QPushButton::click);

    foreach (QSerialPortInfo currentScan, QSerialPortInfo::availablePorts())
    {
        ui->comboBoxSerialPort->addItem(currentScan.portName());
    }

    aNewThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::In(const GlobalSignal &aGlobalSignal)
{

}


void MainWindow::on_pushButton_UHVType_clicked()
{
    if (ui->pushButton_UHVType->text() == QStringLiteral("UHV2"))
    {
        ui->pushButton_UHVType->setText(QStringLiteral("UHV4"));
    }
    else
    {
        ui->pushButton_UHVType->setText(QStringLiteral("UHV2"));
    }
}


void MainWindow::updateSENDlabel(const QString &SENDstyleSheet, const QString &SentMsgStr, const QString &SentMessageStr)
{
    ui->labelSEND->setStyleSheet(SENDstyleSheet);
    ui->labelSentMsg->setStyleSheet(SENDstyleSheet);
    ui->labelSentMsg->setText(SentMsgStr);
    ui->labelSentMessage->setStyleSheet(SENDstyleSheet);
    ui->labelSentMessage->setText(SentMessageStr);
    ui->labelSEND->update();
    ui->labelSentMsg->update();
    ui->labelSentMessage->update();
}

void MainWindow::updateREADlabel(const QString &READstyleSheet, const QString &ReadMsgStr, const QString &ReadMessageStr)
{
    ui->labelREAD->setStyleSheet(READstyleSheet);
    ui->labelReadMsg->setStyleSheet(READstyleSheet);
    ui->labelReadMsg->setText(ReadMsgStr);
    ui->labelReadMessage->setStyleSheet(READstyleSheet);
    ui->labelReadMessage->setText(ReadMessageStr);
    ui->labelREAD->update();
    ui->labelReadMsg->update();
    ui->labelReadMessage->update();
}

void MainWindow::on_pushButtonHVonoff_clicked()
{

}

void MainWindow::on_pushButtonReadV_clicked()
{

}

void MainWindow::on_pushButtonReadI_clicked()
{

}

void MainWindow::on_pushButtonReadP_clicked()
{

}
