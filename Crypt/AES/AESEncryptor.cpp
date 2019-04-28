/*******************************************************************************
** @file:     AESEncryptor.cpp
** @class:    AESEncryptor
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-4
** @version:
*******************************************************************************/

#include "AESCrypt.h"
#include "AESEncryptor.h"
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QString>

#include <fstream>
using namespace std;

AesEncryptor::AesEncryptor(unsigned char* key)
{
    m_pEncryptor = new AESCrypt(key);
}


AesEncryptor::~AesEncryptor(void)
{
    delete m_pEncryptor;
}

QString AesEncryptor::EncryptQString(QString strInfor)
{
    QString result = QString("");
    char ch_mingwen[10240];
    char ch_miwen[10240];
    strcpy(ch_mingwen,strInfor.toUtf8().data());
    m_pEncryptor->Cipher(ch_mingwen,ch_miwen);
    result = QString(ch_miwen);
    return result;
}

QString AesEncryptor::DecryptQString(QString strMessage)
{
    QString result = QString("");
    char ch_mingwen[10240];
    char ch_miwen[10240];
    strcpy(ch_miwen,strMessage.toUtf8().data());
    m_pEncryptor->InvCipher(ch_miwen,ch_mingwen);
    result = QString(ch_mingwen);
    return result;
}

void AesEncryptor::Byte2Hex(const unsigned char* src, int len, char* dest) {
    for (int i=0; i<len; ++i) {
#ifdef Q_OS_WIN
        sprintf_s(dest + i * 2, 3, "%02X", src[i]);
#else
        sprintf(dest + i * 2, "%02X", src[i]);
#endif
    }
}

void AesEncryptor::Hex2Byte(const char* src, int len, unsigned char* dest) {
    int length = len / 2;
    for (int i=0; i<length; ++i) {
        dest[i] = Char2Int(src[i * 2]) * 16 + Char2Int(src[i * 2 + 1]);
    }
}

int AesEncryptor::Char2Int(char c) {
    if ('0' <= c && c <= '9') {
        return (c - '0');
    }
    else if ('a' <= c && c<= 'f') {
        return (c - 'a' + 10);
    }
    else if ('A' <= c && c<= 'F') {
        return (c - 'A' + 10);
    }
    return -1;
}

string AesEncryptor::EncryptString(string strInfor) {
    int nLength = strInfor.length();
    int spaceLength = 16 - (nLength % 16);
    unsigned char* pBuffer = new unsigned char[nLength + spaceLength];
    memset(pBuffer, '\0', nLength + spaceLength);   
#ifdef Q_OS_WIN
    memcpy_s(pBuffer, nLength + spaceLength, strInfor.c_str(), nLength);
#else
    memcpy(pBuffer, strInfor.c_str(), nLength);
#endif
    m_pEncryptor->Cipher(pBuffer, nLength + spaceLength);

    // 这里需要把得到的字符数组转换成十六进制字符串
    char* pOut = new char[2 * (nLength + spaceLength)];
    memset(pOut, '\0', 2 * (nLength + spaceLength));
    Byte2Hex(pBuffer, nLength + spaceLength, pOut);

    string retValue(pOut);
    delete[] pBuffer;
//    delete[] pOut;
    return retValue;
}

string AesEncryptor::DecryptString(string strMessage) {
    int nLength = strMessage.length() / 2;
    unsigned char* pBuffer = new unsigned char[nLength];
    memset(pBuffer, '\0', nLength);
    Hex2Byte(strMessage.c_str(), strMessage.length(), pBuffer);

    m_pEncryptor->InvCipher(pBuffer, nLength);
    string retValue((char*)pBuffer);
//    delete[] pBuffer;
    return retValue;
}

void AesEncryptor::EncryptTxtFile(const char* inputFileName, const char* outputFileName) {
    ifstream ifs;

    // Open file:
    ifs.open(inputFileName);
    if (!ifs) {
//        UNILOGW("AesEncryptor::EncryptTxtFile() - Open input file failed!");
        return ;
    }

    // Read config data:
    string strInfor;
    string strLine;
    while (!ifs.eof()) {
        char temp[1024];
        memset(temp, '\0', 1024);
        ifs.read(temp, 1000);
        strInfor += temp;
    }
    ifs.close();

    // Encrypt
    strLine = EncryptString(strInfor);

    // Writefile
    ofstream ofs;
    ofs.open(outputFileName);
    if (!ofs) {
//        UNILOGW("AesEncryptor::EncryptTxtFile() - Open output file failed!");
        return ;
    }
    ofs << strLine;
    ofs.close();
}

void AesEncryptor::DecryptTxtFile(const char* inputFile, const char* outputFile) {
    ifstream ifs;

    // Open file:
    ifs.open(inputFile);
    if (!ifs) {
//        UNILOGW("AesEncryptor::DecryptTxtFile() - Open input file failed!");
        return ;
    }

    // Read config data:
    string strInfor;
    string strLine;
    while (!ifs.eof()) {
        char temp[1024];
        memset(temp, '\0', 1024);
        ifs.read(temp, 1000);
        strInfor += temp;
    }
    ifs.close();

    // Encrypt
    strLine = DecryptString(strInfor);

    // Writefile
    ofstream ofs;
    ofs.open(outputFile);
    if (!ofs) {
//        UNILOGW("AesEncryptor::DecryptTxtFile() - Open output file failed!");
        return ;
    }
    ofs << strLine;
    ofs.close();
}

void AesEncryptor::DecryptLine(QString inputFile,QString outputFile,bool &isDecrypt)
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

        string strLine = DecryptString(line.toStdString());
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

void AesEncryptor::DecryptAllFile(QString path,bool &bIsDecrypt)
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
        bIsDecrypt = true;

    for (int i = 0; i < string_list.size(); i++) {
        bool isDecrypt = true;
        DecryptLine(string_list.at(i),string_list.at(i)+"_AES_Decrypt",isDecrypt);
        if (isDecrypt)
            qDebug()<<"input file : " << string_list.at(i) << " AES decrypt success.";
        else
            qDebug()<<"input file : " << string_list.at(i) << " not need decrypt.";
    }
}
