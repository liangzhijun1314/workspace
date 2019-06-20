#include "comtool.h"
#include <QtGlobal>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QSysInfo>
#include <string>


#ifdef Q_OS_WIN32
#include <Windows.h>
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);
#endif

#ifdef Q_OS_MAC
#include "unistd.h"
#endif
ComTool::ComTool()
{

}

const std::string ComTool::getSystemInfo()
{
    std::string info;
#ifdef Q_OS_WIN32
// win
    QSysInfo::WinVersion ver = QSysInfo::windowsVersion();
    if (0x30 == ver) {
        info = "WinXP";
    } else if (0x80 == ver) {
        info = "WinVista";
    } else if (0x90 == ver) {
        info = "Win7";
    } else if(0xa0 == ver || 0xb0 == ver) {
        info = "Win8";
    } else if(0xc0 == ver) {
        info = "Win10";
    } else {
        info = "windows";
    }
#endif

#ifdef Q_OS_MAC
// mac
    QSysInfo::MacVersion ver = QSysInfo::macVersion();
    if(QSysInfo::MV_9 == ver) {
        info = "macOS 9";
    } else if(QSysInfo::MV_10_0 == ver) {
        info = "macOS 10.0";
    } else if(QSysInfo::MV_10_1 == ver) {
        info = "macOS 10.1";
    } else if(QSysInfo::MV_10_2 == ver) {
        info = "macOS 10.2";
    } else if(QSysInfo::MV_10_3 == ver) {
        info = "macOS 10.3";
    } else if(QSysInfo::MV_10_4 == ver) {
        info = "macOS 10.4";
    } else if(QSysInfo::MV_10_5 == ver) {
        info = "macOS 10.5";
    } else if(QSysInfo::MV_10_6 == ver) {
        info = "macOS 10.6";
    } else if(QSysInfo::MV_10_7 == ver) {
        info = "macOS 10.7";
    } else if(QSysInfo::MV_10_8 == ver) {
        info = "macOS 10.8";
    } else if(QSysInfo::MV_10_9 == ver) {
        info = "macOS 10.9";
    } else if(QSysInfo::MV_10_10 == ver) {
        info = "macOS 10.10";
    } else if(QSysInfo::MV_10_11 == ver) {
        info = "macOS 10.11";
    } else if(QSysInfo::MV_10_12 == ver) {
        info = "macOS 10.12";
    } else {
        info = "mac";
    }
#endif
    return info;
}

//QString ComTool::getOSDisplayString(OS_INFO type)
//{
//    static QString osInfo, winVer, winType, winBit, winDes;
//    if(osInfo.isEmpty())
//    {
//#ifdef Q_OS_MAC
//        //方法1
//        //        QString  plistPath = "/System/Library/CoreServices/SystemVersion.plist";
//        //        QSettings readReg(plistPath, QSettings::NativeFormat);
//        //        QString productName = readReg.value("ProductName",QVariant()).toString();
//        //        QString productVersion = readReg.value("ProductVersion", QVariant()).toString();
//        //        osInfo = productName + " " + productVersion;

//        //方法2
//        QString name = QSysInfo::prettyProductName(); // the string may change with update to Qt
//        QString version = QSysInfo::productVersion();
//        osInfo = "macOS " + version;

//        winVer = osInfo;
//#endif

//#ifdef Q_OS_WIN32
//        OSVERSIONINFOEX osvi;
//        SYSTEM_INFO si;
//        PGNSI pGNSI;
//        PGPI pGPI;
//        BOOL bOsVersionInfoEx;
//        DWORD dwType;
//        ZeroMemory(&si, sizeof(SYSTEM_INFO));
//        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
//        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
//        if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *)&osvi)))
//            return 1;

//        // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
//        pGNSI = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
//        if(NULL != pGNSI)
//            pGNSI(&si);
//        else
//            GetSystemInfo(&si);

//        //判断版本
//        if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId && osvi.dwMajorVersion > 4 )
//        {
//            // 测试指定版本号.	//支持到win10
//            //Version 10.0
//            if (10 == osvi.dwMajorVersion && 0 == osvi.dwMinorVersion)
//            {
//                if (osvi.wProductType == VER_NT_WORKSTATION)
//                    winVer = "Windows 10 ";
//                else
//                    winVer = "Windows Server 2016 ";

//                pGPI = (PGPI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
//                pGPI(6, 0, 0, 0, &dwType);

//                switch (dwType)
//                {
//                case PRODUCT_ULTIMATE:
//                    winType = "Ultimate Edition";
//                    break;
//                case PRODUCT_HOME_PREMIUM:
//                    winType = "Home Premium Edition";
//                    break;
//                case PRODUCT_HOME_BASIC:
//                    winType = "Home Basic Edition";
//                    break;
//                case PRODUCT_ENTERPRISE:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_BUSINESS:
//                    winType = "Business Edition";
//                    break;
//                case PRODUCT_STARTER:
//                    winType = "Starter Edition";
//                    break;
//                case PRODUCT_CLUSTER_SERVER:
//                    winType = "Cluster Server Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER:
//                    winType = "Datacenter Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER_CORE:
//                    winType = "Datacenter Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_CORE:
//                    winType = "Enterprise Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_IA64:
//                    winType = "Enterprise Edition for Itanium-based Systems";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER:
//                    winType = "Small Business Server";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
//                    winType = "Small Business Server Premium Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER:
//                    winType = "Standard Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER_CORE:
//                    winType = "Standard Edition (core installation)";
//                    break;
//                case PRODUCT_WEB_SERVER:
//                    winType = "Web Server Edition";
//                    break;
//                }

//                if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
//                    winBit = "64-bit";
//                else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
//                    winBit = "32-bit";
//            }

//            //Version 6.3
//            if (6 == osvi.dwMajorVersion && 3 == osvi.dwMinorVersion)
//            {
//                if (osvi.wProductType == VER_NT_WORKSTATION)
//                    winVer = "Windows 8.1 ";
//                else
//                    winVer = "Windows Server 2012 R2 ";

//                pGPI = (PGPI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
//                pGPI(6, 0, 0, 0, &dwType);

//                switch (dwType)
//                {
//                case PRODUCT_ULTIMATE:
//                    winType = "Ultimate Edition";
//                    break;
//                case PRODUCT_HOME_PREMIUM:
//                    winType = "Home Premium Edition";
//                    break;
//                case PRODUCT_HOME_BASIC:
//                    winType = "Home Basic Edition";
//                    break;
//                case PRODUCT_ENTERPRISE:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_BUSINESS:
//                    winType = "Business Edition";
//                    break;
//                case PRODUCT_STARTER:
//                    winType = "Starter Edition";
//                    break;
//                case PRODUCT_CLUSTER_SERVER:
//                    winType = "Cluster Server Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER:
//                    winType = "Datacenter Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER_CORE:
//                    winType = "Datacenter Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_CORE:
//                    winType = "Enterprise Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_IA64:
//                    winType = "Enterprise Edition for Itanium-based Systems";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER:
//                    winType = "Small Business Server";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
//                    winType = "Small Business Server Premium Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER:
//                    winType = "Standard Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER_CORE:
//                    winType = "Standard Edition (core installation)";
//                    break;
//                case PRODUCT_WEB_SERVER:
//                    winType = "Web Server Edition";
//                    break;
//                }

//                if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
//                    winType = "64-bit";
//                else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
//                    winType = "32-bit";
//            }

//            //Version 6.2
//            if (6 == osvi.dwMajorVersion && 2 == osvi.dwMinorVersion )
//            {
//                if (osvi.wProductType == VER_NT_WORKSTATION)
//                    winVer = "Windows 8 ";
//                else
//                    winVer = "Windows Server 2012 ";

//                pGPI = (PGPI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
//                pGPI(6, 0, 0, 0, &dwType);

//                switch (dwType)
//                {
//                case PRODUCT_ULTIMATE:
//                    winType = "Ultimate Edition";
//                    break;
//                case PRODUCT_HOME_PREMIUM:
//                    winType = "Home Premium Edition";
//                    break;
//                case PRODUCT_HOME_BASIC:
//                    winType = "Home Basic Edition";
//                    break;
//                case PRODUCT_ENTERPRISE:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_BUSINESS:
//                    winType = "Business Edition";
//                    break;
//                case PRODUCT_STARTER:
//                    winType = "Starter Edition";
//                    break;
//                case PRODUCT_CLUSTER_SERVER:
//                    winType = "Cluster Server Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER:
//                    winType = "Datacenter Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER_CORE:
//                    winType = "Datacenter Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_CORE:
//                    winType = "Enterprise Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_IA64:
//                    winType = "Enterprise Edition for Itanium-based Systems";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER:
//                    winType = "Small Business Server";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
//                    winType = "Small Business Server Premium Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER:
//                    winType = "Standard Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER_CORE:
//                    winType = "Standard Edition (core installation)";
//                    break;
//                case PRODUCT_WEB_SERVER:
//                    winType = "Web Server Edition";
//                    break;
//                }

//                if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
//                    winBit = "64-bit";
//                else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
//                    winBit = "32-bit";
//            }

//            //Version 6.1
//            if (6 == osvi.dwMajorVersion && 1 == osvi.dwMinorVersion)
//            {

//                if (osvi.wProductType == VER_NT_WORKSTATION)
//                    winVer = "Windows 7 ";
//                else
//                    winVer = "Windows Server 2008 R2 ";

//                pGPI = (PGPI)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
//                pGPI(6, 0, 0, 0, &dwType);

//                switch (dwType)
//                {
//                case PRODUCT_ULTIMATE:
//                    winType = "Ultimate Edition";
//                    break;
//                case PRODUCT_HOME_PREMIUM:
//                    winType = "Home Premium Edition";
//                    break;
//                case PRODUCT_HOME_BASIC:
//                    winType = "Home Basic Edition";
//                    break;
//                case PRODUCT_ENTERPRISE:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_BUSINESS:
//                    winType = "Business Edition";
//                    break;
//                case PRODUCT_STARTER:
//                    winType = "Starter Edition";
//                    break;
//                case PRODUCT_CLUSTER_SERVER:
//                    winType = "Cluster Server Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER:
//                    winType = "Datacenter Edition";
//                    break;
//                case PRODUCT_DATACENTER_SERVER_CORE:
//                    winType = "Datacenter Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER:
//                    winType = "Enterprise Edition";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_CORE:
//                    winType = "Enterprise Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_IA64:
//                    winType = "Enterprise Edition for Itanium-based Systems";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER:
//                    winType = "Small Business Server";
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
//                    winType = "Small Business Server Premium Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER:
//                    winType = "Standard Edition";
//                    break;
//                case PRODUCT_STANDARD_SERVER_CORE:
//                    winType = "Standard Edition (core installation)";
//                    break;
//                case PRODUCT_WEB_SERVER:
//                    winType = "Web Server Edition";
//                    break;
//                }

//                if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
//                    winBit = "64-bit";
//                else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
//                    winBit = "32-bit";
//            }

//            //version 6.0
//            if (6 == osvi.dwMajorVersion && 0 == osvi.dwMinorVersion )
//            {
//                if( osvi.wProductType == VER_NT_WORKSTATION )
//                    winVer ="Windows Vista ";
//                else
//                    winVer ="Windows Server 2008 ";

//                pGPI = (PGPI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
//                pGPI( 6, 0, 0, 0, &dwType);

//                switch( dwType )
//                {
//                case PRODUCT_ULTIMATE:
//                    winType ="Ultimate Edition" ;
//                    break;
//                case PRODUCT_HOME_PREMIUM:
//                    winType ="Home Premium Edition" ;
//                    break;
//                case PRODUCT_HOME_BASIC:
//                    winType ="Home Basic Edition" ;
//                    break;
//                case PRODUCT_ENTERPRISE:
//                    winType ="Enterprise Edition" ;
//                    break;
//                case PRODUCT_BUSINESS:
//                    winType ="Business Edition" ;
//                    break;
//                case PRODUCT_STARTER:
//                    winType ="Starter Edition" ;
//                    break;
//                case PRODUCT_CLUSTER_SERVER:
//                    winType ="Cluster Server Edition" ;
//                    break;
//                case PRODUCT_DATACENTER_SERVER:
//                    winType ="Datacenter Edition" ;
//                    break;
//                case PRODUCT_DATACENTER_SERVER_CORE:
//                    winType ="Datacenter Edition (core installation)";
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER:
//                    winType ="Enterprise Edition" ;
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_CORE:
//                    winType ="Enterprise Edition (core installation)" ;
//                    break;
//                case PRODUCT_ENTERPRISE_SERVER_IA64:
//                    winType ="Enterprise Edition for Itanium-based Systems" ;
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER:
//                    winType ="Small Business Server" ;
//                    break;
//                case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
//                    winType ="Small Business Server Premium Edition" ;
//                    break;
//                case PRODUCT_STANDARD_SERVER:
//                    winType ="Standard Edition" ;
//                    break;
//                case PRODUCT_STANDARD_SERVER_CORE:
//                    winType ="Standard Edition (core installation)" ;
//                    break;
//                case PRODUCT_WEB_SERVER:
//                    winType ="Web Server Edition";
//                    break;
//                }

//                if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
//                    winBit = "64-bit" ;
//                else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
//                    winBit = "32-bit";
//            }

//            //Version 5.2
//            if (5 == osvi.dwMajorVersion && 2 == osvi.dwMinorVersion)
//            {
//                if( GetSystemMetrics(SM_SERVERR2) )
//                    winVer = "Windows Server 2003 R2, ";
//                else if ( osvi.wSuiteMask==VER_SUITE_STORAGE_SERVER )
//                    winVer ="Windows Storage Server 2003";
//                else if( osvi.wProductType == VER_NT_WORKSTATION &&si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
//                {
//                    winVer = "Windows XP Professional x64 Edition";
//                }
//                else
//                    winVer ="Windows Server 2003, ";

//                // Test for the server type.
//                if ( osvi.wProductType != VER_NT_WORKSTATION )
//                {
//                    if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
//                    {
//                        if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
//                            winType ="Datacenter Edition for Itanium-based Systems" ;
//                        else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
//                            winType = "Enterprise Edition for Itanium-based Systems";
//                    }
//                    else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
//                    {
//                        if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
//                            winType = "Datacenter x64 Edition" ;
//                        else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
//                            winType = "Enterprise x64 Edition" ;
//                        else
//                            winType = "Standard x64 Edition";
//                    }
//                    else
//                    {
//                        if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
//                            winType = "Compute Cluster Edition" ;
//                        else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
//                            winType = "Datacenter Edition";
//                        else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
//                            winType ="Enterprise Edition" ;
//                        else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
//                            winType = "Web Edition" ;
//                        else
//                            winType ="Standard Edition" ;
//                    }
//                }
//            }

//            //Version 5.1
//            if (5 == osvi.dwMajorVersion && 1 == osvi.dwMinorVersion)
//            {
//                winVer = "Windows XP ";

//                if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
//                    winType = "Home Edition" ;
//                else
//                    winType ="Professional" ;
//            }

//            //Version 5.0
//            if (5 == osvi.dwMajorVersion && 0 == osvi.dwMinorVersion)
//            {
//                winVer ="Windows 2000 ";

//                if ( osvi.wProductType == VER_NT_WORKSTATION )
//                {
//                    winType = "Professional" ;
//                }
//                else
//                {
//                    if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
//                        winType = "Datacenter Server" ;
//                    else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
//                        winType ="Advanced Server" ;
//                    else
//                        winType = "Server" ;
//                }
//            }
//            // Include service pack (if any) and build number.
//            winDes = QString::fromWCharArray(osvi.szCSDVersion);
//            winVer += winType;
//            osInfo = QString("%1 %2 %3")
//                    .arg(winVer)
//                    .arg(winBit)
//                    .arg(winDes);
//        }
//        else
//        {
//            printf( "This sample does not support this version of Windows./n");
//            return "";
//        }
//#endif
//    }

//    QString tmpRes;
//    switch(type)
//    {
//    case OS_ALL:
//        tmpRes = osInfo;
//        break;
//    case OS_VER:
//        tmpRes = winVer;
//        break;
//    case OS_BIT:
//        tmpRes = winBit;
//        break;
//    case OS_DES:
//        tmpRes = winDes;
//        break;
//    default:
//        tmpRes = osInfo;
//    }

//    return tmpRes;
//}
