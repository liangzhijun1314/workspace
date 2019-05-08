/********************************************************************************
** Form generated from reading UI file 'httpdownload.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTTPDOWNLOAD_H
#define UI_HTTPDOWNLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HttpDownload
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *downloadUrl;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *labelStatus;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *labelSpeed;
    QLabel *label_5;
    QLabel *labelRemainTime;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *labelCurrentDownload;
    QLabel *label_3;
    QLabel *labelFileSize;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pButtonStart;
    QPushButton *pButtonStop;
    QPushButton *pButtonClose;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *HttpDownload)
    {
        if (HttpDownload->objectName().isEmpty())
            HttpDownload->setObjectName(QStringLiteral("HttpDownload"));
        HttpDownload->resize(400, 300);
        horizontalLayout_5 = new QHBoxLayout(HttpDownload);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(HttpDownload);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        downloadUrl = new QLineEdit(HttpDownload);
        downloadUrl->setObjectName(QStringLiteral("downloadUrl"));

        horizontalLayout->addWidget(downloadUrl);

        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(HttpDownload);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        labelStatus = new QLabel(HttpDownload);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));

        horizontalLayout_4->addWidget(labelStatus);

        horizontalLayout_4->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_4);

        progressBar = new QProgressBar(HttpDownload);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(HttpDownload);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        labelSpeed = new QLabel(HttpDownload);
        labelSpeed->setObjectName(QStringLiteral("labelSpeed"));

        horizontalLayout_2->addWidget(labelSpeed);

        label_5 = new QLabel(HttpDownload);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        labelRemainTime = new QLabel(HttpDownload);
        labelRemainTime->setObjectName(QStringLiteral("labelRemainTime"));

        horizontalLayout_2->addWidget(labelRemainTime);

        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(HttpDownload);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        labelCurrentDownload = new QLabel(HttpDownload);
        labelCurrentDownload->setObjectName(QStringLiteral("labelCurrentDownload"));

        horizontalLayout_3->addWidget(labelCurrentDownload);

        label_3 = new QLabel(HttpDownload);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        labelFileSize = new QLabel(HttpDownload);
        labelFileSize->setObjectName(QStringLiteral("labelFileSize"));

        horizontalLayout_3->addWidget(labelFileSize);

        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        pButtonStart = new QPushButton(HttpDownload);
        pButtonStart->setObjectName(QStringLiteral("pButtonStart"));

        verticalLayout_2->addWidget(pButtonStart);

        pButtonStop = new QPushButton(HttpDownload);
        pButtonStop->setObjectName(QStringLiteral("pButtonStop"));

        verticalLayout_2->addWidget(pButtonStop);

        pButtonClose = new QPushButton(HttpDownload);
        pButtonClose->setObjectName(QStringLiteral("pButtonClose"));

        verticalLayout_2->addWidget(pButtonClose);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_5->addLayout(verticalLayout_2);


        retranslateUi(HttpDownload);

        QMetaObject::connectSlotsByName(HttpDownload);
    } // setupUi

    void retranslateUi(QWidget *HttpDownload)
    {
        HttpDownload->setWindowTitle(QApplication::translate("HttpDownload", "Form", nullptr));
        label->setText(QApplication::translate("HttpDownload", "\344\270\213\350\275\275\351\223\276\346\216\245\357\274\232", nullptr));
        label_6->setText(QApplication::translate("HttpDownload", "\344\270\213\350\275\275\347\212\266\346\200\201\357\274\232", nullptr));
        labelStatus->setText(QString());
        label_4->setText(QApplication::translate("HttpDownload", "\344\270\213\350\275\275\351\200\237\345\272\246\357\274\232", nullptr));
        labelSpeed->setText(QString());
        label_5->setText(QApplication::translate("HttpDownload", "\345\211\251\344\275\231\346\227\266\351\227\264\357\274\232", nullptr));
        labelRemainTime->setText(QString());
        label_2->setText(QApplication::translate("HttpDownload", "\345\275\223\345\211\215\345\244\247\345\260\217\357\274\232", nullptr));
        labelCurrentDownload->setText(QString());
        label_3->setText(QApplication::translate("HttpDownload", "\346\200\273\345\244\247\345\260\217\357\274\232", nullptr));
        labelFileSize->setText(QString());
        pButtonStart->setText(QApplication::translate("HttpDownload", "start", nullptr));
        pButtonStop->setText(QApplication::translate("HttpDownload", "stop", nullptr));
        pButtonClose->setText(QApplication::translate("HttpDownload", "close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HttpDownload: public Ui_HttpDownload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTTPDOWNLOAD_H
