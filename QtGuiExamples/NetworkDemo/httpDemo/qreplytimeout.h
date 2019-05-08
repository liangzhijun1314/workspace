/*******************************************************************************
** @file:     qreplytimeout.h
** @class:    QReplyTimeout
** @brief:    //处理网络超时的类 ,参考网址http://blog.csdn.net/liang19890820/article/details/53204396
** 使用方式eg:
**      QNetworkAccessManager *pManger = new QNetworkAccessManager(this);
**      QNetworkReply *pReply = pManger->get(QNetworkRequest(QUrl("https://www.google.com")));
**      QReplyTimeout *pTimeout = new QReplyTimeout(pReply, 1000);
**      // 超时进一步处理
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
        if (reply && reply->isRunning()) {  // 启动单次定时器
            QTimer::singleShot(timeout, this, SLOT(onTimeout()));
        }
    }

signals:
    void timeout();  // 超时信号 - 供进一步处理

private slots:
    void onTimeout() {  // 处理超时
        QNetworkReply *reply = static_cast<QNetworkReply*>(parent());
        if (reply->isRunning()) {
            reply->abort();
            reply->deleteLater();
            emit timeout();
        }
    }
};

#endif // QREPLYTIMEOUT_H
