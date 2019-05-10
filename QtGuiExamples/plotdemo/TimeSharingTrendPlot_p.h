#include "FinancialPlot_p.h"

#include "TimeSharingTrendPlot.h"

struct TimeSharingTrendPlotPrivate : public FinancialPlotPrivate
{
	TimeSharingTrendPlotPrivate() : FinancialPlotPrivate(){}
	Q_DECLARE_PUBLIC(TimeSharingTrendPlot)

	QCP::QuotaLineTypes m_eQuota;
	QCPMarginGroup * m_pMarginGroup = nullptr;
};