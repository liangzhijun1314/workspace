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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBoxCodecSource;
    QLabel *label_2;
    QComboBox *comboBoxCodecDest;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnProject;
    QPushButton *btnChange;
    QTextBrowser *textBrowser;
    QLabel *labelStatus;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(782, 433);
        Widget->setStyleSheet(QLatin1String("QPushButton {\n"
"	border: 1px solid #AEAEAE;\n"
"	border-radius: 0;\n"
"	color: #000000;\n"
"	min-width: 100px;\n"
"	min-height: 25px;\n"
"	padding: 0px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: #ffffff;\n"
"	background-color: #448ACA;\n"
"}\n"
"\n"
"QComboBox{\n"
"    border-radius: 0px;\n"
"    padding: 1px 10px 1px 5px;\n"
"    border: 1px solid #AEAEAE;\n"
"	min-width: 100px;\n"
"	min-height: 20px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"    border-left-width: 1px;\n"
"    border-left-style: solid;\n"
"    border-left-color: #DCDCDC;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    background-color: #DCDCDC;\n"
"}\n"
"\n"
"QLabel#labelStatus {\n"
"	color: #0000ff;\n"
"}\n"
"\n"
"QTextBrowser {\n"
"	border: 1px solid #AEAEAE;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"\n"
"QScrollBar:vertical {\n"
"    width:10px;\n"
"    background-color:#ffffff;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    height:"
                        "10px;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    width:10px;\n"
"	height: 100px;\n"
"    background: #D3D3D3;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    height:10px;\n"
"    background: #D3D3D3;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    width:10px;\n"
"    background: #C9C9C9;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    height:10px;\n"
"    background: #C9C9C9;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical {\n"
"    height:0px;\n"
"    width:0px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"    height:0px;\n"
"    width:0px;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical {\n"
"    height:0px;\n"
"    width:0px;\n"
"}\n"
"\n"
""));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBoxCodecSource = new QComboBox(Widget);
        comboBoxCodecSource->addItem(QString());
        comboBoxCodecSource->addItem(QString());
        comboBoxCodecSource->setObjectName(QStringLiteral("comboBoxCodecSource"));

        horizontalLayout->addWidget(comboBoxCodecSource);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBoxCodecDest = new QComboBox(Widget);
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->addItem(QString());
        comboBoxCodecDest->setObjectName(QStringLiteral("comboBoxCodecDest"));

        horizontalLayout->addWidget(comboBoxCodecDest);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnProject = new QPushButton(Widget);
        btnProject->setObjectName(QStringLiteral("btnProject"));

        horizontalLayout->addWidget(btnProject);

        btnChange = new QPushButton(Widget);
        btnChange->setObjectName(QStringLiteral("btnChange"));
        btnChange->setMaximumSize(QSize(100, 25));

        horizontalLayout->addWidget(btnChange);


        verticalLayout->addLayout(horizontalLayout);

        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        labelStatus = new QLabel(Widget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(labelStatus);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\272\220\346\226\207\344\273\266\347\274\226\347\240\201\357\274\232", nullptr));
        comboBoxCodecSource->setItemText(0, QApplication::translate("Widget", "UTF8", nullptr));
        comboBoxCodecSource->setItemText(1, QApplication::translate("Widget", "GB18030", nullptr));

        label_2->setText(QApplication::translate("Widget", "\347\233\256\346\240\207\346\226\207\344\273\266\347\274\226\347\240\201\357\274\232", nullptr));
        comboBoxCodecDest->setItemText(0, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(1, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(2, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(3, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(4, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(5, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(6, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(7, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(8, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(9, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBoxCodecDest->setItemText(10, QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));

        btnProject->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\351\241\271\347\233\256", nullptr));
        btnChange->setText(QApplication::translate("Widget", "\350\275\254\346\215\242", nullptr));
        labelStatus->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
