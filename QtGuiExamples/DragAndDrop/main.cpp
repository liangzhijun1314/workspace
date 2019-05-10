#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>
#include <QElapsedTimer>
#include <QDateTime>
#include <QObject>
//#include <QMessageLogContext>  // 仅Qt5

//myMessageOutput  Qt5中可以把打印信息重定向到文件中
//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    // 加锁
//    static QMutex mutex;
//    mutex.lock();
//    QByteArray localMsg = msg.toLocal8Bit();

//    QString strMsg("");
//    switch(type)
//    {
//    case QtDebugMsg:
//        strMsg = QString("Debug:");  //调试信息提示
//        break;
//    case QtWarningMsg:
//        strMsg = QString("Warning:");//一般的警告提示
//        break;
//    case QtCriticalMsg:
//        strMsg = QString("Critical:");//严重错误提示
//        break;
//    case QtFatalMsg:
//        strMsg = QString("Fatal:");//致命错误提示
//        break;
//    }

//    // 设置输出信息格式
//    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");

//    //Message:%1 File:%2 Line:%3 Function:%4 DateTime:%5
//    QString strMessage = QString("Message:%1   DateTime:%2")
//            .arg(localMsg.constData())/*.arg(context.file).arg(context.line).arg(context.function)*/.arg(strDateTime);

//    // 输出信息至文件中（读写、追加形式）
//    QFile file("log.txt");
//    file.open(QIODevice::ReadWrite | QIODevice::Append);
//    QTextStream stream(&file);
//    stream << strMessage << "\r\n";
//    file.flush();
//    file.close();

//    // 解锁
//    mutex.unlock();
//}

//  Qt4 中重定向输出信息到文件中
void customMessageHandler(QtMsgType type,const char *msg)
{
    // 加锁
    //使用QMutex进行加锁、解锁操作，便于我们可以安全的在多线程操作中使用
    static QMutex mutex;
    mutex.lock();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:%1").arg(msg);  //调试信息提示
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:%1").arg(msg);//一般的警告提示
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:%1").arg(msg);//严重错误提示
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:%1").arg(msg);//致命错误提示
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");

    QString strMessage = QString("DateTime:%1---%2 ")
            .arg(strDateTime).arg(strMsg);

    // 输出信息至文件中（读写、追加形式）
    QFile file("log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);//（读写、追加模式）
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

// 安装消息处理程序  重定向输出信息
//    qInstallMsgHandler(customMessageHandler); // Qt4 OK
//    qInstallMessageHandler(myMessageOutput);  //Qt5
    qDebug("This is a debug message.");
    qWarning("This is a warning message.");
    qCritical("This is a critical message.");
//    qFatal("This is a fatal message.");  //致命错误提示  加上该句会出现错误
//

//实现启动界面 目的加个延时
    QPixmap pixmap("screen.png");
    QSplashScreen screen(pixmap);
    screen.show();
    screen.showMessage(QObject::tr("QSplashScreen启动画面"),Qt::AlignCenter,Qt::red);

    // 下面俩种方式都可以，另外构造函数中的方式也可以
#if 0
    int delayTime = 5;
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < (delayTime * 1000)){
        a.processEvents();
    }
#endif

#if 0
    QDateTime n = QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
        a.processEvents();
    }while(n.secsTo(now)<=5);//5为需要延时的秒数

#endif
//
    MainWindow w;
    w.show();
    screen.finish(&w);

    return a.exec();
}
