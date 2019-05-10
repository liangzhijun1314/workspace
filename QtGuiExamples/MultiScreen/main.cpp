#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QDebug>
typedef struct{
    int screen_no;
    QRect rect;
}SCREEN;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget *desktop = QApplication::desktop();
    int screen_count = desktop->screenCount();//获取当前屏幕个数
    int prim_screen = desktop->primaryScreen();//获取主屏幕的索引序号
    int desktop_width = desktop->width();//获取虚拟屏幕全宽,是获取的总宽度，对于横向扩展屏来说，也就是 屏幕1+ 屏幕2 + ...n 的宽度
    int desktop_height = desktop->height();  //获取虚拟屏幕全高
    qDebug()<<"screen_count = "<<screen_count;
    qDebug()<<"prim_screen = "<<prim_screen;
    qDebug()<<"desktop_width = "<<desktop_width;
    qDebug()<<"desktop_height = "<<desktop_height;
//    MainWindow wd[screen_count];
    MainWindow *wd = new MainWindow[screen_count];
    QRect rect;

    for(int i = 0 ; i < screen_count; i++){
        rect = desktop->screenGeometry(prim_screen + i);   //整个屏幕的矩形区域
        rect = desktop->availableGeometry(prim_screen + i);//当前屏幕的可用部分
        int scrren_width = rect.width();
        int screen_height = rect.height();
        int offsetX = rect.x();
        int offsetY = rect.y();
        qDebug()<<"offsetX = "<<offsetX;  //
        qDebug()<<"offsetY = "<<offsetY;
        qDebug()<<"Current Screen is "<<prim_screen + i<<"; screen width = "<<scrren_width<<"; screen height = "<<screen_height;

        if(i == 0){
            wd[i].move(0,0);
        }else{
            wd[i].move(offsetX,offsetY);
//            wd[i].move(desktop->screenGeometry(prim_screen+i-1).width(),0);
        }
        wd[i].setWindowTitle(QString::fromLocal8Bit("屏幕")+QString::number(i));

//        wd[i].setScreenSize(0,0,scrren_width,screen_height);
//        wd[i].setScreenIndex(prim_screen + i);
//        wd[i].setWindowFlags( Qt::FramelessWindowHint);
        wd[i].showMaximized();
        //        wd[i].resize(scrren_width,screen_height);
                wd[i].show();

    }

    return a.exec();
}
