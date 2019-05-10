#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T10:52:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plotdemo
TEMPLATE = app


SOURCES += main.cpp\
        plotdemo.cpp \
    AxisFixedPixelTicker.cpp \
    BasicPlot.cpp \
    BasicWidget.cpp \
    CrossLinePlot.cpp \
    FinancialPlot.cpp \
    FinancialWidget.cpp \
    PlotWidget.cpp \
    QCustomplot.cpp \
    stdafx.cpp \
    TimeSharingTrendPlot.cpp \
    TimeSharingTrendWidget.cpp

HEADERS  += plotdemo.h \
    AxisFixedPixelTicker.h \
    BasicPlot.h \
    BasicPlot_p.h \
    BasicWidget.h \
    BasicWidget_p.h \
    CrossLinePlot.h \
    FinancialPlot.h \
    FinancialPlot_p.h \
    FinancialWidget.h \
    FinancialWidget_p.h \
    IStockCommon.h \
    PlotCallback.h \
    PlotDefine.h \
    PlotWidget.h \
    QCustomplot.h \
    stdafx.h \
    TimeSharingTrendPlot.h \
    TimeSharingTrendPlot_p.h \
    TimeSharingTrendWidget.h \
    TimeSharingTrendWidget_p.h

FORMS    += plotdemo.ui

RESOURCES += \
    plotdemo.qrc
