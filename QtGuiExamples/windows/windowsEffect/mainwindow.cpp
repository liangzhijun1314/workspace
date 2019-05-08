/*******************************************************************************
** @file:     mainwindow.cpp
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-2-7
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#include "mainwindow.h"
#include <QtGui>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWinFlags();
    this->resize(300,200);
    mainLayout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::mainLayout()
{
    QWidget* widget = new QWidget(this);
    dropBtn = new QPushButton(QString::fromLocal8Bit("下坠效果"),widget);
    shakeBtn = new QPushButton(QString::fromLocal8Bit("抖动效果"),widget);
    opacityBtn = new QPushButton(QString::fromLocal8Bit("透明效果"),widget);
    QVBoxLayout * vLayout = new  QVBoxLayout;
    vLayout->addWidget(dropBtn);
    vLayout->addWidget(shakeBtn);
    vLayout->addWidget(opacityBtn);
    widget->setLayout(vLayout);

    this->setCentralWidget(widget);
    QObject::connect(dropBtn,SIGNAL(clicked(bool)),this,SLOT(dropCLicked()));
    QObject::connect(shakeBtn,SIGNAL(clicked(bool)),this,SLOT(shakeClicked()));
    QObject::connect(opacityBtn,SIGNAL(clicked(bool)),this,SLOT(opacityClicked()));
}

void MainWindow::setWinFlags()
{
/*******************
** Qt::Widget  -- QWiget构造函数的默认值，如果新的窗口部件没有父窗口部件，则为独立窗口，否则为子窗口部件。
** ·Qt::Window -- 不管有没有父窗口，都是一个窗口，带有窗口边框和标题栏。
** ·Qt::Dialog -- 新窗口部件为对话框，是QDialog构造函数的默认值。
** ·Qt::Sheet -- 新窗口部件为Macintosh表单（sheet）。
** ·Qt::Drawer -- 新窗口部件为Macintosh抽屉（drawer）。
** ·Qt::Popup -- 新窗口部件为弹出式顶层窗口。
** ·Qt::Tool -- 为工具窗口，通常是显示工具按钮的小窗口。若有父窗口，则显示在父窗口上面，否则就显示在顶层。
** ·Qt::ToolTip -- 为一个提示窗口，无标题栏和边框。
** ·Qt::SplashScreen -- 欢迎窗口，也叫启动画面，是QSplashScreen函数的默认值。
** ·Qt::Desktop -- 新窗口部件是桌面，是QdesktopWidet构造函数的默认值。
** ·Qt::SubWindow -- 五六年有没有父窗口，此窗口都是一个子窗口。
** ·Qt::MSWindowsFixedSizeDialogHint -- 为窗口添加一个窄的对话框边框，通常这个提示用于固定大小的对话框。
** ·Qt::MSWindowsOwnDC -- 为窗口添加自身的显示上下文菜单。
** ·Qt::X11BypassWindowManagerHint -- 完全忽视窗口管理器，作用是产生一个不被管理的无边框的窗口。（调用Qwidget::activeWindow()函数才可以接受键盘输入事件）
** ·Qt::FramelessWindowHint -- 无边框的窗口，无法移动或改变大小。
** ·Qt::CustomizeWindowHint -- 关闭默认的窗口标题提示。
** ·Qt::WindowTitleHint -- 为窗口添加一个标题栏。
** ·Qt::WindowSystemMenuHint -- 为窗口添加一个窗口系统菜单。
** ·Qt::WindowMinimizeButtonHint -- 为窗口添加一个最小化按钮。
** ·Qt::WindowMaximizeButtonHint -- 为窗口添加一个最大化按钮。
** ·Qt::WindowMinMaxBttondHint -- 添加一个最小化和最大化按钮。
** ·Qt::WindowContextHelpButtonHint -- 给窗口添加上下文帮助按钮。
** ·Qt::WindowStaysOnTopHint -- 该窗口停留在所有窗口的上面，即设置顶层窗口。
** ·Qt::WindowType_Mask -- 一个用于提取窗口标识中窗口类型部分的掩码。
*******************/
    Qt::WindowFlags flags = Qt::Window;
    this->setWindowFlags(flags);

    //常用指定效果
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint); // 去掉标题栏,去掉任务栏显示，窗口置顶

    // 设置窗口透明度
    this->setWindowOpacity(0.9); //0为全透明，1为不透明
}

void MainWindow::dropCLicked()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");

    QDesktopWidget *pDesktopWidget = QApplication::desktop();
    int x = (pDesktopWidget->availableGeometry().width() - width()) / 2;
    int y = (pDesktopWidget->availableGeometry().height() - height()) / 2;

    pAnimation->setDuration(1000);
    pAnimation->setStartValue(QRect(x, 0, width(), height()));
    pAnimation->setEndValue(QRect(x, y, width(), height()));
    pAnimation->setEasingCurve(QEasingCurve::OutElastic);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::shakeClicked()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::opacityClicked()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "windowOpacity");
    pAnimation->setDuration(1000);
    pAnimation->setKeyValueAt(0, 1);
    pAnimation->setKeyValueAt(0.5, 0);
    pAnimation->setKeyValueAt(1, 1);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
