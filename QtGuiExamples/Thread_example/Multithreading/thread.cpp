#include "thread.h"
#include <iostream>
#include <QDebug>
#include <QMutexLocker>
using namespace std;

Thread::Thread(QString message, QObject *parent):
    stopped(false)
  , QThread(parent)
{
    stopped = false;
}

Thread::~Thread()
{
    this->stop();
    this->wait();
    qDebug() << this;
}

void Thread::setMessage(const QString &message)
{
    this->messageStr = message;
}

QString Thread::getMessage()
{
    return this->messageStr;
}

void Thread::stop()
{
//    mutex.lock();
    QMutexLocker locker(&mutex);
    stopped = true;
//    mutex.unlock();
}

void Thread::run()
{
//    while (!stopped){
//        printMessage();
//    }
//    stopped = false;

    forever{
//        mutex.lock();
        QMutexLocker locker(&mutex);
        if(stopped){
            stopped = false;
//            mutex.unlock();
            break;
        }
//        mutex.unlock();
        printMessage();
    }
    std::cerr<<std::endl;
}

void Thread::printMessage()
{
    qDebug()<<"messageStr = "<<this->messageStr;
    sleep(1);
}
