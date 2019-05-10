#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T17:13:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = screen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

# for platform win32
win32 {
DEFINES += OS_WIN
DEFINES += QT_USE
}


# for platform Ubuntu Linux
unix1 {
DEFINES += QT_USE
}

# for Embeded Linux platform
unix {
DEFINES += LINUX_HI
DEFINES += QT_USE
}
