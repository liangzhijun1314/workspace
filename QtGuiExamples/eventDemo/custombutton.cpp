#include "custombutton.h"
#include <QDebug>
#include <QMouseEvent>

CustomButton::CustomButton(QWidget *parent):
    QPushButton(parent)
{
    this->setText(tr("CustomButton Click me"));
//    connect(this,&CustomButton::clicked,
//            this,&CustomButton::onClicked);
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"--CustomButton--";
//    qDebug()<<"event button = "<<event->button();
//    qDebug()<<"event isAccept = "<<event->isAccepted();
//    if (event->button() == Qt::LeftButton) {
//        qDebug()<<"left button clicked me ";
//    } else if ( event->button() == Qt::RightButton) {
//        qDebug()<<"right button clicked me ";
//    } /*else if ( event->button() == Qt::MiddleButton) {
//        qDebug()<<"middle button clicked me ";
//    } */else {  //调用父类的同名函数
//        QPushButton::mousePressEvent(event);
//    }
}

void CustomButton::onClicked()
{
    qDebug()<<"You Clicked me!!!";
}

CustomButtonEx::CustomButtonEx(QWidget *parent) :
    CustomButton(parent)
{
    this->setText(tr("CustomButtonEx Click me"));
}

void CustomButtonEx::mousePressEvent(QMouseEvent *event)
{
//    event->accept();
    event->ignore();//ignore()说明我们想让事件继续传播,于是CustomButtonEx的父组件CustomWidget也收到了这个事件
    qDebug()<<"--CustomButtonEx--";
}

CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent)
{

}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    //QWidget的默认是调用event->ignore()
    //自定义的事件默认是调用event->accept()
    //调用accept()意味着 Qt 会停止事件的传播 调用ignore()则意味着事件继续传播
    qDebug()<<"--CustomWidget--";
    event->accept();
//    event->ignore();
//    QWidget::mousePressEvent(event);
}
