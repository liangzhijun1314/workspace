#ifndef NETWORKER_H
#define NETWORKER_H

//�� QNetworkAccessManager�����˼򵥵ķ�װ
#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class QNetworkReply;



//����ģʽ
//Ҫ���캯�����������캯���͸�ֵ���������˽�е�
class NetWorker : public QObject
{
    Q_OBJECT
public:
    static NetWorker *instance();//��һ��instance()�������������Ψһ��ʵ��
    ~NetWorker();
//    void get(const QString &url);
    QNetworkReply *get(const QString &url);
signals:
    void finished(QNetworkReply *reply);
private:
    class Private;//������һ��NetWorker���ڲ���
    friend class Private;
    Private *d;//����������ڲ���� d ָ��,d ָ���� C++ �����õ�һ�����ģʽ,������й�

    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;//������� Qt5 �����ӵģ���˼�ǽ��������εĺ�������Ϊ deleted������ C++11 �������ԣ�
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
