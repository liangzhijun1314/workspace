#ifndef COMTOOL_H
#define COMTOOL_H

#include "common_global.h"
#include <QRect>
#include <string>

enum OS_INFO
{
    OS_VER = 0,
    OS_BIT = 1,
    OS_DES = 2,
    OS_ALL = -1,
};
class COMMONSHARED_EXPORT ComTool
{
public:
    ComTool();
    static const std::string getSystemInfo();  //获取系统版本号， Windows与Mac
//    QString getOSDisplayString(OS_INFO type = OS_ALL);		//获取系统版本信息
};

#endif // COMTOOL_H
