#include "workthread.h"
#include <QDebug>

WorkThread::WorkThread()
{
}

void WorkThread::run()
{
    while(true)
    {
        for(int n=0;n<10;n++)
            qDebug()<<n<<n<<n<<n<<n<<n<<n<<n;  //为了效果明显，每个数字打印8次
    }
}
