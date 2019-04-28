/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-7
** @version:
*******************************************************************************/

#include <QCoreApplication>
#include "AESEncryptor.h"
#include "iostream"
#include <string.h>
#include <fstream>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QDirIterator>

#include "AES.h"
#include "Base64.h"
using namespace std;

const char g_key[17] = "cbox4620Password";
const char g_iv[17] = "cbox4620Password";


string EncryptionAES(const string& strSrc) //AES加密
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
string DecryptionAES(const string& strSrc) //AES解密
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
void DecryptionAESLine(QString inputFile,QString outputFile,bool &isDecrypt)
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

void DecryptionAESAllFile(QString path, bool &bIsDecryption) {
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
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    unsigned char key[] = "cbox4620Password";
//    AesEncryptor *AES = new AesEncryptor(key);

    // 方式1
//    QString str = "hello AES 中文测试";
//    std::string miwen = AES->EncryptString(str.toStdString());
//    qDebug()<<"mi went str = " << QString::fromStdString(miwen);
//    std::string miwen = "D75E5B64CD9A0B8CF02B1C17F336173154A2055D9DC2FE09FE927282A4E39913";  // only test
//    std::string mingwen = AES->DecryptString(miwen);
//    qDebug()<<"mingwen went str = " << QString::fromStdString(mingwen);

    // 方式2
//    QString str = "hello AES 中文测试" + QString::number(i);
//    QString miwen = AES->EncryptQString(str);
//    qDebug()<<"mi went str = " << miwen;
//    QString mingwen = AES->DecryptQString(miwen);
//    qDebug()<<"ming went str = " << mingwen;

//    bool bIsDecrypt = false;
//    AES->DecryptAllFile(QDir::currentPath(),bIsDecrypt);

//    delete AES;
//    AES = NULL;
//    if (bIsDecrypt)
//        qDebug()<<"AES Decrypt success, please close.";
//    else
//        qDebug()<<"No file need to decrypt.";

    //方法3

//    string str1 = "qwertyuisfdlsajdxcvnkhsakfh1332487  中文测试";
//    qDebug() << QString("原文:")<< QString::fromStdString(str1);


//    string str2 = EncryptionAES(str1);
//    qDebug()<<"加密"<< QString::fromStdString(str2);

//    string str3 = DecryptionAES(str2);
//    qDebug()<<"解密"<< QString::fromStdString(str3);

    bool bIsDecryption = false;
    DecryptionAESAllFile(QDir::currentPath(),bIsDecryption);
    if (bIsDecryption)
        qDebug()<<"AES Decrypt success, please close.";
    else
        qDebug()<<"No file need to decrypt,please close.";
    return a.exec();
}
