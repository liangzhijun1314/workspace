/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 重庆重邮汇测通信技术有限公司
 文 件 名 : widgetkeyboard.h --- WidgetKeyBoard
 作 者    : Niyh
 编写日期 : 2017
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
 倪又华    2017    1.0.0.0 1     文件创建
*******************************************************************/
#ifndef WIDGETKEYBOARD_H
#define WIDGETKEYBOARD_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class WidgetKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetKeyboard(QWidget *parent = 0);
    ~WidgetKeyboard();

signals:

public slots:

private:
    // 布局
    QHBoxLayout *horLyout[6];
    QVBoxLayout *verLayoutGlobal;
    QGridLayout *gridLayout;
    // 顶部
    QPushButton *btnTop[14];
    // 数字
    QPushButton *btnTopNumber[14];
    // 字母
    QPushButton *btnLetterQp[14];
    QPushButton *btnLetterAl[13];
    QPushButton *btnLetterZm[12];
    QPushButton *btnBottom[7];
    QPushButton *btnDirection[4];

private:
    void InitButtons();
    void SetStyleSheet();
protected:
    QPoint m_pointDrag;
    bool m_bLeftBtnPress;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);
};

#endif // WIDGETKEYBOARD_H
