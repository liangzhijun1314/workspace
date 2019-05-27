#ifndef COMMON_GLOBAL_H
#define COMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMON_LIBRARY)
#  define COMMONSHARED_EXPORT Q_DECL_EXPORT //当编译共享库时，必须将其添加到使用的符号声明
#else
#  define COMMONSHARED_EXPORT Q_DECL_IMPORT //当编译一个（使用了该共享库）客户端时，必须将其添加到使用的符号声明
#endif

#endif // COMMON_GLOBAL_H
