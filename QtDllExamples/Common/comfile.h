#ifndef COMFILE_H
#define COMFILE_H

#include "common_global.h"
#include <QStringList>

class COMMONSHARED_EXPORT Comfile
{
public:
    static QString getFileContent(const QString &strFileName, bool isDecipjer = false);
    static bool writeContent(const QString &strFileName,const QString& strContent,bool isEcryption = false);

    static QStringList getFileListAtPath(const QString& strPath);
    static bool removeFileAtPath(const QString& strPath,const QString& strFileName = "");//strFileName为空表示删除所有文件

    static QString deciphering(const QByteArray &strContent);
    static QString ecryption(const QString &strContent);
};

#endif // COMFILE_H
