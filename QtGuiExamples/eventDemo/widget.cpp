#include "widget.h"
#include "custombutton.h"
#include "customevent.h"
#include <QVBoxLayout>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//    this->resize(300,200);
//    customBtn = new CustomButton(this);
//    customBtn->setGeometry(100,90,100,20);
//    customBtn->show();

    //事件的接受与忽略
    customWidget  = new CustomWidget(this);
    customBtn = new CustomButton(customWidget);
    customBtnEx = new CustomButtonEx(customWidget);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(customBtn);
    layout->addWidget(customBtnEx);
    customWidget->setLayout(layout);
    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(customWidget);
    this->setLayout(mainLayout);


}

Widget::~Widget()
{

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"Main Widget press";
}

bool Widget::event(QEvent *event)
{
    CustomEvent* cevent = static_cast <CustomEvent*> (event);
    if (event->type() == CustomEvent::EventType) {
        qDebug()<<"event() is dispathing CustomEvent";
        CustomEvent *cEvent = static_cast<CustomEvent *>(event);
        processEvent(cEvent);
        if (cEvent->isAccepted()) {
            qDebug()<<"The CustomEvent has been handled!";
            return true;
        }
    }
    if (event->type() == static_cast<QEvent::Type>(CustomEvent::getType(CustomEventType::CUSTOM_EVENT_1))) {
        qWarning()<<"use event"<<cevent->getId();
    }
    return QObject::event(event);
}

void Widget::processEvent(CustomEvent *event)
{
    qDebug()<<"Process customEvent "<<event->type();
    event->accept();
}

void Widget::customEvent(QEvent *event)
{
    qWarning()<<"use customEvent ";

    CustomEvent* cevent = static_cast <CustomEvent*> (event);

    qWarning()<<"custom event"<<cevent->getId();
}
