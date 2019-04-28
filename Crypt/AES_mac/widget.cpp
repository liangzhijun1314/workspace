/*******************************************************************************
** @file:     widget.cpp
** @class:    Widget
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-21
** @version:
*******************************************************************************/

#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>

#include "AES.h"
#include "Base64.h"
using namespace std;

const char g_key[17] = "cbox4620Password";
const char g_iv[17] = "cbox4620Password";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏


}

Widget::~Widget()
{
    delete ui;
}

void Widget::DecryptionAESAllFile(QString path, bool &bIsDecryption)
{
    QDir dir(path);
    if(!dir.exists())
    {
        return;
    }
    //获取所选文件类型过滤器
    QStringList filters;
    filters<<QString("*.tmp");

    //定义迭代器并设置过滤器
    QDirIterator dir_iterator(path,
                              filters,
                              QDir::Files | QDir::NoSymLinks,
                              QDirIterator::Subdirectories);
    QStringList string_list;
    while(dir_iterator.hasNext())
    {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString absolute_file_path = file_info.absoluteFilePath();
        string_list.append(absolute_file_path);
    }
    if (string_list.size() > 0)
        bIsDecryption = true;

    for (int i = 0; i < string_list.size(); i++) {
        bool isDecrypt = true;
        DecryptionAESLine(string_list.at(i),string_list.at(i)+"_AES_Decrypt",isDecrypt);
        if (isDecrypt)
            qDebug()<<"input file : " << string_list.at(i) << " AES decrypt success.";
        else
            qDebug()<<"input file : " << string_list.at(i) << " not need decrypt.";
    }
}

void Widget::DecryptionAESLine(QString inputFile, QString outputFile, bool &isDecrypt)
{
    QFile infile(inputFile);
    if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        isDecrypt = false;
        qDebug() << "Can not open file " << inputFile;
        return;
    }

    QFile outfile(outputFile);
    if (!outfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        isDecrypt = false;
        qDebug() << "Can not open file " << outputFile;
        return;
    }

    QTextStream in(&infile);
    int numLine = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (numLine == 0){
            if (line.contains(" -- AES decrypt ok.")) {
                isDecrypt = false;
                break;
            }
        }

        string strLine = DecryptionAES(line.toStdString());
        if (numLine == 0)
            strLine += " -- AES decrypt ok.";

        numLine++;
        QTextStream out(&outfile);
        out << QString::fromStdString(strLine) <<"\n";

    }
    infile.close();
    outfile.close();

    if (isDecrypt) {
        QFile::remove(inputFile);
        QFile::rename(outputFile,inputFile);
    } else {
        QFile::remove(outputFile);
    }
}

string Widget::EncryptionAES(const string &strSrc)
{
    size_t length = strSrc.length();
    int block_num = length / BLOCK_SIZE + 1;
    //明文
    char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
    memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
    strcpy(szDataIn, strSrc.c_str());

    //进行PKCS7Padding填充。
    int k = length % BLOCK_SIZE;
    int j = length / BLOCK_SIZE;
    int padding = BLOCK_SIZE - k;
    for (int i = 0; i < padding; i++)
    {
        szDataIn[j * BLOCK_SIZE + k + i] = padding;
    }
    szDataIn[block_num * BLOCK_SIZE] = '\0';

    //加密后的密文
    char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
    memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

    //进行进行AES的CBC模式加密
    AES aes;
    aes.MakeKey(g_key, g_iv, 16, 16);
    aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
    string str = base64_encode((unsigned char*) szDataOut,
            block_num * BLOCK_SIZE);
    delete[] szDataIn;
    delete[] szDataOut;
    return str;
}

string Widget::DecryptionAES(const string &strSrc)
{
    string strData = base64_decode(strSrc);
    size_t length = strData.length();
    //密文
    char *szDataIn = new char[length + 1];
    memcpy(szDataIn, strData.c_str(), length+1);
    //明文
    char *szDataOut = new char[length + 1];
    memcpy(szDataOut, strData.c_str(), length+1);

    //进行AES的CBC模式解密
    AES aes;
    aes.MakeKey(g_key, g_iv, 16, 16);
    aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);

    //去PKCS7Padding填充
    if (0x00 < szDataOut[length - 1] <= 0x16)
    {
        int tmp = szDataOut[length - 1];
        for (int i = length - 1; i >= length - tmp; i--)
        {
            if (szDataOut[i] != tmp)
            {
                memset(szDataOut, 0, length);
                cout << "去填充失败！解密出错！！" << endl;
                break;
            }
            else
                szDataOut[i] = 0;
        }
    }
    string strDest(szDataOut);
    delete[] szDataIn;
    delete[] szDataOut;
    return strDest;
}

void Widget::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    bool bIsDecryption = false;
    QString currentAppPath = QApplication::applicationDirPath();
    QStringList list = currentAppPath.split("/");
    QString currentPath = "";
    for (int i = 0; i < list.size(); i++) {
        if (i < list.size() - 3)
            currentPath += list.at(i) + "/";
    }
    DecryptionAESAllFile(currentPath,bIsDecryption);
    if (bIsDecryption) {
        QMessageBox::warning(this,"tishi",QString("AES Decrypt success, please close!"));
    } else {
        QMessageBox::warning(this,"tishi",QString(" No file need to decrypt, please close!"));
    }

    this->close();
}
