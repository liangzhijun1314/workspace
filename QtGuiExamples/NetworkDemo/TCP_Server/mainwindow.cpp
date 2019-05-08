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

void MainWindow::start()    //开始监听
{
    ui->startButton->setEnabled(false);
    bytesReceived = 0;
    if(!tcpServer.listen(QHostAddress::Any,8888)) {
        qDebug()<<"tcp error : "<<tcpServer.errorString();
        close();
        return;
    }
    qDebug()<<"---start listen---";
    ui->serverStatusLabel->setText(QString::fromLocal8Bit("监听"));
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

void MainWindow::acceptConnection()  //接受连接
{
    tcpServerConnection = new QTcpSocket;
    tcpServerConnection = tcpServer.nextPendingConnection();//得到每个连进来的socket
    connect(tcpServerConnection,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));  //有可读的信息，触发读函数槽
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->serverStatusLabel->setText(QString::fromLocal8Bit("接受连接"));
    tcpServer.close();
}

void MainWindow::updateServerProgress()   //更新进度条，接收数据
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_5_8);
    qDebug()<<"sizeof qint64 = "<<sizeof(qint64);
    if (bytesReceived <= (sizeof(qint64) * 2)) {
        //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
        if (tcpServerConnection->bytesAvailable() >= (sizeof(qint64) * 2) && (fileNameSize == 0)) {
            in >> totalBytes >> fileNameSize;
            bytesReceived += (sizeof(qint64) * 2);
        }
        if (tcpServerConnection->bytesAvailable() >= fileNameSize && (fileNameSize != 0)) {
            // 接收文件名，并建立文件
            in >> fileName;
            ui->serverStatusLabel->setText(QString::fromLocal8Bit("接收文件 %1 ...").arg(fileName));
            bytesReceived += fileNameSize;
            localFile = new QFile(fileName);
            if (!localFile->open(QFile::WriteOnly)) {
                qDebug() << QString::fromLocal8Bit("打开文件 %1 失败").arg(fileName);
                return;
            }
        } else
            return;
    }

    if (bytesReceived < totalBytes) {  //如果接收的数据小于总数据，那么写入文件
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    ui->serverProgressBar->setMaximum(totalBytes);
    ui->serverProgressBar->setValue(bytesReceived);
    //更新进度条
    if (bytesReceived == totalBytes) { //接收数据完成时
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
        ui->serverStatusLabel->setText(QString::fromLocal8Bit("接收文件 %1 成功！").arg(fileName));
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)  //错误处理
{
    qDebug()<<"param error ："<<socketError;
    qDebug()<<"tcp Server error : "<<tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText(QString::fromLocal8Bit("服务端就绪"));
    ui->startButton->setEnabled(true);
}

void MainWindow::on_startButton_clicked()
{
    start();
}
