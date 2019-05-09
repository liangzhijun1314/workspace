/*******************************************************************************
** @file:     clock.h
** @class:    Clock
** @brief:    //模拟时钟
** Detailed description
**
** @author:   lzj
** @date:     2018-2-5
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QSoundEffect>
#include <QToolTip>
#include <QSystemTrayIcon>

class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = 0);
    ~Clock();

private slots:
    void slot_showMaxiNormal();
    void slot_EffectControl();

private:
    static const QPoint hourHand[4];
    static const QPoint minuteHand[4];
    static const QPoint secondHand[4];

    QPen mHourHandPen;
    QPen mMinuteHandPen;
    QPen mSecondHandPen;

    QPoint mPos;

    // 右键菜单
    QMenu *m_pRBMenu;
    QAction *m_pCloseAct;
    QAction *m_pMaxiMinimizeAct;

    // 音效控制菜单
    QMenu *m_pSDMenu;
    QAction *m_pSoundOffAct;
    QAction *m_pSoundOnAct;

    QSoundEffect *m_pEffect;

    QStringList m_fontList;

    QSystemTrayIcon *systemTray;

protected:
    void paintEvent(QPaintEvent *event);
    void drawHourHand(QPainter *painter);
    void drawMinuteHand(QPainter *painter);
    void drawSecondHand(QPainter *painter);
    void drawLcdNumber(QPainter *painter);
    void drawClockDial(QPainter *painter);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void createMenu();
    void createTray();
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // CLOCK_H
