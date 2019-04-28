/*******************************************************************************
** @file:     widget.h
** @class:    Widget
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-21
** @version:
*******************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "iostream"
#include "AES.h"
#include "Base64.h"
using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void DecryptionAESAllFile(QString path, bool &bIsDecryption);
    void DecryptionAESLine(QString inputFile,QString outputFile,bool &isDecrypt);
    string EncryptionAES(const string& strSrc); //AES加密
    string DecryptionAES(const string& strSrc); //AES解密

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
