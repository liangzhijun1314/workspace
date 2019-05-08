#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class DownLoadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownLoadManager(QObject *parent = 0);
    ~DownLoadManager();

    void setDownInto(bool isSupportBreakPoint);
    QString getDownloadUrl();
    void downloadFile(QString url , QString fileName);
    void stopWork();
    void stopDownload();
    void reset();
    void removeFile(QString fileName);
    void closeDownload();

public slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onReadyRead();
    void onFinished();
    void onError(QNetworkReply::NetworkError code);
signals:
    void signalDownloadProcess(qint64 bytesReceived, qint64 bytesTotal);
    void signalReplyFinished(int);
    void signalDownloadError();
private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_reply;
    QUrl    m_url;
    QString m_fileName;
    bool    m_isSupportBreakPoint;
    qint64  m_bytesReceived;
    qint64  m_bytesTotal;
    qint64  m_bytesCurrentReceived;
    bool    m_isStop;
};

#endif // DOWNLOADMANAGER_H
