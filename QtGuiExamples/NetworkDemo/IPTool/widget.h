#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnGetLocalIP_clicked();

    void on_btnGetWebIP_clicked();

    void on_btnCheckWeb_clicked();

private:
    Ui::Widget *ui;

    bool IPLive(QString ip, int port);
    QString GetHtml(QString url);
    QString GetNetIP(QString webCode);

};

#endif // WIDGET_H
