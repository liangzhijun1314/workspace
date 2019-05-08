/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 重庆重邮汇测通信技术有限公司
 文 件 名 : widgetkeyboard.cpp --- WidgetKeyBoard
 作 者    : Niyh
 编写日期 : 2017
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
 倪又华    2017    1.0.0.0 1     文件创建
*******************************************************************/
#include "widgetkeyboard.h"

#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QPushButton>
#include <QDebug>

#define BORDER_COLOR        "#5DB6D6"
#define TEXT_COLOR          "#66CAEE"
#define BACKGROUND          "#1A1D20"


WidgetKeyboard::WidgetKeyboard(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setFixedSize(980, 410);
//    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    SetStyleSheet();

    InitButtons();
}

WidgetKeyboard::~WidgetKeyboard()
{
    for (int i = 0; i < 14; i++) {
        delete btnTop[i];
        delete btnTopNumber[i];
        delete btnLetterQp[i];

        if (i < 13) delete btnLetterAl[i];
        if (i < 12) delete btnLetterZm[i];

        if (i < 7) delete btnBottom[i];
        if (i < 4) delete btnDirection[i];
    }

    delete gridLayout;
    for (int i = 0; i < 6; i++) {
        delete horLyout[i];
    }
    delete verLayoutGlobal;
}

// 初始化按钮
void WidgetKeyboard::InitButtons()
{
    // 全局布局
    verLayoutGlobal = new QVBoxLayout(this);
    verLayoutGlobal->setContentsMargins(20, 20, 20, 20);
    verLayoutGlobal->setSpacing(5);

    // 6个水平布局
    for (int i = 0; i < 6; i++) {
        horLyout[i] = new QHBoxLayout();
        horLyout[i]->setSpacing(5);
        horLyout[i]->setContentsMargins(0, 0, 0, 0);
        verLayoutGlobal->addLayout(horLyout[i]);
    }

    ///////////////////////////////////////////////////////////////////////////////
    //顶部的F~F12
    for (int i = 0; i < 14; i++) {
        btnTop[i] = new QPushButton(this);
        btnTop[i]->setText(QString("F%1").arg(i));
        btnTop[i]->setFixedSize(60, 35);
        horLyout[0]->addWidget(btnTop[i]);
    }
    btnTop[0]->setText("Esc");
    btnTop[13]->setText("Quit");

    connect(btnTop[13], SIGNAL(clicked()), this, SLOT(hide()));

    ///////////////////////////////////////////////////////////////////////////////
    // 顶部数字按钮
    for (int i = 0; i < 14; i++) {
        btnTopNumber[i] = new QPushButton(this);
        btnTopNumber[i]->setFixedSize(60, 60);

        if (1 < i && i < 11) {
            btnTopNumber[i]->setProperty("btnType", "number");
        }

        horLyout[1]->addWidget(btnTopNumber[i]);
    }
    btnTopNumber[0]->setText("~\n`");
    btnTopNumber[1]->setText("!\n1");
    btnTopNumber[2]->setText("@\n2");
    btnTopNumber[3]->setText("#\n3");
    btnTopNumber[4]->setText("$\n4");
    btnTopNumber[5]->setText("%\n5");
    btnTopNumber[6]->setText("^\n6");
    btnTopNumber[7]->setText("&\n7");
    btnTopNumber[8]->setText("*\n8");
    btnTopNumber[9]->setText("(\n9");
    btnTopNumber[10]->setText(")\n0");

    btnTopNumber[11]->setText("-\n_");
    btnTopNumber[12]->setText("+\n=");
    btnTopNumber[13]->setFixedWidth(90);
    btnTopNumber[13]->setText("Backspace");

    ///////////////////////////////////////////////////////////////////////////////
    // 字母按钮Q~P
    for (int i = 0; i < 14; i++) {
        btnLetterQp[i] = new QPushButton(this);
        btnLetterQp[i]->setFixedSize(60, 60);

        if (1 < i && i < 11) {
            btnLetterQp[i]->setProperty("btnType", "letter");
        }

        horLyout[2]->addWidget(btnLetterQp[i]);
    }
    btnLetterQp[0]->setFixedWidth(90);
    btnLetterQp[0]->setText("tab");

    btnLetterQp[1]->setText(QString("%1").arg(QChar(Qt::Key_Q - Qt::Key_A + 'A')));
    btnLetterQp[2]->setText(QString("%1").arg(QChar(Qt::Key_W - Qt::Key_A + 'A')));
    btnLetterQp[3]->setText(QString("%1").arg(QChar(Qt::Key_E - Qt::Key_A + 'A')));
    btnLetterQp[4]->setText(QString("%1").arg(QChar(Qt::Key_R - Qt::Key_A + 'A')));
    btnLetterQp[5]->setText(QString("%1").arg(QChar(Qt::Key_T - Qt::Key_A + 'A')));
    btnLetterQp[6]->setText(QString("%1").arg(QChar(Qt::Key_Y - Qt::Key_A + 'A')));
    btnLetterQp[7]->setText(QString("%1").arg(QChar(Qt::Key_U - Qt::Key_A + 'A')));
    btnLetterQp[8]->setText(QString("%1").arg(QChar(Qt::Key_I - Qt::Key_A + 'A')));
    btnLetterQp[9]->setText(QString("%1").arg(QChar(Qt::Key_O - Qt::Key_A + 'A')));
    btnLetterQp[10]->setText(QString("%1").arg(QChar(Qt::Key_P - Qt::Key_A + 'A')));

    btnLetterQp[11]->setText("{\n[");
    btnLetterQp[12]->setText("}\n]");
    btnLetterQp[13]->setText("|\n\\");
    ///////////////////////////////////////////////////////////////////////////////
    // 字母按钮A~L
    for (int i = 0; i < 13; i++) {
        btnLetterAl[i] = new QPushButton(this);
        btnLetterAl[i]->setFixedSize(60, 60);

        if (1 < i && i < 10) {
            btnLetterAl[i]->setProperty("btnType", "letter");
        }

        horLyout[3]->addWidget(btnLetterAl[i]);
    }
    btnLetterAl[0]->setFixedWidth(108);
    btnLetterAl[0]->setText("Caps Lock");

    btnLetterAl[1]->setText(QString("%1").arg(QChar(Qt::Key_A - Qt::Key_A + 'A')));
    btnLetterAl[2]->setText(QString("%1").arg(QChar(Qt::Key_S - Qt::Key_A + 'A')));
    btnLetterAl[3]->setText(QString("%1").arg(QChar(Qt::Key_D - Qt::Key_A + 'A')));
    btnLetterAl[4]->setText(QString("%1").arg(QChar(Qt::Key_F - Qt::Key_A + 'A')));
    btnLetterAl[5]->setText(QString("%1").arg(QChar(Qt::Key_G - Qt::Key_A + 'A')));
    btnLetterAl[6]->setText(QString("%1").arg(QChar(Qt::Key_H - Qt::Key_A + 'A')));
    btnLetterAl[7]->setText(QString("%1").arg(QChar(Qt::Key_J - Qt::Key_A + 'A')));
    btnLetterAl[8]->setText(QString("%1").arg(QChar(Qt::Key_K - Qt::Key_A + 'A')));
    btnLetterAl[9]->setText(QString("%1").arg(QChar(Qt::Key_L - Qt::Key_A + 'A')));

    btnLetterAl[10]->setText(":\n;");
    btnLetterAl[11]->setText("\"\n'");
    btnLetterAl[12]->setFixedWidth(108);
    btnLetterAl[12]->setText("Return");

    ///////////////////////////////////////////////////////////////////////////////
    // 字母按钮Z~M
    for (int i = 0; i < 12; i++) {
        btnLetterZm[i] = new QPushButton(this);
        btnLetterZm[i]->setFixedSize(60, 60);

        if (1 < i && i < 9) {
            btnLetterZm[i]->setProperty("btnType", "letter");
        }

        horLyout[4]->addWidget(btnLetterZm[i]);
    }
    btnLetterZm[0]->setFixedWidth(140);
    btnLetterZm[0]->setText("Shift");

    btnLetterZm[1]->setText(QString("%1").arg(QChar(Qt::Key_Z - Qt::Key_A + 'A')));
    btnLetterZm[2]->setText(QString("%1").arg(QChar(Qt::Key_X - Qt::Key_A + 'A')));
    btnLetterZm[3]->setText(QString("%1").arg(QChar(Qt::Key_C - Qt::Key_A + 'A')));
    btnLetterZm[4]->setText(QString("%1").arg(QChar(Qt::Key_V - Qt::Key_A + 'A')));
    btnLetterZm[5]->setText(QString("%1").arg(QChar(Qt::Key_B - Qt::Key_A + 'A')));
    btnLetterZm[6]->setText(QString("%1").arg(QChar(Qt::Key_N - Qt::Key_A + 'A')));
    btnLetterZm[7]->setText(QString("%1").arg(QChar(Qt::Key_M - Qt::Key_A + 'A')));

    btnLetterZm[ 8]->setText("<\n,");
    btnLetterZm[ 9]->setText(">\n.");
    btnLetterZm[10]->setText("?\n/");

    btnLetterZm[11]->setFixedWidth(140);
    btnLetterZm[11]->setText("Shift");

    ///////////////////////////////////////////////////////////////////////////////
    // 底部按钮
    for (int i = 0; i < 7; i++) {
        btnBottom[i] = new QPushButton(this);
        btnBottom[i]->setFixedSize(60, 60);
        horLyout[5]->addWidget(btnBottom[i]);
    }

    btnBottom[0]->setText("Fn");
    btnBottom[1]->setText("Ctrl");
    btnBottom[2]->setText("Alt\noption");

    btnBottom[3]->setFixedWidth(76);
    btnBottom[3]->setText("Win");
    btnBottom[5]->setFixedWidth(76);
    btnBottom[5]->setText("Win");

    btnBottom[4]->setFixedWidth(318);
    btnBottom[4]->setText("Space");

    btnBottom[6]->setText("Alt\noption");

    // 方向控制键
    for (int i = 0; i < 4; i++) {
        btnDirection[i] = new QPushButton(this);
        btnDirection[i]->setFixedSize(60, 30);
    }
    btnDirection[0]->setIcon(QIcon(":/images/icons/arrow_up"));
    btnDirection[1]->setIcon(QIcon(":/images/icons/arrow_left"));
    btnDirection[2]->setIcon(QIcon(":/images/icons/arrow_down"));
    btnDirection[3]->setIcon(QIcon(":/images/icons/arrow_right"));

    gridLayout = new QGridLayout();
    gridLayout->setVerticalSpacing(0);
    gridLayout->setHorizontalSpacing(5);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    gridLayout->addWidget(btnDirection[0], 0, 1);
    gridLayout->addWidget(btnDirection[1], 1, 0);
    gridLayout->addWidget(btnDirection[2], 1, 1);
    gridLayout->addWidget(btnDirection[3], 1, 2);
    horLyout[5]->addLayout(gridLayout);

    // 测试用
    verLayoutGlobal->addStretch();
}

void WidgetKeyboard::SetStyleSheet()
{
    QStringList qss;
    qss.append(QString(".WidgetKeyboard{border: 2px solid %1; border-radius: 8px; background-color:%2;}").arg(BORDER_COLOR).arg(BACKGROUND));
    qss.append(QString("QPushButton{border: 2px solid %1; border-radius: 8px; background-color: transparent; color: %2; font: bold 14px;}").arg(BORDER_COLOR).arg(TEXT_COLOR));
    qss.append(QString("QPushButton:hover,QPushButton:pressed,QPushButton:checked{background-color: #000000;}"));
    this->setStyleSheet(qss.join(""));
}

// 按下鼠标左键
void WidgetKeyboard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pointDrag = event->globalPos() - frameGeometry().topLeft();
        m_bLeftBtnPress = true;
        event->accept();
    }
}

// 按下鼠标左键并移动
void WidgetKeyboard::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() == Qt::LeftButton) && m_bLeftBtnPress)
    {
        move(event->globalPos() - m_pointDrag);
        event->accept();
    }
}

// 释放鼠标
void WidgetKeyboard::mouseReleaseEvent(QMouseEvent *)
{
    m_bLeftBtnPress = false;
}

// 设置背景色
void WidgetKeyboard::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(QColor(BORDER_COLOR));
    pen.setWidth(2);

    painter.setPen(pen);
    painter.setBrush(QColor(BACKGROUND));
    painter.drawRoundRect(QRect(2, 2, this->width() - 4, this->height() - 4), 2, 5);
#else
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
#endif
}
