#-------------------------------------------------
#
# Project created by QtCreator 2019-01-21T16:26:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AES_mac
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    AES.cpp \
    base64.cpp

HEADERS  += widget.h \
    AES.h \
    base64.h

FORMS    += widget.ui
