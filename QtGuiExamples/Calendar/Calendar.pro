#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T13:51:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyCalendar
TEMPLATE = app


SOURCES += main.cpp\
        mycalendar.cpp \
    DefDateTimeEdit.cpp \
    DefineCalendar.cpp

HEADERS  += mycalendar.h \
    DefDateTimeEdit.h \
    DefineCalendar.h

FORMS    += mycalendar.ui
