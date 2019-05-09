#include "serverthread.h"
#include <QFile>
#define COMMAND_SIZE 50
ServerThread::ServerThread(int socketDescriptor,QObject *parent,MainWindow *m,int c):QThread(parent)
{
    this->mainWindow=m;
    this->clientCode=c;
    socket=new QTcpSocket(parent);
    socket->setSocketDescriptor(socketDescriptor);
}

void ServerThread::run()
{
    this->connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
    connect(this,SIGNAL(newCommand(const char*,int,const char*,int)),this->mainWindow,SLOT(execCommand(const char*,int,const char*,int)));
    connect(this->mainWindow,SIGNAL(writeFile(int)),this,SLOT(readFile(int)));
    exec();
}

void ServerThread::receiveData()
{
    int left=socket->bytesAvailable();
    char *command=new char[COMMAND_SIZE];
    while(left>0)
    {
        int read=socket->readLine(command,COMMAND_SIZE);
        emit newCommand(command,read,"test",this->clientCode);
        left-=read;
    }
}

void ServerThread::readFile(int cC)
{
    if(cC==this->clientCode)
    {
        QFile *file=new QFile("temp.txt");
        if(file->open(QIODevice::ReadWrite))
        {
            char *buffer=new char[100];
            int length;
            while((length=file->read(buffer,100))>0)
            {
                socket->write(buffer,length);
            }
        }
        socket->flush();
        file->close();
        system("del temp.txt");
    }
}
