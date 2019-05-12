#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void DataStreamDemo();//二进制文件读写demo
    void TextStreamDemo();//文本文件读写demo
};

#endif // DIALOG_H
