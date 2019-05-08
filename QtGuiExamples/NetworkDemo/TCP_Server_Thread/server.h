#ifndef SERVER_H
#define SERVER_H

#include <QTextDocument>
#include <QTcpServer>

class MainWindow;

class Server:public QTcpServer
{
    Q_OBJECT
private:
    int port;
    MainWindow *mainWindow;
    QHostAddress hostAddress;
    int clientNum;

public:
    Server(MainWindow *m,int p,QHostAddress a);
    void incomingConnection(int handle);
signals:
    void printText(const char *text);

};

#endif // SERVER_H
