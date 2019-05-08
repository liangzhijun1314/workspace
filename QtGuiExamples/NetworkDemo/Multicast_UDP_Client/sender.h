/*******************************************************************************
** @file:     sender.h
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-4-10
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#ifndef SENDER_H
#define SENDER_H

#include <QDialog>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QPushButton;
class QTimer;
class QUdpSocket;
class QSpinBox;
QT_END_NAMESPACE

class Sender : public QDialog
{
    Q_OBJECT

public:
    Sender(QWidget *parent = 0);
    ~Sender();
private slots:
    void ttlChanged(int newTtl);
    void startSending();
    void sendDatagram();

private:
    QLabel *statusLabel;
    QLabel *ttlLabel;
    QSpinBox *ttlSpinBox;
    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QUdpSocket *udpSocket;
    QTimer *timer;
    QHostAddress groupAddress;
    int messageNo;
};

#endif // SENDER_H
