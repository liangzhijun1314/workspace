/********************************************************************************
** Form generated from reading UI file 'frmshowapi.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSHOWAPI_H
#define UI_FRMSHOWAPI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmShowAPI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labLive;
    QLabel *labDateTime;
    QLabel *labCPUMemory;
    QLCDNumber *lcdNumber;
    QComboBox *cboxColor;
    QTableWidget *tableWidget;

    void setupUi(QWidget *frmShowAPI)
    {
        if (frmShowAPI->objectName().isEmpty())
            frmShowAPI->setObjectName(QStringLiteral("frmShowAPI"));
        frmShowAPI->resize(623, 522);
        verticalLayout = new QVBoxLayout(frmShowAPI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labLive = new QLabel(frmShowAPI);
        labLive->setObjectName(QStringLiteral("labLive"));

        verticalLayout->addWidget(labLive);

        labDateTime = new QLabel(frmShowAPI);
        labDateTime->setObjectName(QStringLiteral("labDateTime"));

        verticalLayout->addWidget(labDateTime);

        labCPUMemory = new QLabel(frmShowAPI);
        labCPUMemory->setObjectName(QStringLiteral("labCPUMemory"));
        labCPUMemory->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(labCPUMemory);

        lcdNumber = new QLCDNumber(frmShowAPI);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(0, 60));
        lcdNumber->setStyleSheet(QStringLiteral(""));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setDigitCount(19);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout->addWidget(lcdNumber);

        cboxColor = new QComboBox(frmShowAPI);
        cboxColor->setObjectName(QStringLiteral("cboxColor"));
        cboxColor->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(cboxColor);

        tableWidget = new QTableWidget(frmShowAPI);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(frmShowAPI);

        QMetaObject::connectSlotsByName(frmShowAPI);
    } // setupUi

    void retranslateUi(QWidget *frmShowAPI)
    {
        frmShowAPI->setWindowTitle(QApplication::translate("frmShowAPI", "Form", nullptr));
        labLive->setText(QString());
        labDateTime->setText(QString());
        labCPUMemory->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frmShowAPI: public Ui_frmShowAPI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSHOWAPI_H
