/********************************************************************************
** Form generated from reading UI file 'plotdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDEMO_H
#define UI_PLOTDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_plotdemoClass
{
public:
    QGridLayout *gridLayout_24;
    QTabWidget *tabWidget;
    QWidget *tab_tableWidget;
    QGridLayout *gridLayout_3;
    QTableWidget *widget_tableWidget;
    QWidget *tab_bar;
    QGridLayout *gridLayout_2;
    QCustomPlot *widget;
    QWidget *tab_flow;
    QGridLayout *gridLayout_4;
    QWidget *widget_2;
    QWidget *tab_graph;
    QGridLayout *gridLayout_5;
    QCustomPlot *widget_3;
    QWidget *tab_scatter;
    QGridLayout *gridLayout_6;
    QCustomPlot *widget_4;
    QWidget *tab_scatter_point;
    QGridLayout *gridLayout_7;
    QCustomPlot *widget_5;
    QWidget *tab_versatility;
    QGridLayout *gridLayout_8;
    QCustomPlot *widget_6;
    QWidget *tab_color_map;
    QGridLayout *gridLayout_9;
    QCustomPlot *widget_7;
    QWidget *tab_scatter_pixmap;
    QGridLayout *gridLayout_10;
    QCustomPlot *widget_8;
    QWidget *tab_realtime_graph;
    QGridLayout *gridLayout_11;
    QCustomPlot *widget_9;
    QWidget *tab_multiple_axes;
    QGridLayout *gridLayout_12;
    QCustomPlot *widget_10;
    QWidget *tab_logarithmicaxis;
    QGridLayout *gridLayout_13;
    QCustomPlot *widget_11;
    QWidget *tab_line;
    QGridLayout *gridLayout_17;
    QCustomPlot *widget_12;
    QWidget *tab__date;
    QGridLayout *gridLayout_16;
    QCustomPlot *widget_13;
    QWidget *tab_parametric_curves;
    QGridLayout *gridLayout_15;
    QCustomPlot *widget_14;
    QWidget *tab_stacked_bar;
    QGridLayout *gridLayout_14;
    QCustomPlot *widget_15;
    QWidget *tab_statistical_box;
    QGridLayout *gridLayout_18;
    QCustomPlot *widget_16;
    QWidget *tab_interaction;
    QGridLayout *gridLayout_19;
    QCustomPlot *widget_17;
    QWidget *tab_item;
    QGridLayout *gridLayout_20;
    QCustomPlot *widget_18;
    QWidget *tab_advance_axes;
    QGridLayout *gridLayout_21;
    QCustomPlot *widget_19;
    QWidget *tab_financial;
    QGridLayout *gridLayout_22;
    QCustomPlot *widget_20;
    QWidget *tab;
    QGridLayout *gridLayout_23;
    QWidget *widget_21;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *widget_22;
    QCustomPlot *widget_23;

    void setupUi(QWidget *plotdemoClass)
    {
        if (plotdemoClass->objectName().isEmpty())
            plotdemoClass->setObjectName(QStringLiteral("plotdemoClass"));
        plotdemoClass->resize(980, 770);
        gridLayout_24 = new QGridLayout(plotdemoClass);
        gridLayout_24->setSpacing(0);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QStringLiteral("gridLayout_24"));
        gridLayout_24->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(plotdemoClass);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_tableWidget = new QWidget();
        tab_tableWidget->setObjectName(QStringLiteral("tab_tableWidget"));
        gridLayout_3 = new QGridLayout(tab_tableWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_tableWidget = new QTableWidget(tab_tableWidget);
        widget_tableWidget->setObjectName(QStringLiteral("widget_tableWidget"));

        gridLayout_3->addWidget(widget_tableWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab_tableWidget, QString());
        tab_bar = new QWidget();
        tab_bar->setObjectName(QStringLiteral("tab_bar"));
        gridLayout_2 = new QGridLayout(tab_bar);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QCustomPlot(tab_bar);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(tab_bar, QString());
        tab_flow = new QWidget();
        tab_flow->setObjectName(QStringLiteral("tab_flow"));
        gridLayout_4 = new QGridLayout(tab_flow);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(tab_flow);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        gridLayout_4->addWidget(widget_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_flow, QString());
        tab_graph = new QWidget();
        tab_graph->setObjectName(QStringLiteral("tab_graph"));
        gridLayout_5 = new QGridLayout(tab_graph);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QCustomPlot(tab_graph);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        gridLayout_5->addWidget(widget_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_graph, QString());
        tab_scatter = new QWidget();
        tab_scatter->setObjectName(QStringLiteral("tab_scatter"));
        gridLayout_6 = new QGridLayout(tab_scatter);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QCustomPlot(tab_scatter);
        widget_4->setObjectName(QStringLiteral("widget_4"));

        gridLayout_6->addWidget(widget_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_scatter, QString());
        tab_scatter_point = new QWidget();
        tab_scatter_point->setObjectName(QStringLiteral("tab_scatter_point"));
        gridLayout_7 = new QGridLayout(tab_scatter_point);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QCustomPlot(tab_scatter_point);
        widget_5->setObjectName(QStringLiteral("widget_5"));

        gridLayout_7->addWidget(widget_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_scatter_point, QString());
        tab_versatility = new QWidget();
        tab_versatility->setObjectName(QStringLiteral("tab_versatility"));
        gridLayout_8 = new QGridLayout(tab_versatility);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        widget_6 = new QCustomPlot(tab_versatility);
        widget_6->setObjectName(QStringLiteral("widget_6"));

        gridLayout_8->addWidget(widget_6, 0, 0, 1, 1);

        tabWidget->addTab(tab_versatility, QString());
        tab_color_map = new QWidget();
        tab_color_map->setObjectName(QStringLiteral("tab_color_map"));
        gridLayout_9 = new QGridLayout(tab_color_map);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        widget_7 = new QCustomPlot(tab_color_map);
        widget_7->setObjectName(QStringLiteral("widget_7"));

        gridLayout_9->addWidget(widget_7, 0, 0, 1, 1);

        tabWidget->addTab(tab_color_map, QString());
        tab_scatter_pixmap = new QWidget();
        tab_scatter_pixmap->setObjectName(QStringLiteral("tab_scatter_pixmap"));
        gridLayout_10 = new QGridLayout(tab_scatter_pixmap);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        widget_8 = new QCustomPlot(tab_scatter_pixmap);
        widget_8->setObjectName(QStringLiteral("widget_8"));

        gridLayout_10->addWidget(widget_8, 0, 0, 1, 1);

        tabWidget->addTab(tab_scatter_pixmap, QString());
        tab_realtime_graph = new QWidget();
        tab_realtime_graph->setObjectName(QStringLiteral("tab_realtime_graph"));
        gridLayout_11 = new QGridLayout(tab_realtime_graph);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        widget_9 = new QCustomPlot(tab_realtime_graph);
        widget_9->setObjectName(QStringLiteral("widget_9"));

        gridLayout_11->addWidget(widget_9, 0, 0, 1, 1);

        tabWidget->addTab(tab_realtime_graph, QString());
        tab_multiple_axes = new QWidget();
        tab_multiple_axes->setObjectName(QStringLiteral("tab_multiple_axes"));
        gridLayout_12 = new QGridLayout(tab_multiple_axes);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        widget_10 = new QCustomPlot(tab_multiple_axes);
        widget_10->setObjectName(QStringLiteral("widget_10"));

        gridLayout_12->addWidget(widget_10, 0, 0, 1, 1);

        tabWidget->addTab(tab_multiple_axes, QString());
        tab_logarithmicaxis = new QWidget();
        tab_logarithmicaxis->setObjectName(QStringLiteral("tab_logarithmicaxis"));
        gridLayout_13 = new QGridLayout(tab_logarithmicaxis);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, -1, 0);
        widget_11 = new QCustomPlot(tab_logarithmicaxis);
        widget_11->setObjectName(QStringLiteral("widget_11"));

        gridLayout_13->addWidget(widget_11, 0, 0, 1, 1);

        tabWidget->addTab(tab_logarithmicaxis, QString());
        tab_line = new QWidget();
        tab_line->setObjectName(QStringLiteral("tab_line"));
        gridLayout_17 = new QGridLayout(tab_line);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        gridLayout_17->setContentsMargins(0, 0, 0, 0);
        widget_12 = new QCustomPlot(tab_line);
        widget_12->setObjectName(QStringLiteral("widget_12"));

        gridLayout_17->addWidget(widget_12, 0, 0, 1, 1);

        tabWidget->addTab(tab_line, QString());
        tab__date = new QWidget();
        tab__date->setObjectName(QStringLiteral("tab__date"));
        gridLayout_16 = new QGridLayout(tab__date);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gridLayout_16->setContentsMargins(0, 0, 0, 0);
        widget_13 = new QCustomPlot(tab__date);
        widget_13->setObjectName(QStringLiteral("widget_13"));

        gridLayout_16->addWidget(widget_13, 0, 0, 1, 1);

        tabWidget->addTab(tab__date, QString());
        tab_parametric_curves = new QWidget();
        tab_parametric_curves->setObjectName(QStringLiteral("tab_parametric_curves"));
        gridLayout_15 = new QGridLayout(tab_parametric_curves);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        widget_14 = new QCustomPlot(tab_parametric_curves);
        widget_14->setObjectName(QStringLiteral("widget_14"));

        gridLayout_15->addWidget(widget_14, 0, 0, 1, 1);

        tabWidget->addTab(tab_parametric_curves, QString());
        tab_stacked_bar = new QWidget();
        tab_stacked_bar->setObjectName(QStringLiteral("tab_stacked_bar"));
        gridLayout_14 = new QGridLayout(tab_stacked_bar);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_14->setContentsMargins(0, 0, 0, 0);
        widget_15 = new QCustomPlot(tab_stacked_bar);
        widget_15->setObjectName(QStringLiteral("widget_15"));

        gridLayout_14->addWidget(widget_15, 0, 0, 1, 1);

        tabWidget->addTab(tab_stacked_bar, QString());
        tab_statistical_box = new QWidget();
        tab_statistical_box->setObjectName(QStringLiteral("tab_statistical_box"));
        gridLayout_18 = new QGridLayout(tab_statistical_box);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        gridLayout_18->setContentsMargins(0, 0, 0, 0);
        widget_16 = new QCustomPlot(tab_statistical_box);
        widget_16->setObjectName(QStringLiteral("widget_16"));

        gridLayout_18->addWidget(widget_16, 0, 0, 1, 1);

        tabWidget->addTab(tab_statistical_box, QString());
        tab_interaction = new QWidget();
        tab_interaction->setObjectName(QStringLiteral("tab_interaction"));
        gridLayout_19 = new QGridLayout(tab_interaction);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        gridLayout_19->setContentsMargins(0, 0, 0, 0);
        widget_17 = new QCustomPlot(tab_interaction);
        widget_17->setObjectName(QStringLiteral("widget_17"));

        gridLayout_19->addWidget(widget_17, 0, 0, 1, 1);

        tabWidget->addTab(tab_interaction, QString());
        tab_item = new QWidget();
        tab_item->setObjectName(QStringLiteral("tab_item"));
        gridLayout_20 = new QGridLayout(tab_item);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QStringLiteral("gridLayout_20"));
        gridLayout_20->setContentsMargins(0, 0, 0, 0);
        widget_18 = new QCustomPlot(tab_item);
        widget_18->setObjectName(QStringLiteral("widget_18"));

        gridLayout_20->addWidget(widget_18, 0, 0, 1, 1);

        tabWidget->addTab(tab_item, QString());
        tab_advance_axes = new QWidget();
        tab_advance_axes->setObjectName(QStringLiteral("tab_advance_axes"));
        gridLayout_21 = new QGridLayout(tab_advance_axes);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QStringLiteral("gridLayout_21"));
        gridLayout_21->setContentsMargins(0, 0, 0, 0);
        widget_19 = new QCustomPlot(tab_advance_axes);
        widget_19->setObjectName(QStringLiteral("widget_19"));

        gridLayout_21->addWidget(widget_19, 0, 0, 1, 1);

        tabWidget->addTab(tab_advance_axes, QString());
        tab_financial = new QWidget();
        tab_financial->setObjectName(QStringLiteral("tab_financial"));
        gridLayout_22 = new QGridLayout(tab_financial);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QStringLiteral("gridLayout_22"));
        gridLayout_22->setContentsMargins(0, 0, 0, 0);
        widget_20 = new QCustomPlot(tab_financial);
        widget_20->setObjectName(QStringLiteral("widget_20"));

        gridLayout_22->addWidget(widget_20, 0, 0, 1, 1);

        tabWidget->addTab(tab_financial, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_23 = new QGridLayout(tab);
        gridLayout_23->setSpacing(0);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        gridLayout_23->setContentsMargins(0, 0, 0, 0);
        widget_21 = new QWidget(tab);
        widget_21->setObjectName(QStringLiteral("widget_21"));
        gridLayout = new QGridLayout(widget_21);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(widget_21);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setLineWidth(1);
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(5);
        widget_22 = new QWidget(splitter);
        widget_22->setObjectName(QStringLiteral("widget_22"));
        widget_22->setMaximumSize(QSize(16777215, 16777215));
        splitter->addWidget(widget_22);
        widget_23 = new QCustomPlot(splitter);
        widget_23->setObjectName(QStringLiteral("widget_23"));
        widget_23->setMaximumSize(QSize(16777215, 16777215));
        splitter->addWidget(widget_23);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        gridLayout_23->addWidget(widget_21, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_24->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(plotdemoClass);

        tabWidget->setCurrentIndex(8);


        QMetaObject::connectSlotsByName(plotdemoClass);
    } // setupUi

    void retranslateUi(QWidget *plotdemoClass)
    {
        plotdemoClass->setWindowTitle(QApplication::translate("plotdemoClass", "plotdemo", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_tableWidget), QApplication::translate("plotdemoClass", "\350\241\250\346\240\274", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_bar), QApplication::translate("plotdemoClass", "\346\237\261\347\212\266\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_flow), QApplication::translate("plotdemoClass", "\346\265\201\345\270\203\345\261\200", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_graph), QApplication::translate("plotdemoClass", "\346\212\230\347\272\277\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_scatter), QApplication::translate("plotdemoClass", "\346\225\243\345\260\204\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_scatter_point), QApplication::translate("plotdemoClass", "\346\225\243\345\260\204\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_versatility), QApplication::translate("plotdemoClass", "\345\244\232\345\212\237\350\203\275\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_color_map), QApplication::translate("plotdemoClass", "\351\242\234\350\211\262\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_scatter_pixmap), QApplication::translate("plotdemoClass", "\346\225\243\345\260\204\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_realtime_graph), QApplication::translate("plotdemoClass", "\345\256\236\346\227\266\346\212\230\347\272\277\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_multiple_axes), QApplication::translate("plotdemoClass", "\345\244\232\350\275\264", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_logarithmicaxis), QApplication::translate("plotdemoClass", "\345\257\271\346\225\260\350\275\264", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_line), QApplication::translate("plotdemoClass", "\347\263\273\345\210\227\347\272\277", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab__date), QApplication::translate("plotdemoClass", "\346\227\245\346\234\237\350\275\264", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_parametric_curves), QApplication::translate("plotdemoClass", "\345\217\202\346\225\260\346\233\262\347\272\277", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_stacked_bar), QApplication::translate("plotdemoClass", "\346\240\210\345\274\217\346\237\261\347\212\266\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_statistical_box), QApplication::translate("plotdemoClass", "\347\273\237\350\256\241\347\256\261", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_interaction), QApplication::translate("plotdemoClass", "\344\272\244\344\272\222", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_item), QApplication::translate("plotdemoClass", "\351\241\271\347\233\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_advance_axes), QApplication::translate("plotdemoClass", "\351\253\230\347\272\247\345\244\232\350\275\264", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_financial), QApplication::translate("plotdemoClass", "\351\207\221\350\236\215\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("plotdemoClass", "\346\265\213\350\257\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class plotdemoClass: public Ui_plotdemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDEMO_H
