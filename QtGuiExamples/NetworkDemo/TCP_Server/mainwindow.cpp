/*******************************************************************************
** @file:     mainwindow.cpp
** @class:    MainWindow
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-4-8
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()    //��ʼ����
{
    ui->startButton->setEnabled(false);
    bytesReceived = 0;
    if(!tcpServer.listen(QHostAddress::Any,8888)) {
        qDebug()<<"tcp error : "<<tcpServer.errorString();
        close();
        return;
    }
    qDebug()<<"---start listen---";
    ui->serverStatusLabel->setText(QString::fromLocal8Bit("����"));
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

void MainWindow::acceptConnection()  //��������
{
    tcpServerConnection = new QTcpSocket;
    tcpServerConnection = tcpServer.nextPendingConnection();//�õ�ÿ����������socket
    connect(tcpServerConnection,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));  //�пɶ�����Ϣ��������������
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->serverStatusLabel->setText(QString::fromLocal8Bit("��������"));
    tcpServer.close();
}

void MainWindow::updateServerProgress()   //���½���������������
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_5_8);
    qDebug()<<"sizeof qint64 = "<<sizeof(qint64);
    if (bytesReceived <= (sizeof(qint64) * 2)) {
        //������յ�������С��16���ֽڣ���ô�Ǹտ�ʼ�������ݣ����Ǳ��浽//����ͷ�ļ���Ϣ
        if (tcpServerConnection->bytesAvailable() >= (sizeof(qint64) * 2) && (fileNameSize == 0)) {
            in >> totalBytes >> fileNameSize;
            bytesReceived += (sizeof(qint64) * 2);
        }
        if (tcpServerConnection->bytesAvailable() >= fileNameSize && (fileNameSize != 0)) {
            // �����ļ������������ļ�
            in >> fileName;
            ui->serverStatusLabel->setText(QString::fromLocal8Bit("�����ļ� %1 ...").arg(fileName));
            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if (!localFile->open(QFile::WriteOnly)) {
                qDebug() << QString::fromLocal8Bit("���ļ� %1 ʧ��").arg(fileName);
                return;
            }
        } else
            return;
    }

    if (bytesReceived < totalBytes) {  //������յ�����С�������ݣ���ôд���ļ�
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    ui->serverProgressBar->setMaximum(totalBytes);
    ui->serverProgressBar->setValue(bytesReceived);
    //���½�����
    if (bytesReceived == totalBytes) { //�����������ʱ
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
        ui->serverStatusLabel->setText(QString::fromLocal8Bit("�����ļ� %1 �ɹ���").arg(fileName));
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)  //������
{
    qDebug()<<"param error ��"<<socketError;
    qDebug()<<"tcp Server error : "<<tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText(QString::fromLocal8Bit("����˾���"));
    ui->startButton->setEnabled(true);
}

void MainWindow::on_startButton_clicked()
{
    start();
}
