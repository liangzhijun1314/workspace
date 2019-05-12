# -------------------------------------------------
# Project created by QtCreator 2010-01-08T15:53:29
# -------------------------------------------------
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = TableViewDemo
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    mytestmodel.cpp \
    exportexcelobject.cpp
HEADERS += mainwindow.h \
    mytestmodel.h \
    exportexcelobject.h
FORMS += mainwindow.ui
