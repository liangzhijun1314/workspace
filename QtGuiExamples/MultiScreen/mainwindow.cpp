#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_label = new QLabel(this);
    m_label->show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setScreenIndex(int index)
{
    QString strInfo = "";
    qDebug()<<"index = "<<index;
    if(index == 0){
        strInfo = QString::fromLocal8Bit("信息");
    }else{
        strInfo = QString::fromLocal8Bit("广告");
    }
      m_label->setText(strInfo);
}
