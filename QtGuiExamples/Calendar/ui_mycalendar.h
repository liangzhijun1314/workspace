/********************************************************************************
** Form generated from reading UI file 'mycalendar.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCALENDAR_H
#define UI_MYCALENDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyCalendarClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyCalendarClass)
    {
        if (MyCalendarClass->objectName().isEmpty())
            MyCalendarClass->setObjectName(QStringLiteral("MyCalendarClass"));
        MyCalendarClass->resize(600, 400);
        menuBar = new QMenuBar(MyCalendarClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyCalendarClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyCalendarClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyCalendarClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyCalendarClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyCalendarClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyCalendarClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyCalendarClass->setStatusBar(statusBar);

        retranslateUi(MyCalendarClass);

        QMetaObject::connectSlotsByName(MyCalendarClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyCalendarClass)
    {
        MyCalendarClass->setWindowTitle(QApplication::translate("MyCalendarClass", "MyCalendar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyCalendarClass: public Ui_MyCalendarClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCALENDAR_H
