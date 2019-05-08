/*******************************************************************************
** @file:     clientwidget.cpp
** @class:    ClientWidget
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

#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QFileDialog>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpClient = new QTcpSocket(this);
    connect(tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));
    //�����ӷ������ɹ�ʱ������connected()�źţ����ǿ�ʼ�����ļ�
    connect(tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    //�������ݷ��ͳɹ�ʱ�����Ǹ��½�����
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->sendButton->setEnabled(false);
    ui->hostLineEdit->setText("192.168.1.170");
    ui->portLineEdit->setText("8888");
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

//���ӵ���������ִ�з���
void ClientWidget::send()
{
    ui->sendButton->setEnabled(false);
    bytesWritten = 0;
    //��ʼ���ѷ����ֽ�Ϊ0
    ui->clientStatusLabel->setText(QString::fromLocal8Bit("12345�����С�"));
    tcpClient->connectToHost(QHostAddress(ui->hostLineEdit->text()),ui->portLineEdit->text().toInt());//����
}

//ʵ���ļ���С����Ϣ�ķ���
void ClientWidget::startTransfer()
{
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }
    totalBytes = localFile->size();
    //�ļ��ܴ�С
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFileName;
    //����д���ܴ�С��Ϣ�ռ䣬�ļ�����С��Ϣ�ռ䣬�ļ���---�����ļ�������·����û��Ҫ��·��
    totalBytes += outBlock.size();
    //������ܴ�С���ļ�����С����Ϣ��ʵ���ļ���С���ܺ�
    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));
    //totalBytes���ļ��ܴ�С��������quint64�Ĵ�С+�ļ���+�ļ�ʵ�����ݵĴ�С
    //qint64((outBlock.size() - sizeof(qint64)*2))�õ������ļ�����С
    bytesToWrite = totalBytes - tcpClient->write(outBlock);
    //������ͷ���ݺ�ʣ�����ݵĴ�С�����ļ�ʵ�����ݵĴ�С
    ui->clientStatusLabel->setText(QString::fromLocal8Bit("123456������"));
    outBlock.resize(0);
    qDebug()<<"#####"<<totalBytes;
}

//���½�������ʵ���ļ��Ĵ���
void ClientWidget::updateClientProgress(qint64 numBytes)
{
    qDebug()<<"#######�ѷ��ͣ�"<<bytesWritten<<"ʣ�ࣺ"<<bytesToWrite;
    bytesWritten += (int)numBytes;
    //�Ѿ��������ݵĴ�С
    if(bytesToWrite > 0) //����Ѿ�����������
    {
        outBlock = localFile->read(qMin(bytesToWrite,loadSize));
        //ÿ�η���loadSize��С�����ݣ���������Ϊ4KB�����ʣ������ݲ���4KB��
        //�ͷ���ʣ�����ݵĴ�С
        bytesToWrite -= (int)tcpClient->write(outBlock);
        //������һ�����ݺ�ʣ�����ݵĴ�С
        outBlock.resize(0);
        //��շ��ͻ�����
    }
    else
    {
        localFile->close(); //���û�з����κ����ݣ���ر��ļ�
    }
    ui->clientProgressBar->setMaximum(totalBytes);
    ui->clientProgressBar->setValue(bytesWritten);
    //���½�����
    if(bytesWritten == totalBytes) //�������
    {
        ui->clientStatusLabel->setText(QString::fromLocal8Bit("�����ļ� %1 �ɹ�").arg(fileName));
        localFile->close();
        tcpClient->close();
    }
}

void ClientWidget::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpClient->errorString();
    tcpClient->close();
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText(QString::fromLocal8Bit("�ͻ��˾���"));
    ui->sendButton->setEnabled(true);
}

void ClientWidget::openFile()   //���ļ�
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        ui->sendButton->setEnabled(true);
        ui->clientStatusLabel->setText(QString::fromLocal8Bit("���ļ� %1 �ɹ���").arg(fileName));
    }
}

void ClientWidget::on_sendButton_clicked()
{
    send();
}

void ClientWidget::on_openButton_clicked()
{
    openFile();
}
