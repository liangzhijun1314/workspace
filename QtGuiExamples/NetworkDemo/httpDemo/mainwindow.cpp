#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
//#include <QUrl>
#include <QEventLoop>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("Http 下载器"));
    manager = new QNetworkAccessManager(this);  //用来发送网络请求和接收应答
    connect(manager, SIGNAL(finished(QNetworkReply*)),
              this, SLOT(replyFinished(QNetworkReply*)));//应答结束的时候发送这个信号

    reply = manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
//            this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
//            this, SLOT(slotSslErrors(QList<QSslError>)));

    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDateReadProgress(qint64,qint64))); //下载更新的时候发送前面那个信号
    connect(reply, SIGNAL(finished()), this, SLOT(slotFinished()));   //应答结束
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
//    QByteArray responseData;//定义数据
//    QEventLoop eventLoop;
//    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));//信号槽
//    eventLoop.exec();       //block until finish
//    responseData = reply->readAll();//读取返回数据

//    ui->textBrowser->setText(QString(responseData));

    QString all = reply->readAll();
    ui->textBrowser->setText(all);
    reply->deleteLater(); //删除reply对象
}

void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();
    qDebug()<<"url = "<<ui->lineEdit->text();
    qDebug()<<"url path = "<<url.path();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        qDebug()<<" file open error";
        delete file;
        file = 0;
        return;
    }
    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();

}

void MainWindow::slotReadyRead()
{
    if (file)
        file->write(reply->readAll());
}

void MainWindow::slotFinished()
{
    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;     //下载完成之后
}

void MainWindow::updateDateReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);   //设置进度条
}
