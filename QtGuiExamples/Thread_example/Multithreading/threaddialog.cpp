#include "threaddialog.h"
#include <QCloseEvent>
#include <QVBoxLayout>
ThreadDialog::ThreadDialog(QWidget *parent)
    : QDialog(parent)
{

    threadA.setMessage("A");
    threadB.setMessage("B");
    setWindowTitle("Multithread");
    threadAButton = new QPushButton(tr("Start A"),this);
    threadBButton = new QPushButton(tr("Start B"),this);
    quitButton = new QPushButton(tr("Quit"),this);
    quitButton->setDefault(true);
    connect(threadAButton, SIGNAL(clicked()),this, SLOT(startOrStopThreadA()));
    connect(threadBButton, SIGNAL(clicked()),this, SLOT(startOrStopThreadB()));
    connect(quitButton, SIGNAL(clicked()),this, SLOT(close()));
    QVBoxLayout *widgetLayout = new QVBoxLayout(this);
    widgetLayout->addWidget(threadAButton);
    widgetLayout->addWidget(threadBButton);
    widgetLayout->addWidget(quitButton);



//    QPushButton *buttonQuit = new QPushButton(QString::fromLocal8Bit("Quit"));
//    connect(buttonQuit,SIGNAL(clicked()),this, SLOT(close()));

//    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight, this);

//    QStringList list = QString("ABCDEFGHIJKLMN").split("",QString::SkipEmptyParts);

//    foreach (QString name, list)
//    {
//        Thread *thread = new Thread(name, this);
//        QPushButton *button = new QPushButton(QString("Start ")+name, this);
//        mappingTable.insert(button, thread);
//        thread->setMessage(name);
//        connect(button, SIGNAL(clicked()),this, SLOT(startOrStopThread()));
//        layout->addWidget(button);
//    }

//    layout->addWidget(buttonQuit);
//    this->setLayout(layout);

}

ThreadDialog::~ThreadDialog()
{
    
}

void ThreadDialog::closeEvent(QCloseEvent *event)
{
    threadA.stop();
    threadB.stop();
    threadA.wait();
    threadB.wait();
    event->accept();
}

void ThreadDialog::startOrStopThreadA()
{
    if (threadA.isRunning()) {
        threadAButton->setText(tr("Stop A"));
        threadA.stop();
        threadAButton->setText(tr("Start A"));
    } else {
        threadAButton->setText(tr("Start A"));
        threadA.start();
        threadAButton->setText(tr("Stop A"));
    }
}

void ThreadDialog::startOrStopThreadB()
{
    if (threadB.isRunning()) {
        threadBButton->setText(tr("Stop B"));
        threadB.stop();
        threadBButton->setText(tr("Start B"));
    } else {
        threadBButton->setText(tr("Start B"));
        threadB.start();
        threadBButton->setText(tr("Stop B"));
    }

}

void ThreadDialog::close()
{
    exit(0);
}

void ThreadDialog::startOrStopThread()
{
    QPushButton *buttonNow = dynamic_cast<QPushButton*>(sender());
    Thread *threadNow = (Thread*)mappingTable[buttonNow];

    if (threadNow == NULL) return;

    if(threadNow->isRunning())
    {
        threadNow->stop();
        buttonNow->setText( buttonNow->text().replace(QString("Stop"),QString("Start")) );
    }
    else
    {
        threadNow->start();
        buttonNow->setText( buttonNow->text().replace(QString("Start"),QString("Stop")) );
    }
}
