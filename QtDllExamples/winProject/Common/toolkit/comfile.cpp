#include "comfile.h"

#include <QFile>
#include <QDir>

QString Comfile::getFileContent(const QString &strFileName, bool isDecipjer)
{
    QByteArray strContent = "";
    QFile file(strFileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        strContent = file.readAll();
        file.flush();
        file.close();
    }

    if (isDecipjer)
        return deciphering(strContent);
    else
        return strContent;
}
bool Comfile::writeContent(const QString &strFileName, const QString &strContent, bool isEcryption)
{
    QFile file(strFileName);
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
        return false;
    if (isEcryption)
        file.write(ecryption(strContent).toStdString().c_str());
    else
        file.write(strContent.toStdString().c_str());
    file.close();
    return true;
}

QStringList Comfile::getFileListAtPath(const QString &strPath)
{
    QStringList listFiles;
    listFiles.clear();

    QDir existdir(strPath);
    if (!existdir.exists()) {
        existdir.mkpath(strPath);
        return listFiles;
    }

    QDir dir(strPath);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();
    for (int i=0; i<list.count(); i++) {
        QString strFile = strPath + list.at(i).fileName();
        listFiles.push_back(strFile);
    }

    return listFiles;
}

bool Comfile::removeFileAtPath(const QString &strPath, const QString &strFileName)
{
    QDir existdir(strPath);
    if (!existdir.exists()) {
        existdir.mkpath(strPath);
        return false;
    }

    QDir dir(strPath);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();

    if (strFileName.isEmpty()) {
        for (int i=0; i<list.size(); i++) {
            QString file = strPath + list.at(i).fileName();
            QFile::remove(file);
        }
    } else {
        QFile::remove(strFileName);
    }

    return true;
}

QString Comfile::deciphering(const QByteArray &strContent)
{
    return QString(QByteArray::fromBase64(strContent));
}

QString Comfile::ecryption(const QString &strContent)
{
    QByteArray becr = strContent.toUtf8().toBase64();
    return QString(becr);
}


