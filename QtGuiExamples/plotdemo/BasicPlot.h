#ifndef GRAPHPLOT_H
#define GRAPHPLOT_H

#include <QWidget>

#include "PlotDefine.h"

#include "PlotCallback.h"

class QCustomPlot;

class CrossLinePlot;


/// 描述：基础图 支持插入折线、柱状图、散点  如果需要对折线进行后续操作，需要自己保存折线指针，或者直接调用相关接口直接设置
/// 1、图表上水平和垂直方向的提示信息框是根据十字线的横纵线是否显示决定

namespace QCP
{
	Q_DECLARE_FLAGS(AxisRanges, AxisRange);
	Q_DECLARE_FLAGS(QuotaLineTypes, QuotaLineType);
}

struct BasicPlotPrivate;

class BasicPlot : public QWidget
	, public PlotCallback
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(BasicPlot)

protected:
    BasicPlot(QWidget * parent = 0);
public:
	~BasicPlot();

public:
	//折线图新增
	QCPGraph * GetGraph(int index) const;
	QCPGraph * GetGraph() const;
	QCPGraph * AddGraph(QCPAxis * keyAxis = 0, QCPAxis * valueAxis = 0);
	bool RemoveGraph(QCPGraph * graph);
	bool RemoveGraph(int index);
	bool RemoveGraph(const QString & name);
	int ClearGraphs();
	int GraphCount() const;
	QList<QCPGraph *> SelectedGraphs() const;
	//折线数据新增

//	void SetGraphData(const std::vector<stock::LineData> & datas, QCPGraph * graph = nullptr);
    void SetGraphData(const std::vector<double> & key, const std::vector<double> & value, QCPGraph * graph = 0);
	void AddPointData(double key, double value, QCPGraph * graph = nullptr);//新增 数据自动按key排序，可以存在多个key，不能用于更新数据

	//柱状图新增
	QCPBars * AddBars(QCPAxis * keyAxis = 0, QCPAxis * valueAxis = 0);
	//柱状图添加数据
//	void SetBarsData(const std::vector<stock::LineData> & datas, QCPBars * bars = nullptr);
	void SetBarsData(const std::vector<double> & key, const std::vector<double> & value, QCPBars * bars = nullptr);
	void AddBarData(double key, double value, QCPBars * bars = nullptr);//新增 数据自动按key排序，可以存在多个key，不能用于更新数据

	bool RemovePlottable(QCPAbstractPlottable * plottable);
	bool RemovePlottable(const QString & name);

	//图表类型
	void SetPlotType(QCP::ViewType type);
	QCP::ViewType GetPlotType() const;

	//指标类型，当图表类型为空时，该接口才有用
	void SetQuotaType(QCP::QuotaLineType type);
	QCP::QuotaLineType GetQuotaType() const;
	
	//坐标轴范围
	void SetAxisLower(QCPAxis::AxisType type, double lower);
	void SetAxisUpper(QCPAxis::AxisType type, double upper);
	void SetAxisRange(QCPAxis::AxisType type, double lower, double upper);

public:
	//设置坐标轴显示格式
	void SetAxisLabelFormat(QCPAxis::AxisTypes axse, const QString & format);
	void SetAxisLabelPrecision(QCPAxis::AxisTypes axse, int precision);
	void ResetPlot();//重置图表

public:
	//BasePlot
    virtual void SyncAxisRange(QCPAxis::AxisType type, const QCPRange & range) override;
    virtual bool TipLabelEnable() const override;
    virtual void MoveTipLabel(const QPoint & pos) override;
    virtual bool LineTracerEnable() const override;
    virtual void MoveLineTracer(const QPoint & pos) override;

	void SetLineTracerEnable(bool enable);//是否启用tracer
	void SetLineTracerVisible(bool visible, QCPGraph * graph = nullptr);//鼠标移动时，折线图上的小点是否显示
	void SetMoveTipLabel(bool enable);//是否启用十字线顶端的滑块
	void SetToopTipVisible(QCPAxis::AxisTypes axse, bool visible);

	//坐标轴范围是否自动更新
	void SetAutoAxisRange(QCP::AxisRange type, bool enable);
	void SetAutoAxisRange(QCP::AxisRanges axse);

	//设置节点数据展示类型，例如：空心圆、三角形等
	void SetScatterStyle(QCPScatterStyle style, QCPGraph * graph = nullptr);

	//十字线同步
	void SetCrossLineVisible(bool visible);
	CrossLinePlot * GetCrossLine() const;
	bool RegisiterBortherLine(CrossLinePlot * line);
	bool UnregisiterBortherLine(CrossLinePlot * line);

	QCPAxis * GetAxis(QCPAxis::AxisType axis);
	void SetGridVisible(bool visible);
	void SetAxisPen(QCPAxis::AxisTypes axse, const QPen & pen);
	void SetAxisPadding(QCPAxis::AxisType type, int padding);

protected:
    virtual void enterEvent(QEvent * event) override;
    virtual void leaveEvent(QEvent * event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;//暂时不会被执行 由于其子窗口(QCustomPlot)把事件循环中断

protected:
    BasicPlot(BasicPlotPrivate & pd, QWidget * parent = 0);

protected:
	void EnableFixedTicker(QCPAxis::AxisTypes axse);

private:
	void InitializeUI();

protected:
	QScopedPointer<BasicPlotPrivate> d_ptr;

	friend class CrossLinePlot;
};

#endif // GRAPHPLOT_H
