QT += core
QT -= gui

CONFIG += c++11

TARGET = AES
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    AESCrypt.cpp \
    AESEncryptor.cpp \
    AES.cpp \
    base64.cpp

HEADERS += \
    AESCrypt.h \
    AESEncryptor.h \
    AES.h \
    base64.h

win32:{
QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
}
