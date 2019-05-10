#include "BasicPlot.h"

#include "TimeSharingTrendPlot.h"

struct BasicWidgetPrivate
{
	Q_DECLARE_PUBLIC(BasicWidget);

	PlotWidget * m_pWrapwidget = nullptr;
	std::map<QCP::QuotaLineType, QCPAbstractPlottable *> m_QuotaGrahpMap;

	struct LineMark
	{
		QCPItemStraightLine * lineMark = nullptr;
		QCPAbstractPlottable * graph = nullptr;
	};
	LineMark * m_PresentPriceLine = nullptr;

	BasicPlot * m_pPlot = nullptr;
	BasicWidget * q_ptr;

public:
	void Init()
	{
		m_PresentPriceLine = new LineMark;
	}
};