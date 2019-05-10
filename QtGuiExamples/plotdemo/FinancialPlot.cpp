#include "stdafx.h"

#include "FinancialPlot.h"
#include "FinancialPlot_p.h"

FinancialPlot::FinancialPlot(QWidget * parent)
	: BasicPlot(*new FinancialPlotPrivate, parent)
{
	SetDragOrientation(Qt::Horizontal);
	SetZoomOrientation(Qt::Horizontal | Qt::Vertical);

	//默认为k线
	SetVerticalAxisSynch(true);
	setMouseTracking(true);
}

FinancialPlot::FinancialPlot(FinancialPlotPrivate & pd, QWidget * parent /*= nullptr*/)
	: BasicPlot(pd, parent)
{
	SetDragOrientation(Qt::Horizontal | Qt::Vertical);
	SetZoomOrientation(Qt::Horizontal | Qt::Vertical);

	//默认为k线
	SetVerticalAxisSynch(true);
	setMouseTracking(true);
}

FinancialPlot::~FinancialPlot()
{

}

void FinancialPlot::SetInteractions(const QCP::Interactions & interactions)
{
	d_ptr->m_pPlot->setInteractions(interactions);
}

void FinancialPlot::SetDragOrientation(Qt::Orientations orientations)
{
	d_ptr->m_pPlot->axisRect()->setRangeDrag(orientations);
}

void FinancialPlot::SetZoomOrientation(Qt::Orientations orientations)
{
	d_ptr->m_pPlot->axisRect()->setRangeZoom(orientations);
}

void FinancialPlot::SetCursorShape(Qt::CursorShape  shape)
{
	Q_D(FinancialPlot);
	d->m_eShape = shape;
	switch (d->m_eShape)
	{
	case Qt::ClosedHandCursor:
		SetInteractions(d_ptr->m_pPlot->interactions() | QCP::iRangeDrag | QCP::iRangeZoom);
		break;
	case Qt::ArrowCursor:
		SetInteractions(d_ptr->m_pPlot->interactions() & ~QCP::iRangeDrag & ~QCP::iRangeZoom);
		break;
	default:
		SetInteractions(d_ptr->m_pPlot->interactions() & ~QCP::iRangeDrag & ~QCP::iRangeZoom);
		break;
	}
	setCursor(d->m_eShape);
}

void FinancialPlot::SetVerticalAxisSynch(bool synch)
{
	if (synch)
	{
		connect(d_ptr->m_pPlot->xAxis, static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged), this, [this](const QCPRange & range){
			AxisRangeChanged(QCPAxis::atBottom, range);
		});
	}
	else
	{
		d_ptr->m_pPlot->xAxis->disconnect(this);
	}
}

bool FinancialPlot::RegisiterBrotherRange(QCPAxis::AxisType type, PlotCallback * plot)
{
	//重置步长
	// 	if (plot->GetAxis(type)->tickStep() != GetAxis(type)->tickStep())
	// 	{
	// 		plot->GetAxis(type)->setTickStep(GetAxis(type)->tickStep());
	// 	}

	//重置交互行为
	//if (plot->d_ptr->m_pPlot->interactions() != d_ptr->m_pPlot->interactions())
	//{
	//	plot->d_ptr->m_pPlot->setInteractions(d_ptr->m_pPlot->interactions());
	//}

	if (FinancialPlotPrivate::m_BrotherAxisRange.find(type) == FinancialPlotPrivate::m_BrotherAxisRange.end())
	{
		FinancialPlotPrivate::m_BrotherAxisRange[type].push_back(this);
		FinancialPlotPrivate::m_BrotherAxisRange[type].push_back(plot);
	}
	else
	{
		auto iter = std::find(FinancialPlotPrivate::m_BrotherAxisRange[type].begin(), FinancialPlotPrivate::m_BrotherAxisRange[type].end(), plot);
		if (iter == FinancialPlotPrivate::m_BrotherAxisRange[type].end())
		{
			FinancialPlotPrivate::m_BrotherAxisRange[type].push_back(plot);
		}
	}
	return true;
}

bool FinancialPlot::UnregisiterBrotherRange(QCPAxis::AxisType type, PlotCallback * plot)
{
	if (FinancialPlotPrivate::m_BrotherAxisRange.find(type) != FinancialPlotPrivate::m_BrotherAxisRange.end())
	{
		auto iter = std::find(FinancialPlotPrivate::m_BrotherAxisRange[type].begin(), FinancialPlotPrivate::m_BrotherAxisRange[type].end(), plot);
		if (iter == FinancialPlotPrivate::m_BrotherAxisRange[type].end())
		{
			FinancialPlotPrivate::m_BrotherAxisRange[type].erase(iter);
			if (FinancialPlotPrivate::m_BrotherAxisRange[type].size() == 0)
			{
				FinancialPlotPrivate::m_BrotherAxisRange.erase(type);

				return true;
			}
		}
	}
	return false;
}

QCPFinancial * FinancialPlot::AddFinancial(QCPAxis * keyAxis /*= 0*/, QCPAxis * valueAxis /*= 0*/)
{
	QCPAxis * xAxis = keyAxis;
	QCPAxis * yAxis = valueAxis;
	if (xAxis == nullptr)
	{
		xAxis = d_ptr->m_pPlot->xAxis;
	}
	if (yAxis == nullptr)
	{
		yAxis = d_ptr->m_pPlot->yAxis;
	}
	QCPFinancial *candlesticks = new QCPFinancial(xAxis, yAxis);

	candlesticks->setChartStyle(QCPFinancial::csCandlestick);
	candlesticks->setTwoColored(true);
	candlesticks->setBrushPositive(QColor(0, 0, 0, 0));
	candlesticks->setBrushNegative(QColor(0, 255, 0));
	candlesticks->setPenPositive(QPen(QColor(255, 0, 0)));
	candlesticks->setPenNegative(QPen(QColor(0, 255, 0)));

	return candlesticks;
}

void FinancialPlot::SetFinancialData(const std::vector<double> & keys
	, const std::vector<double> & open
	, const std::vector<double> & high
	, const std::vector<double> & low
	, const std::vector<double> & close
	, QCPFinancial * financial /*= nullptr*/)
{
	if (keys.size() == 0)
	{
		//输入日志
		return;
	}
	if (keys.size() != open.size()
		|| keys.size() != high.size()
		|| keys.size() != low.size()
		|| keys.size() != close.size())
	{
		//输入日志
		return;
	}

	QVector<double> qkey = QVector<double>::fromStdVector(keys);
	QVector<double> qopen = QVector<double>::fromStdVector(open);
	QVector<double> qhigh = QVector<double>::fromStdVector(high);
	QVector<double> qlow = QVector<double>::fromStdVector(low);
	QVector<double> qclose = QVector<double>::fromStdVector(close);
	
	if (financial)
	{
		financial->setData(qkey, qopen, qhigh, qlow, qclose);
	}
	else
	{
		for (int i = 0; i < d_ptr->m_pPlot->plottableCount(); ++i)
		{
			if (QCPFinancial * firstFinancial = dynamic_cast<QCPFinancial *>(d_ptr->m_pPlot->plottable()))
			{
				firstFinancial->setData(qkey, qopen, qhigh, qlow, qclose);
			}
		}
	}
}

void FinancialPlot::AddFinancialData(double key, double open, double high, double low, double close, QCPFinancial * financial /*= nullptr*/)
{
	if (financial)
	{
		financial->addData(key, open, high, low, close);
	}
	else
	{
		for (int i = 0; i < d_ptr->m_pPlot->plottableCount(); ++i)
		{
			if (QCPFinancial * firstFinancial = dynamic_cast<QCPFinancial *>(d_ptr->m_pPlot->plottable()))
			{
				firstFinancial->addData(key, open, high, low, close);
			}
		}
	}
}

void FinancialPlot::ModifyFinancialData(double key, double open, double high, double low, double close, QCPFinancial * financial /*= nullptr*/)
{

}

void FinancialPlot::AxisRangeChanged(QCPAxis::AxisType type, const QCPRange & range)
{
	if (FinancialPlotPrivate::m_BrotherAxisRange.find(QCPAxis::atBottom) != FinancialPlotPrivate::m_BrotherAxisRange.end())
	{
		for (PlotCallback * plot : FinancialPlotPrivate::m_BrotherAxisRange[QCPAxis::atBottom])
		{
			if (plot != this)
			{
				plot->SyncAxisRange(type, range);
			}
		}
	}
}
