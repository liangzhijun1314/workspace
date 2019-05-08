#ifndef NETWORKER_H
#define NETWORKER_H

//将 QNetworkAccessManager进行了简单的封装
#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class QNetworkReply;



//单例模式
//要求构造函数、拷贝构造函数和赋值运算符都是私有的
class NetWorker : public QObject
{
    Q_OBJECT
public:
    static NetWorker *instance();//有一个instance()函数用来获得这唯一的实例
    ~NetWorker();
//    void get(const QString &url);
    QNetworkReply *get(const QString &url);
signals:
    void finished(QNetworkReply *reply);
private:
    class Private;//声明了一个NetWorker的内部类
    friend class Private;
    Private *d;//声明了这个内部类的 d 指针,d 指针是 C++ 程序常用的一种设计模式,与编译有关

    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;//这个宏是 Qt5 新增加的，意思是将它所修饰的函数声明为 deleted（这是 C++11 的新特性）
    NetWorker& operator=(NetWorker rhs) Q_DECL_EQ_DELETE;//
};


class NetWorker :: Private
{
public:
    Private(NetWorker *q) :
        manager(new QNetworkAccessManager(q))
    {}
    QNetworkAccessManager *manager;
};

#endif // NETWORKER_H
