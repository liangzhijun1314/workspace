#include "BasicPlot_p.h"

#include "FinancialPlot.h"

struct FinancialPlotPrivate : public BasicPlotPrivate
{
	FinancialPlotPrivate() : BasicPlotPrivate(){}
	Q_DECLARE_PUBLIC(FinancialPlot)
	Qt::CursorShape m_eShape;
};