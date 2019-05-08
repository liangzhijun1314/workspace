/*******************************************************************************
** @file:     sender.cpp
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-4-10
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#include <QtWidgets>
#include <QtNetwork>

#include "sender.h"

Sender::Sender(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(QString::fromLocal8Bit("广播发射器"));
    statusLabel = new QLabel(QString::fromLocal8Bit("准备在端口45454广播数据报"));
    statusLabel->setWordWrap(true); //可以换行

    startButton = new QPushButton(QString::fromLocal8Bit("开始"));
    quitButton = new QPushButton(QString::fromLocal8Bit("退出"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton,QDialogButtonBox::AcceptRole);
    buttonBox->addButton(quitButton,QDialogButtonBox::RejectRole);

    timer = new QTimer(this);

    udpSocket = new QUdpSocket(this);
    messageNo = 1;

    connect(startButton,SIGNAL(clicked()),this,SLOT(startBroadcasting()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(timer,SIGNAL(timeout()),this,SLOT(broadcastDatagram()));

    widgetLayout();
}

Sender::~Sender()
{

}

void Sender::widgetLayout()
{
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    this->setLayout(mainLayout);
}

void Sender::startBroadcasting()
{
    startButton->setEnabled(false);
    timer->start(2000);  // 2秒的定时器
}

void Sender::broadcastDatagram()
{
    statusLabel->setText(QString::fromLocal8Bit("现在广播数据报 %1").arg(messageNo));

    QByteArray datagram = "Broadcast message : " + QByteArray::number(messageNo);
    udpSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,45454);
    ++messageNo;
}
