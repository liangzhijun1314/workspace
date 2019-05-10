#ifndef TIMESHARINGTRENDWIDGET_H
#define TIMESHARINGTRENDWIDGET_H

#include <QWidget>

#include "BasicPlot.h"
#include "BasicWidget.h"


struct TimeSharingTrendWidgetPrivate;

class TimeSharingTrendPlot;


/// 描述：分时图窗口类，内部嵌入TimeSharingTrendPlot绘图组建。具有接收数据的能力，可以直接被使用或者配合PlotWidget使用

class TimeSharingTrendWidget : public BasicWidget//, public stock::ITimeLineObserve
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(TimeSharingTrendWidget)

public:
	TimeSharingTrendWidget(QWidget * parent = nullptr);
	~TimeSharingTrendWidget();

public:	
	//图表类型
// 	void SetPlotType(stock::TViewType type);
// 	stock::TViewType GetPlotType() const;
// 
// 	//指标类型，当图表类型为空时，该接口才有用
// 	void SetQuotaType(stock::TLineQuotaType type);
// 	stock::TLineQuotaType GettQuotaType() const;

	TimeSharingTrendPlot * GetTimeSharingTrendPlot() const;
	virtual void SetPresentPriceVisible(bool visible) override;

protected:
	//stock::ITimeLineObserve
	//virtual void OnUpdate2(const stock::TLineQuotaType & type, const DataContainer<stock::LineData> & data) override;

private:
	void InitializeUI();
	void DisposeQuotaData(QCP::QuotaLineType type);

private:
};

#endif // TIMESHARINGTRENDWIDGET_H
