#include "dialog.h"
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"file path = "<<a.applicationFilePath();
    qDebug()<<"dir path = "<<a.applicationDirPath();
    qDebug()<<"current path = "<<QDir::currentPath();
    //QFile 和QFileInfo的简单使用
    QFile file("in.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 打开形式是只读方式，文本格式
        qDebug() << "Open file failed.";
        return -1;
    } else {
        while (!file.atEnd()) { // 循环读取文件，知道末尾
            qDebug() << file.readLine().toStdString().c_str();;  // 一行读取的内容 中文也可显示
        }
    }
    QFileInfo info(file);
    qDebug() << "isDir = " << info.isDir();
    qDebug() << "isExecutable = " << info.isExecutable();   //检查该文件是否是可执行文件
    qDebug() << "baseName = " << info.baseName();           //直接获得文件名
    qDebug() << "completeBaseName = " << info.completeBaseName();
    qDebug() << "suffix = " << info.suffix();       //直接获取文件后缀名。
    qDebug() << "completeSuffix = " << info.completeSuffix();
    file.close();

    /*baseName()和completeBaseName()，以及suffix()和completeSuffix()的区别*/
    QFileInfo fi("/tmp/archive.tar.gz");
    QString base  = fi.baseName();  // base = "archive"
    QString cbase = fi.completeBaseName();  // base = "archive.tar"
    QString suffix   = fi.suffix();  // ext = "gz"
    QString comsuffix   = fi.completeSuffix();  // ext = "tar.gz"
    qDebug() <<"base = "<< base;
    qDebug() <<"cbase = "<< cbase;
    qDebug() <<"suffix = "<< suffix;
    qDebug() <<"comsuffix = "<< comsuffix;
    //end

    Dialog w;
    w.show();

    return a.exec();
}
