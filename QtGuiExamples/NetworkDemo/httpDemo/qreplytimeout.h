/*******************************************************************************
** @file:     qreplytimeout.h
** @class:    QReplyTimeout
** @brief:    //�������糬ʱ���� ,�ο���ַhttp://blog.csdn.net/liang19890820/article/details/53204396
** ʹ�÷�ʽeg:
**      QNetworkAccessManager *pManger = new QNetworkAccessManager(this);
**      QNetworkReply *pReply = pManger->get(QNetworkRequest(QUrl("https://www.google.com")));
**      QReplyTimeout *pTimeout = new QReplyTimeout(pReply, 1000);
**      // ��ʱ��һ������
**      connect(pTimeout, &QReplyTimeout::timeout, [=]() {
**          qDebug() << "Timeout";
**      });
**
** @author:   lzj
** @date:     2018-2-1
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/


#ifndef QREPLYTIMEOUT_H
#define QREPLYTIMEOUT_H

#include <QObject>
#include <QTimer>
#include <QNetworkReply>

class QReplyTimeout : public QObject
{
    Q_OBJECT
public:
    QReplyTimeout(QNetworkReply *reply, const int timeout) : QObject(reply) {
        Q_ASSERT(reply);
        if (reply && reply->isRunning()) {  // �������ζ�ʱ��
            QTimer::singleShot(timeout, this, SLOT(onTimeout()));
        }
    }

signals:
    void timeout();  // ��ʱ�ź� - ����һ������

private slots:
    void onTimeout() {  // ����ʱ
        QNetworkReply *reply = static_cast<QNetworkReply*>(parent());
        if (reply->isRunning()) {
            reply->abort();
            reply->deleteLater();
            emit timeout();
        }
    }
};

#endif // QREPLYTIMEOUT_H
