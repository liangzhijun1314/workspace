/*******************************************************************************
** @file:     clientwidget.h
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

#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void send();  //���ӷ�����
    void startTransfer();  //�����ļ���С����Ϣ
    void updateClientProgress(qint64 numBytes); //�������ݣ����½�����
    void displayError(QAbstractSocket::SocketError); //��ʾ����
    void openFile();  //���ļ�
    void on_sendButton_clicked();

    void on_openButton_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpClient;
    QFile *localFile;  //Ҫ���͵��ļ�
    qint64 totalBytes;  //�����ܴ�С
    qint64 bytesWritten;  //�Ѿ��������ݴ�С
    qint64 bytesToWrite;   //ʣ�����ݴ�С
    qint64 loadSize;   //ÿ�η������ݵĴ�С
    QString fileName;  //�����ļ�·��
    QByteArray outBlock;  //���ݻ������������ÿ��Ҫ���͵�����
};

#endif // CLIENTWIDGET_H
