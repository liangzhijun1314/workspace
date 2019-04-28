/*******************************************************************************
** @file:     AESEncryptor.h
** @class:    AESEncryptor
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-4
** @version:
*******************************************************************************/

#ifndef AESENCRYPTOR_H
#define AESENCRYPTOR_H
#include <string>
#include <QString>
#include <QFile>

class AESCrypt;

class AesEncryptor
{
public:
    AesEncryptor(unsigned char* key);
    ~AesEncryptor(void);

    QString EncryptQString(QString strInfor);
    QString DecryptQString(QString strMessage);

    std::string EncryptString(std::string strInfor);
    std::string DecryptString(std::string strMessage);

    void EncryptTxtFile(const char* inputFileName, const char* outputFileName);
    void DecryptTxtFile(const char* inputFileName, const char* outputFileName);

    void DecryptLine(QString inputFile,QString outputFile,bool &isDecrypt); //一行一行的解密
    void DecryptAllFile(QString path,bool &bIsDecrypt); // 解析当前路径下所有符合条件的文件

private:
    void Byte2Hex(const unsigned char* src, int len, char* dest);
    void Hex2Byte(const char* src, int len, unsigned char* dest);
    int  Char2Int(char c);

private:
    AESCrypt* m_pEncryptor;
};

#endif // AESENCRYPTOR_H
