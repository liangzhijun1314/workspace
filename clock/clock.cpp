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
}; // ʱ���ͼ����
const QPoint Clock::minuteHand[4] = {
    QPoint(3, 5),
    QPoint(0, 16),
    QPoint(-3, 5),
    QPoint(0, -68)
}; // �����ͼ����
const QPoint Clock::secondHand[4] = {
    QPoint(3, 5),
    QPoint(0, 18),
    QPoint(-3, 5),
    QPoint(0, -85)
}; // �����ͼ����

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);// ȥ��������,ȥ����������ʾ�������ö�
    this->setWindowIcon(QIcon(":/clock.ico"));
    this->setWindowTitle( QString::fromLocal8Bit("����ʱ��") );
    this->resize(200, 200);
    this->setAttribute(Qt::WA_TranslucentBackground, true);// ����͸����ȥ������������Ч
    /* �����ⲿ�����ļ� */
    m_fontList.clear();
    int lcdFontId = QFontDatabase::addApplicationFont(":/lcd/DS-DIGI.ttf"); // ��source��Դ�ļ�
    if (lcdFontId != -1)
    {
        m_fontList << QFontDatabase::applicationFontFamilies(lcdFontId);
    }

    /* �������� */
    mHourHandPen = QPen(palette().foreground(), 2.0);
    mMinuteHandPen = QPen(palette().foreground(), 1.0);

    QTimer *pTimer = new QTimer(this);
    pTimer->start(1000);
    connect( pTimer, SIGNAL(timeout()), this, SLOT(update()) );

    /* ��Ч���� */
    //    QString dir = QCoreApplication::applicationDirPath();
    //    QString filename(dir + "/sounds/clockMoveSound.wav");
    m_pEffect = new QSoundEffect(this);
    m_pEffect->setLoopCount(QSoundEffect::Infinite); // ѭ������
    //    m_pEffect->setSource( QUrl::fromLocalFile(filename) );
    m_pEffect->setSource( QUrl::fromLocalFile(":/sound/clockMoveSound.wav") );
    m_pEffect->setVolume(1.0); // �������ƣ�0.0-1.0
    //    m_pEffect->play(); // ����
    //    m_pEffect->stop(); // ֹͣ

    /* �����Ҽ��˵� */
    createMenu();

    /* ����ϵͳ������ */
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
/* �Ҽ��˵��ۺ��� */
void Clock::slot_showMaxiNormal()
{
    if (this->isFullScreen())
    {
        this->showNormal();
        m_pMaxiMinimizeAct->setText( QString::fromLocal8Bit("ȫ��") );
        m_pMaxiMinimizeAct->setIcon( QIcon(":/ico/fullscreen.ico") );
        return;
    }
    else
    {
        this->showFullScreen();
        m_pMaxiMinimizeAct->setText( QString::fromLocal8Bit("��ԭ") );
        m_pMaxiMinimizeAct->setIcon( QIcon(":/ico/exitfullscreen.ico") );
        return;
    }
}
/* ��Ч���Ʋۺ��� */
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
        }while(now.msec() >= 50 && now.msec() <= 950); // ��Ч��ʱ

        m_pEffect->play();
        return;
    }
}
/* ��д��ͼ�¼� */
void Clock::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QFont font("Microsoft Yahei", 10, 75); // ���壬��С���Ӵֵ�ͬ��QFont::Bold
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing, true); //�����
    //    painter.setWindow(0, 0, 200, 200);

    int side = qMin(this->width(), this->height());

    /* Բ�α����Ļ��� */
    painter.setPen(Qt::NoPen); // ȥ����Ȧ��
    painter.setBrush(QColor(255, 255, 255, 125));              // ������ɫ�Լ�͸����
    painter.drawEllipse( QPoint(width()/2, height()/2), side/2, side/2 ); // ���Ʊ���

    painter.setPen(QPen( QColor(233, 233, 216 ), 4 )); // ��߿���ɫ�Լ���С
    painter.drawEllipse(QPoint(width()/2, height()/2), side/2 - 3, side/2 - 3); //��߿����

    painter.translate(width() / 2, height() / 2); // ��������ԭ��
    painter.scale(side / 200.0, side / 200.0); // ���ű���

    /* ʱ�롢���롢���롢���̡�Lcd */
    drawHourHand(&painter);
    drawMinuteHand(&painter);
    drawSecondHand(&painter);
    drawClockDial(&painter);
    drawLcdNumber(&painter);

    /* ���ĵ� */
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0, 0), 2, 2);
}

void Clock::drawHourHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->save();
    painter->rotate( 30.0 * (time.hour() + time.minute()/60.0) ); //��������ת
    painter->drawConvexPolygon(hourHand, 4); // ����͹����Σ���n������ƣ��˴���4�������
    painter->restore(); //��λ����
}

void Clock::drawMinuteHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);
    painter->save();
    painter->rotate( 6.0 * (time.minute() + time.second()/60.0) );
    painter->drawConvexPolygon(minuteHand, 4);
    painter->restore(); //��λ����
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
    //     ����ϵͳ������ΪX������������ΪY��������
}
// ���̺�����
void Clock::drawClockDial(QPainter *painter)
{
    for (int i = 1; i <= 60; i++) {
        painter->save();
        painter->rotate(6*i); // ��������ת6*i��

        if ( (i % 5 == 0) && (i <= 15 || i >= 45) ) { // Сʱ�̶Ⱥ�����
            painter->setPen(mHourHandPen);
            painter->drawLine(0, -95, 0, -80);
            painter->drawText(-20, -82, 40, 40,
                              Qt::AlignHCenter | Qt::AlignTop,
                              QString::number(i/5) );
            if (i < 15 || i > 45) { // ����°벿�����ֵ�ת����

                painter->drawLine(0, 80, 0, 95);
                painter->drawText( -20, 41, 40, 40,
                                   Qt::AlignHCenter | Qt::AlignBottom,
                                   QString::number(i<15 ? i/5+6 : i/5-6) );
            }
        } else { // ���ӿ̶�
            painter->setPen(mMinuteHandPen);
            painter->drawLine(0, 95, 0, 90);
        }

        painter->restore();
    }//for
}
/* ʵ�ִ����϶� */
void Clock::mousePressEvent(QMouseEvent *event)
{
    mPos = (event->globalPos()) - (this->pos()); //���µ� - δ����ʱ�ĵ�
}

void Clock::mouseMoveEvent(QMouseEvent *event)
{
    if (this->isFullScreen() == false) {
        this->move(event->globalPos() - mPos );
    }
}
/* ��д�����¼���ʵ�ַŴ���С */
void Clock::wheelEvent(QWheelEvent *event)
{
    QRect tmp = this->geometry();
    QPoint centerPoint = tmp.center(); // �������ĵ�����

    static int adjustSize = 20;

    if (event->delta() > 0) // �Ŵ�
    {
        tmp.setWidth(tmp.width() + adjustSize);
        tmp.setHeight(tmp.height() + adjustSize);
    }
    else // ��С
    {
        tmp.setWidth(tmp.width() - adjustSize);
        tmp.setHeight(tmp.height() - adjustSize);
    }

    if (tmp.width() > 20) // ������С�ߴ�
    {
        tmp.moveCenter(centerPoint); // ���������Ŷ������ϽǴ�
        this->setGeometry(tmp);

        // ����toolTip
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
    m_pCloseAct->setText( QString::fromLocal8Bit("�ر�") );

    m_pMaxiMinimizeAct = new QAction(this);
    m_pMaxiMinimizeAct->setText( QString::fromLocal8Bit("ȫ��") );
    m_pMaxiMinimizeAct->setIcon( QIcon(":/ico/fullscreen.ico") );

    m_pRBMenu->addAction(m_pCloseAct);
    m_pRBMenu->addSeparator();
    m_pRBMenu->addAction(m_pMaxiMinimizeAct);

    connect (m_pCloseAct, SIGNAL(triggered(bool)), qApp, SLOT(quit()) );

    connect( m_pMaxiMinimizeAct, SIGNAL(triggered(bool)),
             this, SLOT( slot_showMaxiNormal() ) );

    /* �����˵� */
    m_pRBMenu->addSeparator();
    m_pSDMenu = m_pRBMenu->addMenu( QIcon(":/ico/sound.ico"), QString::fromLocal8Bit("��Ч����") );

    m_pSoundOnAct = new QAction(this);
    m_pSoundOnAct->setText( QString::fromLocal8Bit("��Ч��") );
    m_pSoundOnAct->setIcon( QIcon(":/ico/nocheck.ico") );
    m_pSoundOffAct = new QAction(this);
    m_pSoundOffAct->setText( QString::fromLocal8Bit("��Ч��") );
    m_pSoundOffAct->setIcon( QIcon(":/ico/check.ico") );

    m_pSDMenu->addAction(m_pSoundOnAct);
    m_pSDMenu->addAction(m_pSoundOffAct);

    connect (m_pSoundOnAct, SIGNAL(triggered(bool)),
             this, SLOT( slot_EffectControl() ) );
    connect( m_pSoundOffAct, SIGNAL(triggered(bool)),
             this, SLOT( slot_EffectControl() ) );
}
/* ����ϵͳ���� */
void Clock::createTray()
{
    /* ����ͼ�� */
    systemTray = new QSystemTrayIcon(this);
    systemTray->setToolTip( QString::fromLocal8Bit("����ʱ��") );
    systemTray->setIcon(QIcon(":/ico/clock.ico"));
    systemTray->show();

    /* ���̲˵� */
    systemTray->setContextMenu(m_pRBMenu); // ���Ҽ��˵����ƣ�QMenu��

    /* ������Ϣ */
    //    systemTray->showMessage(tr("TiTle"), tr("msg"), QIcon("://msgIco.ico"), 1000); // ���⣬��Ϣ���ݣ���Ϣͼ�꣬����ʱ��
}
/* ��д�Ҽ��˵���Ӧ�¼� */
void Clock::contextMenuEvent(QContextMenuEvent *event)
{
    m_pRBMenu->exec(QCursor::pos()); // �ڹ�괦�����Ҽ��˵�
    event->accept();
}
