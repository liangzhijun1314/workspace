#include "BasicWidget_p.h"
#include "TimeSharingTrendPlot.h"

#include "TimeSharingTrendWidget.h"

struct TimeSharingTrendWidgetPrivate : public BasicWidgetPrivate
{
	Q_DECLARE_PUBLIC(TimeSharingTrendWidget);

	TimeSharingTrendWidgetPrivate() :BasicWidgetPrivate()
	{
		m_pPlot = new TimeSharingTrendPlot;
	}
	std::map<QCP::QuotaLineType, QCPAbstractPlottable *> m_PlotMap;
};