#include "networker.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>

NetWorker *NetWorker::instance()
{
    static NetWorker netWorker; // C++ ����ģʽ�����д��
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
    //��QNetworkAccessManager����finished()�ź�ʱ��NetWorkerͬ���ᷢ���Լ���finished()�ź�
}

//NetWorker::NetWorker(const NetWorker &)
//{

//}

//NetWorker &NetWorker::operator=(NetWorker rhs)
//{

//}
