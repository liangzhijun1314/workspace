#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();
protected:
    void run();  //重新实现run函数
};

#endif // WORKTHREAD_H
