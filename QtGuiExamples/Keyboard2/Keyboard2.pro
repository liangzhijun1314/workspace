#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T20:40:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Keyboard2
TEMPLATE = app


SOURCES += main.cpp\
        keyboard.cpp \
    test.cpp \
    this_config.cpp

HEADERS  += keyboard.h \
    test.h \
    this_config.h

FORMS    += keyboard.ui \
    test.ui

RESOURCES += \
    keyboard.qrc
