#include "dialog.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    qDebug() << "-------start DataStreamDemo------";
    DataStreamDemo();//二进制文件读写demo
    qDebug() << "-------start TextStreamDemo------";
    TextStreamDemo();//文本文件读写demo
}

Dialog::~Dialog()
{

}
//二进制文件读写demo
void Dialog::DataStreamDemo()
{
    // 写
    QFile fileWrite("DataStream.dat");
    if (!fileWrite.open(QIODevice::WriteOnly)) { // 打开形式是只写方式
        qDebug() << "Open file failed. the file is not exits";
        return;
    } else {
        QDataStream out(&fileWrite);
        // 写入魔术数字和版本
        out << (quint32)0xA0B0C0D0;
        out << (qint32)123;

        out.setVersion(QDataStream::Qt_5_8);

        out << QString("the answer is");
        out << (qint32)42;
    }
    fileWrite.close();// 如果不想关闭文件，可以使用 file.flush();

    // 读
    QFile fileRead("DataStream.dat");
    if (!fileRead.open(QIODevice::ReadOnly)) { // 打开形式是只写方式
        qDebug() << "Open file failed.";
        return;
    } else {
        QDataStream in(&fileRead);
        // 检查魔术数字
        quint32 magic;
        in >> magic;
        if (magic != 0xA0B0C0D0) {
            return ;
        }
        // 检查版本
        qint32 version;
        in >> version;
        if (version < 100) {
            return ;
        }
        if (version > 123) {
            return ;
        }
        if (version <= 110) {
            in.setVersion(QDataStream::Qt_4_8);
        } else {
            in.setVersion(QDataStream::Qt_5_8);
        }
        QString str;
        qint32 a;
        in >> str >> a;
        qDebug() << "str = " << str;
        qDebug() << "qint32 a = " << a;
    }
    fileRead.close();// 如果不想关闭文件，可以使用 file.flush();

    // 读写
    QFile file("DataStream.dat");
    file.open(QIODevice::ReadWrite);

    QDataStream stream(&file);
    QString str = "the answer is 42";
    QString strout;

    stream << str;
    file.flush();
    //所谓流，就像水流一样，它的游标会随着输出向后移动。当使用<<操作符输出之后，流的游标已经到了最后，
    //此时你再去读，当然什么也读不到了。所以你需要在输出之后重新把游标设置为 0 的位置才能够继续读取
    stream.device()->seek(0);
    stream >> strout;
    qDebug() <<"strout = "<<strout;
}
//文本文件读写demo
void Dialog::TextStreamDemo()
{
    //写
    QFile writedata("TextStream.txt");
    /*
QIODevice::NotOpen 	    未打开
QIODevice::ReadOnly 	以只读方式打开
QIODevice::WriteOnly 	以只写方式打开
QIODevice::ReadWrite 	以读写方式打开
QIODevice::Append 	    以追加的方式打开，新增加的内容将被追加到文件末尾
QIODevice::Truncate 	以重写的方式打开，在写入新的数据时会将原有数据全部清除，游标设置在文件开头。
QIODevice::Text 	    在读取时，将行结束符转换成 \n；在写入时，将行结束符转换成本地格式，例如 Win32 平台上是 \r\n
QIODevice::Unbuffered 	忽略缓存
*/
    if (writedata.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&writedata);
        out << "The answer is " << 42 << '\n';
        out << bin << 12345678 << '\n';  //输出 12345678 的二进制形式 ,等价于out.setIntegerBase(2); out << 12345678;
        out << showbase << uppercasedigits << hex << 12345678 << '\n';  //全部字母大写的十六进制格式(0x)
    }
    writedata.close();

    //读
    QFile readdata("TextStream.txt");
    if (readdata.open(QFile::ReadOnly)) {
        QTextStream in(&readdata);
        in.setCodec("UTF-8");
        QString strall = in.readAll();
        qDebug() << "strall = " << strall;

        in.device()->seek(0);
        while (!readdata.atEnd()) { // 循环读取文件，知道末尾
            qDebug() << "strline = "  << readdata.readLine().toStdString().c_str();;  // 一行读取的内容 中文也可显示
        }
    }
}
