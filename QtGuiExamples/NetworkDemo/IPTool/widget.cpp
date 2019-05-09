#include "widget.h"
#include "ui_widget.h"
#include <QtNetwork>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//判断IP地址及端口是否在线
bool Widget::IPLive(QString ip, int port) {
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, port);
    //100毫秒没有连接上则判断不在线
    return tcpClient.waitForConnected(100);
}

//获取网页所有源代码
QString Widget::GetHtml(QString url) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    return QString(responseData);
}

//获取本机公网IP地址
QString Widget::GetNetIP(QString webCode) {
    QString web = webCode.replace(" ", "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    QStringList list = web.split("<br/>");
    QString tar = list[3];
    QStringList ip = tar.split("=");
    return ip[1];
}

void Widget::on_btnGetLocalIP_clicked()
{
    ui->txtLocalIP->setText(QNetworkInterface::allAddresses()[0].toString());
}

void Widget::on_btnGetWebIP_clicked()
{
    ui->txtWebIP->setText(GetNetIP(GetHtml("http://whois.pconline.com.cn/")));
}

void Widget::on_btnCheckWeb_clicked()
{
    //能接通百度IP说明可以通外网
    bool ok=IPLive("202.108.22.5", 80);
    ui->txtCheckWeb->setText(ok?"true":"false");
}
