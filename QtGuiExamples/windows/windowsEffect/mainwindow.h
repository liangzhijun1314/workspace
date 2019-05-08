/*******************************************************************************
** @file:     mainwindow.h
** @class:    MainWindow
** @brief:    一些窗口的效果
** 来自于网络 http://blog.csdn.net/liang19890820/article/details/51888114
**
** @author:   lzj
** @date:     2018-2-7
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void mainLayout();
    void setWinFlags();  //设置窗口的类型

private slots:
    void dropCLicked();
    void shakeClicked();
    void opacityClicked();

private:
    QPushButton *dropBtn;       //窗口下坠
    QPushButton *shakeBtn;      //窗口抖动
    QPushButton *opacityBtn;    //窗口透明
};

#endif // MAINWINDOW_H
