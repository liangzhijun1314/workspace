#include "FinancialWidget.h"

#include "BasicWidget_p.h"

struct FinancialWidgetPrivate : public BasicWidgetPrivate
{
	Q_DECLARE_PUBLIC(FinancialWidget)
	FinancialWidgetPrivate() :BasicWidgetPrivate()
	{
		m_pPlot = new FinancialPlot;
	}
};