#include "networker.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>

NetWorker *NetWorker::instance()
{
    static NetWorker netWorker; // C++ 单例模式的最简单写法
    return &netWorker;
}

NetWorker::~NetWorker()
{
    delete d;
    d = 0;
}

//void NetWorker::get(const QString &url)
//{
//    d->manager->get(QNetworkRequest(QUrl(url)));
//}

QNetworkReply *NetWorker::get(const QString &url)
{
    return d->manager->get(QNetworkRequest(QUrl(url)));
}

NetWorker::NetWorker(QObject *parent) :
    QObject(parent),
    d(new NetWorker::Private(this))
{
    connect(d->manager,&QNetworkAccessManager::finished,
            this,&NetWorker::finished);
    //当QNetworkAccessManager发出finished()信号时，NetWorker同样会发出自己的finished()信号
}

//NetWorker::NetWorker(const NetWorker &)
//{

//}

//NetWorker &NetWorker::operator=(NetWorker rhs)
//{

//}
