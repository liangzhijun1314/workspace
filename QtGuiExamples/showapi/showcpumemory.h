#ifndef SHOWCPUMEMORY_H
#define SHOWCPUMEMORY_H

#include <QObject>
#include <QtGui>
#include <QMutex>
#include <QTimer>
#include <QProcess>
#include <QLabel>

//class QLabel;
//class QTimer;
//class QProcess;

class ShowCPUMemory : public QObject
{
    Q_OBJECT
public:
    explicit ShowCPUMemory(QObject *parent = 0);
    static ShowCPUMemory *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new ShowCPUMemory;
            }
        }

        return self;
    }

    void SetLab(QLabel *labCPUMemory);
    void Start(int interval);
    void Stop();

private:
    static ShowCPUMemory *self;

    int totalNew, idleNew, totalOld, idleOld;
    int cpuPercent;

    int memoryPercent;
    int memoryAll;
    int memoryUse;
    int memoryFree;

    QTimer *timerCPU;       //定时器获取CPU信息
    QTimer *timerMemory;    //定时器获取内存信息
    QLabel *labCPUMemory;   //显示CPU内存信息的控件
    QProcess *process;

private slots:
    void GetCPU();
    void GetMemory();
    void ReadData();
};

#endif // SHOWCPUMEMORY_H
