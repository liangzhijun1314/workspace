#include "stdafx.h"

#include "PlotWidget.h"
#include "TimeSharingTrendPlot.h"

#include "TimeSharingTrendWidget.h"
#include "TimeSharingTrendWidget_p.h"

namespace QCP
{
	/*inline ViewType VType2UItype(stock::TViewType type)
	{
		ViewType outputType;
		switch (type)
		{
		case stock::ETVT_NULL:					outputType = EVT_NULL;					break;
		case stock::ETVT_TIME_DAY_1:			outputType = EVT_TIME_DAY_1;			break;
		case stock::ETVT_TIME_DAY_5:			outputType = EVT_TIME_DAY_5;			break;
		default:			outputType = EVT_NULL;			break;
		}

		return outputType;
	}
	inline stock::TViewType UItype2VType(ViewType type)
	{
		stock::TViewType outputType;
		switch (type)
		{
		case EVT_NULL:			outputType = stock::ETVT_NULL;			break;
		case EVT_TIME_DAY_1:			outputType = stock::ETVT_TIME_DAY_1;			break;	
		case EVT_TIME_DAY_5:			outputType = stock::ETVT_TIME_DAY_5;			break;
		default:			outputType = stock::ETVT_NULL;			break;
		}

		return outputType;
	}

	inline QuotaLineType LineQuota2UIQuota(stock::TLineQuotaType type)
	{
		QuotaLineType outputType;
		switch (type)
		{
		case stock::ETLQT_NULL:			outputType = QT_NULL;			break;
		case stock::ETL_TIME:			outputType = QT_TIME;			break;
		case stock::ETL_AVERAGE:		outputType = QT_AVERAGE;			break;
		case stock::ETLQT_VOL:			outputType = QT_VOL;			break;
		case stock::ETLQT_VR:			outputType = QT_LMR;			break;
		default:			outputType = QT_NULL;			break;
		}

		return outputType;
	}
	inline stock::TLineQuotaType UIQuota2LineQuota(QuotaLineType type)
	{
		stock::TLineQuotaType outputType;
		switch (type)
		{
		case QT_NULL:			outputType = stock::ETLQT_NULL;			break;
		case QT_TIME:			outputType = stock::ETL_TIME;			break;
		case QT_AVERAGE:		outputType = stock::ETL_AVERAGE;			break;
		case QT_VOL:			outputType = stock::ETLQT_VOL;			break;
		case QT_LMR:			outputType = stock::ETLQT_VR;			break;
		default:			outputType = stock::ETLQT_NULL;			break;
		}

		return outputType;
	}*/
}

TimeSharingTrendWidget::TimeSharingTrendWidget(QWidget * parent)
	: BasicWidget(*new TimeSharingTrendWidgetPrivate, parent)
{
	InitializeUI();
}

TimeSharingTrendWidget::~TimeSharingTrendWidget()
{

}

// void TimeSharingTrendWidget::SetPlotType(stock::TViewType type)
// {
// 	Q_D(TimeSharingTrendWidget);
// 	d->m_pPlot->SetPlotType(QCP::VType2UItype(type));
// }
// 
// stock::TViewType TimeSharingTrendWidget::GetPlotType() const
// {
// 	Q_D(const TimeSharingTrendWidget);
// 	return QCP::UItype2VType(d->m_pPlot->GetPlotType());
// }
// 
// void TimeSharingTrendWidget::SetQuotaType(stock::TLineQuotaType type)
// {
// 	Q_D(TimeSharingTrendWidget);
// 	d->m_pPlot->SetQuotaType(QCP::LineQuota2UIQuota(type));
// }
// 
// stock::TLineQuotaType TimeSharingTrendWidget::GettQuotaType() const
// {
// 	Q_D(const TimeSharingTrendWidget);
// 	return QCP::UIQuota2LineQuota(d->m_pPlot->GetQuotaType());
// }

TimeSharingTrendPlot * TimeSharingTrendWidget::GetTimeSharingTrendPlot() const
{
	Q_D(const TimeSharingTrendWidget);
	return dynamic_cast<TimeSharingTrendPlot *>(d->m_pPlot);
}

void TimeSharingTrendWidget::SetPresentPriceVisible(bool visible)
{
	if (d_ptr->m_PresentPriceLine == nullptr)
	{
		for (auto iter = d_ptr->m_QuotaGrahpMap.begin(); iter != d_ptr->m_QuotaGrahpMap.end(); ++iter)
		{
			if (iter->first == QCP::QT_TIME)
			{
				d_ptr->Init();
				d_ptr->m_PresentPriceLine->lineMark = new QCPItemStraightLine(iter->second->parentPlot());
				d_ptr->m_PresentPriceLine->graph = iter->second;

				if (QCPAxis * axis = iter->second->parentPlot()->axisRect()->axis(QCPAxis::atBottom))
				{
					QCPRange range = axis->range();
					connect(axis, static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged), this, [this](const QCPRange &newRange){
						int value = 10;
						d_ptr->m_PresentPriceLine->lineMark->positions().first()->setCoords(QPointF(newRange.lower, value));
						d_ptr->m_PresentPriceLine->lineMark->positions().last()->setCoords(QPointF(newRange.upper, value));
					});

					int value = 20;
					QCPItemPosition * start = new QCPItemPosition(iter->second->parentPlot(), d_ptr->m_PresentPriceLine->lineMark, QStringLiteral("firstPoint"));
					QCPItemPosition * end = new QCPItemPosition(iter->second->parentPlot(), d_ptr->m_PresentPriceLine->lineMark, QStringLiteral("secondPoint"));
					d_ptr->m_PresentPriceLine->lineMark->positions().append(start);
					d_ptr->m_PresentPriceLine->lineMark->positions().append(end);
					d_ptr->m_PresentPriceLine->lineMark->setPen(/*d_ptr->m_PresentPriceLine.graph->pen()*/QPen(Qt::red));
				}
				break;
			}
		}
	}

	if (d_ptr->m_PresentPriceLine && d_ptr->m_PresentPriceLine->lineMark)
	{
		d_ptr->m_PresentPriceLine->lineMark->setVisible(visible);
	}
	else
	{
		//异常，不存在现价线
	}
}

// void TimeSharingTrendWidget::OnUpdate2(const stock::TLineQuotaType & type, const DataContainer<stock::LineData> & data)
// {
// 	//只需要展示数据，不需要处理异常数据
// 	Q_D(TimeSharingTrendWidget);
// 	QCP::QuotaLineType uitype = QCP::LineQuota2UIQuota(type);
// 	if (d->m_PlotMap.find(uitype) != d->m_PlotMap.end())
// 	{
// 		DisposeQuotaData(uitype);
// 	}
// }

void TimeSharingTrendWidget::InitializeUI()
{
	Q_D(TimeSharingTrendWidget);
	QVBoxLayout * mainLayout = new QVBoxLayout;

	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(d->m_pPlot);

	setLayout(mainLayout);
}

void TimeSharingTrendWidget::DisposeQuotaData(QCP::QuotaLineType type)
{

}
