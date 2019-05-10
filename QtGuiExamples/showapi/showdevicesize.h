#ifndef SHOWDEVICESIZE_H
#define SHOWDEVICESIZE_H

#include <QObject>
#include <QtGui>
#include <QMutex>
#include <QProcess>
#include <QTableWidget>

//class QTableWidget;
//class QProcess;

class ShowDeviceSize : public QObject
{
    Q_OBJECT
public:
    explicit ShowDeviceSize(QObject *parent = 0);
    static ShowDeviceSize *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new ShowDeviceSize;
            }
        }

        return self;
    }

    void SetTableWidget(QTableWidget *tableWidget);
    void Load();

private:
    static ShowDeviceSize *self;
    QTableWidget *tableWidget;
    QProcess *process;

private slots:
    void ReadData();
    void CheckSize(QString result, QString name);
    void InsertSize(QString name, QString use, QString free, QString all, int percent);

signals:

public slots:
};

#endif // SHOWDEVICESIZE_H
