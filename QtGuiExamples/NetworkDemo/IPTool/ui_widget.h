/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QLineEdit *txtLocalIP;
    QPushButton *btnGetLocalIP;
    QLineEdit *txtWebIP;
    QPushButton *btnGetWebIP;
    QLineEdit *txtCheckWeb;
    QPushButton *btnCheckWeb;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(320, 99);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        txtLocalIP = new QLineEdit(Widget);
        txtLocalIP->setObjectName(QStringLiteral("txtLocalIP"));

        gridLayout->addWidget(txtLocalIP, 0, 0, 1, 1);

        btnGetLocalIP = new QPushButton(Widget);
        btnGetLocalIP->setObjectName(QStringLiteral("btnGetLocalIP"));

        gridLayout->addWidget(btnGetLocalIP, 0, 1, 1, 1);

        txtWebIP = new QLineEdit(Widget);
        txtWebIP->setObjectName(QStringLiteral("txtWebIP"));

        gridLayout->addWidget(txtWebIP, 1, 0, 1, 1);

        btnGetWebIP = new QPushButton(Widget);
        btnGetWebIP->setObjectName(QStringLiteral("btnGetWebIP"));

        gridLayout->addWidget(btnGetWebIP, 1, 1, 1, 1);

        txtCheckWeb = new QLineEdit(Widget);
        txtCheckWeb->setObjectName(QStringLiteral("txtCheckWeb"));

        gridLayout->addWidget(txtCheckWeb, 2, 0, 1, 1);

        btnCheckWeb = new QPushButton(Widget);
        btnCheckWeb->setObjectName(QStringLiteral("btnCheckWeb"));

        gridLayout->addWidget(btnCheckWeb, 2, 1, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        btnGetLocalIP->setText(QApplication::translate("Widget", "\350\216\267\345\217\226\346\234\254\346\234\272IP", nullptr));
        btnGetWebIP->setText(QApplication::translate("Widget", "\350\216\267\345\217\226\345\244\226\347\275\221IP", nullptr));
        btnCheckWeb->setText(QApplication::translate("Widget", "\346\243\200\346\265\213\346\230\257\345\220\246\351\200\232\345\244\226\347\275\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
