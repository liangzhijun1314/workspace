/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtIn;
    QPushButton *btnAppend;
    QPushButton *btnThread;
    QPushButton *btnTimer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QTextEdit *txtOut;

    void setupUi(QWidget *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QStringLiteral("frmMain"));
        frmMain->resize(695, 515);
        verticalLayout = new QVBoxLayout(frmMain);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(frmMain);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        txtIn = new QLineEdit(frmMain);
        txtIn->setObjectName(QStringLiteral("txtIn"));

        horizontalLayout->addWidget(txtIn);

        btnAppend = new QPushButton(frmMain);
        btnAppend->setObjectName(QStringLiteral("btnAppend"));

        horizontalLayout->addWidget(btnAppend);

        btnThread = new QPushButton(frmMain);
        btnThread->setObjectName(QStringLiteral("btnThread"));

        horizontalLayout->addWidget(btnThread);

        btnTimer = new QPushButton(frmMain);
        btnTimer->setObjectName(QStringLiteral("btnTimer"));

        horizontalLayout->addWidget(btnTimer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(frmMain);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        txtOut = new QTextEdit(frmMain);
        txtOut->setObjectName(QStringLiteral("txtOut"));

        horizontalLayout_2->addWidget(txtOut);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(frmMain);

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QWidget *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "Widget", nullptr));
        label->setText(QApplication::translate("frmMain", "\350\276\223\345\205\245", nullptr));
        txtIn->setText(QApplication::translate("frmMain", "hello", nullptr));
        btnAppend->setText(QApplication::translate("frmMain", "Append", nullptr));
        btnThread->setText(QApplication::translate("frmMain", "start thread", nullptr));
        btnTimer->setText(QApplication::translate("frmMain", "start timer", nullptr));
        label_2->setText(QApplication::translate("frmMain", "\350\276\223\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
