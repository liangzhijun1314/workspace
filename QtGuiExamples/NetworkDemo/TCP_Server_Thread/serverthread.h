#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include "mainwindow.h"

class ServerThread:public QThread
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    MainWindow *mainWindow;
    int clientCode;
public:
    ServerThread(int socketDescriptor,QObject *parent,MainWindow *m,int clientCode);
    void run();
signals:
    void newCommand(const char *str,const int length,const char *add,int clientCode);
public slots:
    void receiveData();
    void readFile(int cC);
};

#endif // SERVERTHREAD_H
