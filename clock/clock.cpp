/*******************************************************************************
** @file:     clock.cpp
** @class:    Clock
** @brief:    //Short description
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

#include "clock.h"
#include <QTimer>
#include <QIcon>
#include <QTime>
#include <QFont>
#include <QCoreApplication>
#include <QFontDatabase>

const QPoint Clock::hourHand[4] = {
    QPoint(3, 5),
    QPoint(0, 13),
    QPoint(-3, 5),
    QPoint(0, -40)
}; // 时针绘图区域
const QPoint Clock::minuteHand[4] = {
    QPoint(3, 5),
    QPoint(0, 16),
    QPoint(-3, 5),
    QPoint(0, -68)
}; // 分针绘图区域
const QPoint Clock::secondHand[4] = {
    QPoint(3, 5),
    QPoint(0, 18),
    QPoint(-3, 5),
    QPoint(0, -85)
}; // 秒针绘图区域

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);// 去掉标题栏,去掉任务栏显示，窗口置顶
    this->setWindowIcon(QIcon(":/clock.ico"));
    this->setWindowTitle( QString::fromLocal8Bit("桌面时钟") );
    this->resize(200, 200);
    this->setAttribute(Qt::WA_TranslucentBackground, true);// 窗口透明，去掉标题栏后方生效
    /* 加载外部字体文件 */
    m_fontList.clear();
    int lcdFontId = QFontDatabase::addApplicationFont(":/lcd/DS-DIGI.ttf"); // 从source资源文件
    if (lcdFontId != -1)
    {
        m_fontList << QFontDatabase::applicationFontFamilies(lcdFontId);
    }

    /* 画笔设置 */
    mHourHandPen = QPen(palette().foreground(), 2.0);
    mMinuteHandPen = QPen(palette().foreground(), 1.0);

    QTimer *pTimer = new QTimer(this);
    pTimer->start(1000);
    connect( pTimer, SIGNAL(timeout()), this, SLOT(update()) );

    /* 音效控制 */
    //    QString dir = QCoreApplication::applicationDirPath();
    //    QString filename(dir + "/sounds/clockMoveSound.wav");
    m_pEffect = new QSoundEffect(this);
    m_pEffect->setLoopCount(QSoundEffect::Infinite); // 循环播放
    //    m_pEffect->setSource( QUrl::fromLocalFile(filename) );
    m_pEffect->setSource( QUrl::fromLocalFile(":/sound/clockMoveSound.wav") );
    m_pEffect->setVolume(1.0); // 音量控制：0.0-1.0
    //    m_pEffect->play(); // 播放
    //    m_pEffect->stop(); // 停止

    /* 创建右键菜单 */
    createMenu();

    /* 创建系统托盘项 */
    createTray();
}

Clock::~Clock()
{
    delete m_pRBMenu;
    delete m_pCloseAct;
    delete m_pMaxiMinimizeAct;
    delete m_pSoundOnAct;
    delete m_pSoundOffAct;
    delete m_pEffect;
}
/* 右键菜单槽函数 */
void Clock::slot_showMaxiNormal()
{
    if (this->isFullScreen())
    {
        this->showNormal();
        m_pMaxiMinimizeAct->setText( QString::fromLocal8Bit("全屏") );
        m_pMaxiMinimizeAct->setIcon( QIcon(":/ico/fullscreen.ico") );
        return;
    }
    else
    {
        this->showFullScreen();
        m_pMaxiMinimizeAct->setText( QString::fromLocal8Bit("还原") );
        m_pMaxiMinimizeAct->setIcon( QIcon(":/ico/exitfullscreen.ico") );
        return;
    }
}
/* 音效控制槽函数 */
void Clock::slot_EffectControl()
{
    if ( m_pEffect->isPlaying() )
    {
        m_pEffect->stop();
        m_pSoundOffAct->setIcon( QIcon(":/ico/check.ico") );
        m_pSoundOnAct->setIcon( QIcon(":/ico/nocheck.ico") );
        return;
    }
    else
    {
        m_pSoundOnAct->setIcon( QIcon(":/ico/check.ico") );
        m_pSoundOffAct->setIcon( QIcon(":/ico/nocheck.ico") );

        QTime now;
        do{
            now = QTime::currentTime();
        }while(now.msec() >= 50 && now.msec() <= 950); // 音效对时

        m_pEffect->play();
        return;
    }
}
/* 重写绘图事件 */
void Clock::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QFont font("Microsoft Yahei", 10, 75); // 字体，大小，加粗等同于QFont::Bold
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing, true); //反锯齿
    //    painter.setWindow(0, 0, 200, 200);

    int side = qMin(this->width(), this->height());

    /* 圆形背景的绘制 */
    painter.setPen(Qt::NoPen); // 去掉外圈线
    painter.setBrush(QColor(255, 255, 255, 125));              // 背景颜色以及透明度
    painter.drawEllipse( QPoint(width()/2, height()/2), side/2, side/2 ); // 绘制背景

    painter.setPen(QPen( QColor(233, 233, 216 ), 4 )); // 外边框颜色以及大小
    painter.drawEllipse(QPoint(width()/2, height()/2), side/2 - 3, side/2 - 3); //外边框绘制

    painter.translate(width() / 2, height() / 2); // 设置坐标原点
    painter.scale(side / 200.0, side / 200.0); // 缩放比例

    /* 时针、分针、秒针、表盘、Lcd */
    drawHourHand(&painter);
    drawMinuteHand(&painter);
    drawSecondHand(&painter);
    drawClockDial(&painter);
    drawLcdNumber(&painter);

    /* 中心点 */
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0, 0), 2, 2);
}

void Clock::drawHourHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->save();
    painter->rotate( 30.0 * (time.hour() + time.minute()/60.0) ); //坐标轴旋转
    painter->drawConvexPolygon(hourHand, 4); // 绘制凸多边形，由n个点控制，此处由4个点控制
    painter->restore(); //复位坐标
}

void Clock::drawMinuteHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);
    painter->save();
    painter->rotate( 6.0 * (time.minute() + time.second()/60.0) );
    painter->drawConvexPolygon(minuteHand, 4);
    painter->restore(); //复位坐标
}

void Clock::drawSecondHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->save();
    painter->rotate( 6.0 * time.second() );
    painter->drawConvexPolygon(secondHand, 4);
    painter->restore();
}

void Clock::drawLcdNumber(QPainter *painter)
{
    if (!m_fontList.isEmpty()) {
        QFont font;
        font.setFamily(m_fontList.at(0));
        font.setPointSize(15);
        // font.setStretch(side / 200.0);
        painter->setFont(font);
    }
    painter->setPen( QColor(0, 0, 0) );
    painter->drawText( -40, 34, 80, 22, Qt::AlignCenter,
                       QTime::currentTime().toString("hh:mm:ss") );

    //    painter->setBrush(Qt::NoBrush);
    //    painter->drawRect(-40, 34, 80, 22);
    //     坐标系统：向右为X轴正方向，向下为Y轴正方向
}
// 表盘和数字
void Clock::drawClockDial(QPainter *painter)
{
    for (int i = 1; i <= 60; i++) {
        painter->save();
        painter->rotate(6*i); // 坐标轴旋转6*i度

        if ( (i % 5 == 0) && (i <= 15 || i >= 45) ) { // 小时刻度和数字
            painter->setPen(mHourHandPen);
            painter->drawLine(0, -95, 0, -80);
            painter->drawText(-20, -82, 40, 40,
                              Qt::AlignHCenter | Qt::AlignTop,
                              QString::number(i/5) );
            if (i < 15 || i > 45) { // 解决下半部分数字倒转问题

                painter->drawLine(0, 80, 0, 95);
                painter->drawText( -20, 41, 40, 40,
                                   Qt::AlignHCenter | Qt::AlignBottom,
                                   QString::number(i<15 ? i/5+6 : i/5-6) );
            }
        } else { // 分钟刻度
            painter->setPen(mMinuteHandPen);
            painter->drawLine(0, 95, 0, 90);
        }

        painter->restore();
    }//for
}
/* 实现窗口拖动 */
void Clock::mousePressEvent(QMouseEvent *event)
{
    mPos = (event->globalPos()) - (this->pos()); //按下点 - 未按下时的点
}

void Clock::mouseMoveEvent(QMouseEvent *event)
{
    if (this->isFullScreen() == false) {
        this->move(event->globalPos() - mPos );
    }
}
/* 重写滚轮事件，实现放大缩小 */
void Clock::wheelEvent(QWheelEvent *event)
{
    QRect tmp = this->geometry();
    QPoint centerPoint = tmp.center(); // 储存中心点坐标

    static int adjustSize = 20;

    if (event->delta() > 0) // 放大
    {
        tmp.setWidth(tmp.width() + adjustSize);
        tmp.setHeight(tmp.height() + adjustSize);
    }
    else // 缩小
    {
        tmp.setWidth(tmp.width() - adjustSize);
        tmp.setHeight(tmp.height() - adjustSize);
    }

    if (tmp.width() > 20) // 限制最小尺寸
    {
        tmp.moveCenter(centerPoint); // 从中心缩放而非左上角处
        this->setGeometry(tmp);

        // 设置toolTip
        double percent = (double)tmp.width() / 200.0;
        QString percentStr = QString::number(percent*100) + "%";
        QToolTip::showText(QCursor::pos(), percentStr, this, QRect(), 500);
    }
}

void Clock::createMenu()
{
    m_pRBMenu = new QMenu(this);

    m_pCloseAct = new QAction(this);
    m_pCloseAct->setIcon( QIcon(":/ico/closeBt.ico") );
    m_pCloseAct->setText( QString::fromLocal8Bit("关闭") );

    m_pMaxiMinimizeAct = new QAction(this);
    m_pMaxiMinimizeAct->setText( QString::fromLocal8Bit("全屏") );
    m_pMaxiMinimizeAct->setIcon( QIcon(":/ico/fullscreen.ico") );

    m_pRBMenu->addAction(m_pCloseAct);
    m_pRBMenu->addSeparator();
    m_pRBMenu->addAction(m_pMaxiMinimizeAct);

    connect (m_pCloseAct, SIGNAL(triggered(bool)), qApp, SLOT(quit()) );

    connect( m_pMaxiMinimizeAct, SIGNAL(triggered(bool)),
             this, SLOT( slot_showMaxiNormal() ) );

    /* 二级菜单 */
    m_pRBMenu->addSeparator();
    m_pSDMenu = m_pRBMenu->addMenu( QIcon(":/ico/sound.ico"), QString::fromLocal8Bit("音效控制") );

    m_pSoundOnAct = new QAction(this);
    m_pSoundOnAct->setText( QString::fromLocal8Bit("音效开") );
    m_pSoundOnAct->setIcon( QIcon(":/ico/nocheck.ico") );
    m_pSoundOffAct = new QAction(this);
    m_pSoundOffAct->setText( QString::fromLocal8Bit("音效关") );
    m_pSoundOffAct->setIcon( QIcon(":/ico/check.ico") );

    m_pSDMenu->addAction(m_pSoundOnAct);
    m_pSDMenu->addAction(m_pSoundOffAct);

    connect (m_pSoundOnAct, SIGNAL(triggered(bool)),
             this, SLOT( slot_EffectControl() ) );
    connect( m_pSoundOffAct, SIGNAL(triggered(bool)),
             this, SLOT( slot_EffectControl() ) );
}
/* 创建系统托盘 */
void Clock::createTray()
{
    /* 托盘图标 */
    systemTray = new QSystemTrayIcon(this);
    systemTray->setToolTip( QString::fromLocal8Bit("桌面时钟") );
    systemTray->setIcon(QIcon(":/ico/clock.ico"));
    systemTray->show();

    /* 托盘菜单 */
    systemTray->setContextMenu(m_pRBMenu); // 与右键菜单类似，QMenu类

    /* 托盘消息 */
    //    systemTray->showMessage(tr("TiTle"), tr("msg"), QIcon("://msgIco.ico"), 1000); // 标题，消息内容，消息图标，持续时间
}
/* 重写右键菜单响应事件 */
void Clock::contextMenuEvent(QContextMenuEvent *event)
{
    m_pRBMenu->exec(QCursor::pos()); // 在光标处弹出右键菜单
    event->accept();
}
