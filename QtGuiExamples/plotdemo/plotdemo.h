#ifndef PLOTDEMO_H
#define PLOTDEMO_H

#include <QWidget>

#include "ui_plotdemo.h"

class QCPItemTracer;

class plotdemo : public QWidget
{
	Q_OBJECT

public:
	plotdemo(QWidget *parent = 0);
	~plotdemo();

private:
    void InitalizeBar();//柱状图
    void InitalizeTable();//
    void InitalizeGraph();//折线图
    void InitalizeScatter();//散射图
    void InitalizeScatter2();//散射图
    void InitalizeVersatility();//多功能图 折线图+柱状图
    void InitalizeColorMap();   //颜色图
    void InitalizeScatter3();//散射图
    void InitalizeGraph2();//实时折线图
    void InitalizeMultipleAxes();//多轴
    void InitalizeLogarithmicAxis();//对数坐标轴
    void InitalizeLine();//一系列线
    void InitalizeDateAxis();//日期轴
    void InitalizeParametricCurves();//参数曲线
    void InitalizeStackedBar();//栈式柱状图
    void InitalizeStatisticalBox();//统计箱
    void InitalizeInteraction();//交互
    void InitalizeItem();//项演示
    void IinitalizeAdvanceAxes();//多轴高级
    void IinitalizeFinancial();//金融
    void Test();

private slots:
//	InitalizeInteraction
//    void removeSelectedGraph();
//    void removeAllGraphs();
//    void selectionChanged();
//    void mousePress();
//    void mouseWheel();
//	void titleDoubleClick(QMouseEvent* event, QCPPlotTitle * title);
//    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
//    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
//    void graphClicked(QCPAbstractPlottable *plottable);
    void addRandomGraph();
//    void contextMenuRequest(QPoint pos);

private:
	Ui::plotdemoClass ui;
    QCPItemTracer * itemDemoPhaseTracer = NULL;
};

#endif // PLOTDEMO_H
