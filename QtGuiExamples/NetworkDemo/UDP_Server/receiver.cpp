/*******************************************************************************
** @file:     receiver.cpp
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

#include "receiver.h"
#include <QtWidgets>
#include <QtNetwork>

Receiver::Receiver(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(QString::fromLocal8Bit("广播接收器"));
    statusLabel = new QLabel(QString::fromLocal8Bit("监听广播消息"));
    statusLabel->setWordWrap(true); //设置文字可以换行

    quitButton = new QPushButton(QString::fromLocal8Bit("&退出"));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454,QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    widgetLayout();

}

Receiver::~Receiver()
{

}

void Receiver::widgetLayout()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);

}

void Receiver::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        qDebug()<<"udpSocket->pendingDatagramSize() ========= "<<udpSocket->pendingDatagramSize();
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        statusLabel->setText(QString::fromLocal8Bit("接收到数据报 : \"%1\"")
                             .arg(datagram.data()));
    }
}
