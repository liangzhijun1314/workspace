/*******************************************************************************
** @file:     mainwindow.cpp
** @class:    MainWindow
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-4-9
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QHostAddress>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText(QString::fromLocal8Bit("¿ªÊ¼¼àÌý"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getConnect()
{
    QTextDocument *textDocumentM=new QTextDocument(QString("new connect !"),this);
    ui->textEdit->setDocument(textDocumentM);
    server->nextPendingConnection();
}

void MainWindow::execCommand(const char *command, int length, const char *add, int clientCode)
{
    QTextDocument *textDocumentC=new QTextDocument(QString("message"),this);
    char *commandStr=new char[length+15];
    strcpy(commandStr,command);
    char *para=commandStr+length;
    char *c=" > temp.txt";
    strcpy(para,c);
    system(commandStr);
    emit writeFile(clientCode);
    ui->textEdit->setDocument(textDocumentC);
}

void MainWindow::ShowText(const char *text)
{
    QTextDocument *textDocumentT=new QTextDocument(QString(text),this);
    ui->textEdit->setDocument(textDocumentT);
}

void MainWindow::on_pushButton_clicked()
{
    server = new Server(this,8888,QHostAddress::Any);
}
