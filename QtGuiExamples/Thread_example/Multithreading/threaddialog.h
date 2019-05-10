#ifndef THREADDIALOG_H
#define THREADDIALOG_H

#include <QDialog>
#include "thread.h"
#include <QPushButton>
#include <QMap>

class Thread;
class ThreadDialog : public QDialog
{
    Q_OBJECT
    
public:
    ThreadDialog(QWidget *parent = 0);
    ~ThreadDialog();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void startOrStopThreadA();
    void startOrStopThreadB();
    void close();

    void startOrStopThread();
private:
    Thread threadA;
    Thread threadB;
    QPushButton *threadAButton;
    QPushButton *threadBButton;
    QPushButton *quitButton;
    QMap<QPushButton *,Thread *> mappingTable;
};

#endif // THREADDIALOG_H
