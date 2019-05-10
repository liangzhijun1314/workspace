#ifndef THREAD_H
#define THREAD_H

#include <QThread>

#include <QThread>

class Thread : public QThread{
    Q_OBJECT

public:
    Thread();  //构造函数

signals:
    void returnResult(long);

protected:
    void run();
};
#endif // THREAD_H
