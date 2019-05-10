#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutexLocker>
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QString message = "",QObject *parent = 0);
    ~Thread();
    void setMessage(const QString &message);
    QString getMessage();
    void stop();
protected:
    void run();
    void printMessage();
private:
    QString messageStr;
    volatile bool stopped;  //stopped变量前面的volatile声明stopped为易失性变量，这样每次读取stopped时都是最新的值
    QMutex mutex;
    
};

#endif // THREAD_H
