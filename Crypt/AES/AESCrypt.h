/*******************************************************************************
** @file:     AESCrypt.h
** @class:    AESCrypt
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-4
** @version:
*******************************************************************************/

#ifndef AESCRYPT_H
#define AESCRYPT_H


class AESCrypt
{
public:
    AESCrypt(unsigned char* key);
    virtual ~AESCrypt();
    unsigned char* Cipher(unsigned char* input);    // 加密，传入的数组大小必须是16字节
    unsigned char* InvCipher(unsigned char* input); // 解密，传入的数组也必须是16字节
    void* Cipher(void* input, int length=0);        // 可以传入数组，大小必须是16的整数倍，如果不是将会越界操作；如果不传length而默认为0，那么将按照字符串处理，遇'\0'结束
    void* InvCipher(void* input, int length);       // 必须传入数组和大小，必须是16的整数倍

    void Cipher(char* input, char *output);
    void InvCipher(char *input,char *output);

private:
    void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
    unsigned char FFmul(unsigned char a, unsigned char b);

    void SubBytes(unsigned char state[][4]);
    void ShiftRows(unsigned char state[][4]);
    void MixColumns(unsigned char state[][4]);
    void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

    void InvSubBytes(unsigned char state[][4]); //逆字节替代
    void InvShiftRows(unsigned char state[][4]);//逆行移位
    void InvMixColumns(unsigned char state[][4]);//逆列混淆

    int strToHex(const char *ch, char *hex);
    int hexToStr(const char *hex, char *ch);
    int ascillToValue(const char ch);
    char valueToHexCh(const int value);
    int getUCharLen(const unsigned char *uch);
    int strToUChar(const char *ch, unsigned char *uch);
    int ucharToStr(const unsigned char *uch, char *ch);
    int ucharToHex(const unsigned char *uch, char *hex);
    int hexToUChar(const char *hex, unsigned char *uch);

private:
    unsigned char Sbox[256];
    unsigned char InvSbox[256];
    unsigned char w[11][4][4];
    int plainLength;

};

#endif // AESCRYPT_H
