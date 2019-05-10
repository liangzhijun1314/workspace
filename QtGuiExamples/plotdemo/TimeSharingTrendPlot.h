#ifndef MUTIAXESPLOT_H
#define MUTIAXESPLOT_H

#include <memory>

#include "FinancialPlot.h"

struct TimeSharingTrendPlotPrivate;


/// 描述：金融图，主要用于展示分时图，图表中可以包含多个纵轴，但是只有一个横轴


class TimeSharingTrendPlot : public FinancialPlot
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(TimeSharingTrendPlot)

protected:
	TimeSharingTrendPlot(QWidget * parent = nullptr);
public:
	~TimeSharingTrendPlot();

public:
	//指标控制
	QCPBars * ShowVOL(bool visible);//
	QCPGraph * ShowLMR(bool visible);//量比

protected:
	TimeSharingTrendPlot(TimeSharingTrendPlotPrivate & pd, QWidget * parent = nullptr);


	friend class TimeSharingTrendWidgetPrivate;
};

#endif // MUTIAXESPLOT_H
