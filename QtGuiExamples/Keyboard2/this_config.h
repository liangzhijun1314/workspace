#ifndef THIS_CONFIG_H
#define THIS_CONFIG_H

#include <QPainter>
#include <QSize>
#include <Qsettings.h>
#include <QString>
#include <QList>
#include <QDialog>
#include <QtGui>
#include "Qmessagebox.h"
#include "keyboard.h"


#ifdef RUN_ON_LINUX
    #include <sys/ioctl.h>
    #include <fcntl.h>
    #include <linux/fs.h>
    #include <termio.h>
    //---------
    #include <stdio.h>
    #include <termios.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>

#else
    #include <Windows.h>
#endif

#define SCREEN_WIDTH    480         //屏宽度
#define SCREEN_HEIGHT   272
#define GLOBAL_CODEC    "GB2312"

#ifdef RUN_ON_LINUX
    #define FILE_OPTION     "data/Option.ini"
    #define FILE_ZI_KU      "data/ziku.dat"

#endif

class Option
{
public:
    Option();
    ~Option();

private:
    Keyboard    *k_board;


public:
    void ShowKeyBoard(QWidget *parent, bool num = false);
    void CloseKeyBoard();

};
extern Option g_OptionData;
extern Option Window_show;

#endif // THIS_CONFIG_H
