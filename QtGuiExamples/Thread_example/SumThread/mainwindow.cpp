#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include "thread.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = new Thread();
    connect(thread, SIGNAL(returnResult(long)), this, SLOT(displayResult(long)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sumBtn_clicked()
{
    if(ui->lineEdit->text()!=" ")
        ui->lineEdit->clear();
    thread->start();

}

void MainWindow::on_showBtn_clicked()
{
    qDebug()<<"thread id = "<<QThread::currentThreadId();
    static int flag = 0;
    if(flag == 0)
    {
        flag = 1;
        ui->lineEdit->setText(tr("hello, world!"));
    }
    else
    {
        flag = 0;
        ui->lineEdit->setText(tr("I Love You!"));
    }
}

void MainWindow::displayResult(long result)
{
    ui->lineEdit->setText(QString::number(result));
}
