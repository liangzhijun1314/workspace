#ifndef READER_H
#define READER_H
#include <QObject>
#include <QDebug>

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader() {}

public slots:   //Qt4中必须由slots修饰，并且要使用访问控制符进行访问控制
    void receiveNewspaper(const QString name)
    {
        qDebug()<<"Receives Newspaper: "<<name;
    }
};
#endif // READER_H
