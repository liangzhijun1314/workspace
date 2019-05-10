#include "threaddlg.h"
#include <QHBoxLayout>

ThreadDlg::ThreadDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("thread"));

    startBtn = new QPushButton(tr("start"));
    stopBtn = new QPushButton(tr("stop"));
    quitBtn = new QPushButton(tr("exit"));

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(startBtn);
    mainLayout->addWidget(stopBtn);
    mainLayout->addWidget(quitBtn);

    connect(startBtn, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(stopBtn, SIGNAL(clicked()), this, SLOT(slotStop()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ThreadDlg::~ThreadDlg()
{

}

void ThreadDlg::slotStart()
{
    for(int i=0;i<MAXSIZE;i++)
    {
        workThread[i] = new WorkThread();
    }
    for(int i=0;i<MAXSIZE;i++)
    {
        workThread[i]->start();
    }
    startBtn->setEnabled(false);
    stopBtn->setEnabled(true);
}

void ThreadDlg::slotStop()
{
    for(int i=0;i<MAXSIZE;i++)
    {
        workThread[i]->terminate();  //强制结束线程
        workThread[i]->wait();  //将一个线程挂起，直到超时或者该线程被唤醒。
    }
    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
}
