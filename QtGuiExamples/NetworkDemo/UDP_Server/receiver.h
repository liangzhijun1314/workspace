/*******************************************************************************
** @file:     receiver.h
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

#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QUdpSocket;
class QAction;
QT_END_NAMESPACE

class Receiver : public QWidget
{
    Q_OBJECT

public:
    Receiver(QWidget *parent = 0);
    ~Receiver();
    void widgetLayout();
private slots:
    void readPendingDatagrams();

private:
    QLabel      *statusLabel;
    QPushButton *quitButton;
    QUdpSocket  *udpSocket;  
};

#endif // RECEIVER_H
