#include "stdafx.h"

#include "TimeSharingTrendPlot.h"
#include "TimeSharingTrendPlot_p.h"

TimeSharingTrendPlot::TimeSharingTrendPlot(QWidget * parent)
	: FinancialPlot(*new TimeSharingTrendPlotPrivate, parent)
{
	d_ptr->m_pPlot->plotLayout()->setRowSpacing(0);

	Q_D(TimeSharingTrendPlot);
	d->m_pMarginGroup = new QCPMarginGroup(d_ptr->m_pPlot);

	d_ptr->m_pPlot->selectionRect()->setPen(QPen(Qt::red));
	d_ptr->m_pPlot->setSelectionRectMode(QCP::srmSelect);

	ShowVOL(true);
}

TimeSharingTrendPlot::TimeSharingTrendPlot(TimeSharingTrendPlotPrivate & pd, QWidget * parent /*= nullptr*/)
	: FinancialPlot(pd, parent)
{
	d_ptr->m_pPlot->plotLayout()->setRowSpacing(0);
	d_ptr->m_pPlot->plotLayout()->clear();

	Q_D(TimeSharingTrendPlot);
	d->m_pMarginGroup = new QCPMarginGroup(d_ptr->m_pPlot);
	d_ptr->m_pPlot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, d->m_pMarginGroup);
}

TimeSharingTrendPlot::~TimeSharingTrendPlot()
{

}

QCPBars * TimeSharingTrendPlot::ShowVOL(bool visible)
{
	Q_D(TimeSharingTrendPlot);
	if (visible)
	{
		if (d->m_eQuota.testFlag(QCP::QT_VOL) == false)
		{
			d->m_eQuota |= QCP::QT_VOL;

			QCPAxisRect *VolAxisRect = new QCPAxisRect(d_ptr->m_pPlot);
			connect(d_ptr->m_pPlot->xAxis, static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged)
				, VolAxisRect->axis(QCPAxis::atBottom), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::setRange));
			connect(VolAxisRect->axis(QCPAxis::atBottom), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged)
				, d_ptr->m_pPlot->xAxis, static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::setRange));
			VolAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
			VolAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
			VolAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
			VolAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
			VolAxisRect->setMargins(QMargins(0, 0, 0, 0));
			d_ptr->m_pPlot->plotLayout()->addElement(1, 0, VolAxisRect);

			VolAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, d->m_pMarginGroup);

			EnableFixedTicker(QCPAxis::atLeft | QCPAxis::atRight);

			//拉取分时图下VOL指标数据
			Q_D(TimeSharingTrendPlot);
			QCPBars * bars = AddBars(VolAxisRect->axis(QCPAxis::atBottom), VolAxisRect->axis(QCPAxis::atLeft));

			return bars;
		}
		else
		{
		}
	}
	else
	{
		d->m_eQuota &= ~QCP::QT_VOL;
		d->m_pPlot->plotLayout()->remove(d_ptr->m_pPlot->plotLayout()->element(1, 0));
	}

	d->m_pPlot->plotLayout()->simplify();

	return nullptr;
}

QCPGraph * TimeSharingTrendPlot::ShowLMR(bool visible)
{
	Q_D(TimeSharingTrendPlot);
	if (visible)
	{
		if (d->m_eQuota.testFlag(QCP::QT_LMR) == false)
		{
			d->m_eQuota |= QCP::QT_LMR;

			QCPAxisRect * LmrAxisRect = new QCPAxisRect(d_ptr->m_pPlot);
			connect(d_ptr->m_pPlot->xAxis, static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged)
				, LmrAxisRect->axis(QCPAxis::atBottom), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::setRange));
			connect(LmrAxisRect->axis(QCPAxis::atBottom), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged)
				, d_ptr->m_pPlot->xAxis, static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::setRange));
			LmrAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
			LmrAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
			LmrAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
			LmrAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
			LmrAxisRect->setMargins(QMargins(0, 0, 0, 0));
			if (d->m_eQuota.testFlag(QCP::QT_VOL))
			{
				d_ptr->m_pPlot->plotLayout()->addElement(2, 0, LmrAxisRect);
			}
			else
			{
				d_ptr->m_pPlot->plotLayout()->addElement(1, 0, LmrAxisRect);
			}

			LmrAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, d->m_pMarginGroup);

			EnableFixedTicker(QCPAxis::atLeft | QCPAxis::atRight);

			//拉取分时图下LMR指标数据
			Q_D(TimeSharingTrendPlot);
			QCPGraph * grahp = AddGraph(LmrAxisRect->axis(QCPAxis::atBottom), LmrAxisRect->axis(QCPAxis::atLeft));
			
			return grahp;
		}
		else
		{
		}
	}
	else
	{
		d->m_eQuota &= ~QCP::QT_LMR;
		if (d->m_eQuota.testFlag(QCP::QT_VOL))
		{
			d_ptr->m_pPlot->plotLayout()->remove(d_ptr->m_pPlot->plotLayout()->element(2, 0));
		}
		else
		{
			d_ptr->m_pPlot->plotLayout()->remove(d_ptr->m_pPlot->plotLayout()->element(1, 0));
		}
	}
	d->m_pPlot->plotLayout()->simplify();
	return nullptr;
}


