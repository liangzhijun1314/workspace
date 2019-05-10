#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setScreenIndex(int index);  //设置屏幕的索引
private:
    QLabel *m_label;
};

#endif // MAINWINDOW_H
