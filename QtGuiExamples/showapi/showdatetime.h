#ifndef SHOWDATETIME_H
#define SHOWDATETIME_H

#include <QObject>
#include <QMutex>
#include <QtGui>
#include <QLabel>
#include <QLCDNumber>

//class QLabel;
//class QLCDNumber;
//class QTimer;

class ShowDateTime : public QObject
{
    Q_OBJECT
public:
    explicit ShowDateTime(QObject *parent = 0);
    static ShowDateTime *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new ShowDateTime;
            }
        }

        return self;
    }

    void SetLab(QLabel *labDateTime, QLabel *labLive);
    void SetLcdNumber(QLCDNumber *lcdNumber);
    void Start(int interval);
    void Stop();

private:
    static ShowDateTime *self;

    int day;                //天数
    int hour;               //时钟数
    int minute;             //分钟数
    int seconds;            //秒钟数
    QTimer *timer;          //定时器获取时间
    QLabel *labDateTime;    //显示日期时间的载体
    QLabel *labLive;        //显示已运行
    QLCDNumber *lcdNumber;  //显示日期时间的LCD控件

private slots:
    void SetTimeInfo();
    void ShowTime();
};

#endif // SHOWDATETIME_H
