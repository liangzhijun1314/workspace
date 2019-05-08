#include "server.h"
#include "serverthread.h"

Server::Server(MainWindow *m,int p,QHostAddress a)
{
    this->hostAddress=a;
    this->port=p;
    this->mainWindow=m;
    this->clientNum=0;
    this->QTcpServer::listen(hostAddress,quint16(port));
    connect(this,SIGNAL(printText(const char*)),this->mainWindow,SLOT(showText(const char*)));
}

void Server::incomingConnection(int handle)
{
    qDebug()<<" in coming Connection -";
    char ch[]="new connection !";
    emit printText(ch);
    ServerThread *thread=new ServerThread(handle,this,mainWindow,this->clientNum);
    this->clientNum++;
    thread->start();
}
