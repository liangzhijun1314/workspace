#-------------------------------------------------
#
# Project created by QtCreator 2011-11-24T11:31:50
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = myGetColorValueTools
TEMPLATE = app


SOURCES += main.cpp\
        frmmain.cpp

HEADERS  += frmmain.h

FORMS    += frmmain.ui

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj

win32:RC_FILE=main.rc
