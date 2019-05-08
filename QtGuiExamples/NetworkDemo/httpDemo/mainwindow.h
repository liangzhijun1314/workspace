#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class QNetworkReply;
class QNetworkAccessManager;
class QFile;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRequest(QUrl url);
    void InitRequest();

private slots:
    void replyFinished(QNetworkReply *reply);
    void on_pushButton_clicked();
    void slotReadyRead();
    void slotFinished();
    void updateDateReadProgress(qint64 bytesRead, qint64 totalBytes);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;
};

#endif // MAINWINDOW_H
