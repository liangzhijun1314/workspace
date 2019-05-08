#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QWidget>
#include <QUrl>

namespace Ui {
class HttpDownload;
}
class QTime;
class DownLoadManager;
class HttpDownload : public QWidget
{
    Q_OBJECT

public:
    explicit HttpDownload(QWidget *parent = 0);
    ~HttpDownload();
private:
    void initWindow();

private slots:
    void on_pButtonStart_clicked();

    void on_pButtonStop_clicked();

    void on_pButtonClose_clicked();
    void onDownloadProcess(qint64 bytesReceived,qint64 bytesTotal);
    void onReplyFinished(int );
    QString transformUnit(qint64 bytes , bool isSpeed=true);
    QString transformTime(qint64 seconds);
signals:
    void signalDownloadProcess(qint64,qint64);
    void signalReplyFinished(int statusCode);
private:
    Ui::HttpDownload *ui;

    DownLoadManager *m_downloadManager;
    QString m_url;
    qint64  m_timeInterval;
    qint64  m_currentDownload;
    qint64  m_intervalDownload;
//    QTime  m_timeRecord;
};

#endif // HTTPDOWNLOAD_H
