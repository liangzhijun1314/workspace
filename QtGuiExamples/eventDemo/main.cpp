#include "widget.h"
#include <QApplication>
#include <QDebug>
#include "customevent.h"

//Qt 的事件处理方式的调用顺序
/*
 *  顺序
 * 1:---QApplication eventFilter---
 * 2:---Label eventFilter---
 * 3:---Label event---
 * 4:---Label mousePressEvent---
 */

class Label : public QWidget
{
public:
    Label()
    {
        installEventFilter(this);  //Label 安装事件过滤器
        this->setWindowTitle(tr("label mouse press demo"));
    }

    bool eventFilter(QObject *watched, QEvent *event)
    {
        if (watched == this) {
            if (event->type() == QEvent::MouseButtonPress) {  //判断是鼠标点击的事件
                qDebug()<<"---Label eventFilter---";
            }
        }
    }
protected:
    void mousePressEvent(QMouseEvent * event)  //鼠标点击事件
    {
        qDebug()<<"---Label mousePressEvent---";
    }
    bool event(QEvent *event)   // 事件分发
    {
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug()<<"---Label event---";
        }
        return QWidget::event(event);
    }
};

class EventFilter : public QObject
{
public:
    EventFilter(QObject * watched, QObject *parent = 0):
        QObject(parent),
        m_watched(watched)
    {

    }
    bool eventFilter(QObject *watched, QEvent *event)
    {
        if (watched == m_watched) {
            if (event->type() == QEvent::MouseButtonPress) {
               qDebug()<<"---QApplication eventFilter---";
            }
        }
    }
private:
    QObject *m_watched;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    //事件处理方式的调用顺序测试  测试不成功
//    Label label;
//    a.installEventFilter(new EventFilter(&label,&label));
//    label.show();

    Widget w;
    w.show();

//自定义事件的发送和处理 1
    CustomEvent cEvent;
    a.sendEvent(&w,&cEvent);

//自定义事件的发送和处理 2
    CustomEvent * cust = new CustomEvent(CustomEvent::getType(CustomEventType::CUSTOM_EVENT_1));
    cust->setId(15);
    a.sendEvent(&w,cust);

    return a.exec();
}

//  自定义事件实例
//#include <QApplication>
//#include <QCoreApplication>
//#include <QEvent>
//#include <QObject>
//#include <QDebug>

//static const QEvent::Type MyEventType = (QEvent::Type)QEvent::registerEventType(QEvent::User+100);

////长官
//class MyEvent: public QEvent
//{
//public:
//    MyEvent(Type MyEventType):QEvent(MyEventType){}
//};

////信使
//class MySender: public QCoreApplication
//{
//public:
//    MySender(int argc,char *argv[]):QCoreApplication(argc,argv){}

//public:
//    bool notify(QObject *receiver, QEvent *event);

//};

//bool MySender::notify(QObject *receiver, QEvent *event)
//{
//    qDebug()<<"event type = "<<event->type();
//    if(event->type() == MyEventType)
//    {
//        qDebug()<<"MyEventType is coming!";
//        //return true;
//        /*这里不能return true,因为重写notify就是在事件被向下传递之前截住它，
//        随便搞它，搞完了还得给QCoreApplication::notify向下传递，除非在mySender.notify
//        实现了事件向下传递的那一套。直接返回的话myArmy就收不到这个事件，因为执行完这个
//        mySender.notify的return true后，事件传递被人为的在半截终止了
//        （见Qt事件处理的五个层次http://blog.csdn.net/michealtx/article/details/6865891 ）
//        ，下面的myArmy的安装的过滤器和它自己的event都不会收到这个事件，更甭提最后干活
//        的myEventHandler了。所以在主函数中执行完mySender.sendEvent把myEvent
//        交给mySender.notify这个败家子儿后，就执行mySender.exec进入其它事件的循环了。这就是
//        问题http://topic.csdn.net/u/20111012/19/78036d16-c163-40f9-a05c-3b7d6f4e9043.html
//        出现的原因。感谢1+1=2大牛！非常感谢！
//        */
//    }
//    return QCoreApplication::notify(receiver,event);
//}

////军队
//class MyArmy: public QObject
//{
//public:
//    void MyEventHandler(QEvent *event);
//    bool event(QEvent *event);
//};

//void MyArmy::MyEventHandler(QEvent *event)
//{
//    qDebug()<<"The event is being handled!";
//    event->accept();
//}

//bool MyArmy::event(QEvent *event)
//{
//    if(event->type() == MyEventType)
//    {
//        qDebug()<<"event() is dispathing MyEvent";
//        MyEventHandler(event);//调用事件处理函数
//        if((MyEvent*)event->isAccepted())
//        {
//            qDebug()<<"The event has been handled!";
//            return true;
//        }
//    }
//    return QObject::event(event);
//}

////监控者
//class MyWatcher: public QObject
//{
//public:
//    bool eventFilter(QObject *watched, QEvent *event);
//};

//bool MyWatcher::eventFilter(QObject *watched, QEvent *event)
//{
//    if(event->type() == MyEventType)
//    {
//        qDebug()<<"I don't wanna filter MyEventType";
//        return false;
//    }
//    return QObject::eventFilter(watched,event);
//}


//int main(int argc, char *argv[])
//{
//    //QCoreApplication a(argc, argv);
//    MySender mySender(argc,argv);

//    MyArmy myArmy;
//    MyWatcher myWatcher;
//    myArmy.installEventFilter(&myWatcher);//安装事件过滤器

//    MyEvent myEvent(MyEventType);
//    mySender.sendEvent(&myArmy,&myEvent);
//    return mySender.exec();
//}
