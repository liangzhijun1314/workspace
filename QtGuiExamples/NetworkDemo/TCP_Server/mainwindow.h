/*******************************************************************************
** @file:     mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QFile>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void start();       //��ʼ����
    void acceptConnection();  //��������
    void updateServerProgress();  //���½���������������
    void displayError(QAbstractSocket::SocketError socketError);
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer  tcpServer;
    QTcpSocket  *tcpServerConnection;
    qint64      totalBytes;         //����ܴ�С��Ϣ
    qint64      bytesReceived;      //���յ����ݵĴ�С
    qint64      fileNameSize;       //�ļ����Ĵ�С��Ϣ
    QString     fileName;           //����ļ���
    QFile       *localFile;         //�����ļ�
    QByteArray  inBlock;            //���ݻ�����
};

#endif // MAINWINDOW_H
