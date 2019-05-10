#include "thread.h"
#include <QDebug>

Thread::Thread()
{
}
void Thread::run()
{
    long result = 0;
    for(int i = 0; i < 2000000000; i++)
        result += i;
    qDebug()<<"thread id = "<<QThread::currentThreadId();
    emit returnResult(result);  //将结果放在信号中

}
