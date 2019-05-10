#include "stdafx.h"

#include "BasicPlot.h"
#include "FinancialPlot.h"

#include "FinancialWidget.h"
#include "FinancialWidget_p.h"

namespace QCP
{
	/*inline ViewType KType2UItype(stock::KViewType type)
	{
		ViewType outputType;
		switch (type)
		{
		case stock::EKVT_NULL:			outputType = EVT_NULL;					break;
		case stock::EKVT_KLINE_DAY:		outputType = EVT_KLINE_DAY;				break;
		case stock::EKVT_KLINE_WEEK:	outputType = EVT_KLINE_WEEK;			break;
		case stock::EKVT_KLINE_MONTH:	outputType = EVT_KLINE_MONTH;			break;
		default:						outputType = EVT_NULL;					break;
		}

		return outputType;
	}
	inline stock::KViewType UIType2KType(ViewType type)
	{
		stock::KViewType outputType;
		switch (type)
		{
		case EVT_NULL:					outputType = stock::EKVT_NULL;					break;
		case EVT_KLINE_DAY:				outputType = stock::EKVT_KLINE_DAY;				break;
		case EVT_KLINE_WEEK:			outputType = stock::EKVT_KLINE_WEEK;			break;
		case EVT_KLINE_MONTH:			outputType = stock::EKVT_KLINE_MONTH;			break;
		default:						outputType = stock::EKVT_NULL;					break;
		}

		return outputType;
	}

	inline QuotaLineType LineQuota2UIQuota(stock::KLineQuotaType type)
	{
		QuotaLineType outputType;
		switch (type)
		{
		case stock::EKLQT_NULL:			outputType = QT_NULL;			break;
		case stock::EKLQT_MACD:			outputType = QT_MACD;			break;
		case stock::EKLQT_KDJ:			outputType = QT_KDJ;			break;
		case stock::EKLQT_RSI:			outputType = QT_RSI;			break;
		case stock::EKLQT_BRAR:			outputType = QT_ARBR;			break;
		case stock::EKLQT_DMI:			outputType = QT_DMI;			break;
		case stock::EKLQT_CR:			outputType = QT_CR;				break;
		case stock::EKLQT_PSY:			outputType = QT_PSY;			break;
		case stock::EKLQT_KD:			outputType = QT_LMR;			break;
		case stock::EKLQT_DMA:			outputType = QT_DMA;			break;
		default:						outputType = QT_NULL;			break;
		}

		return outputType;
	}

	inline stock::KLineQuotaType UIQuota2LineQuota(QuotaLineType type)
	{
		stock::KLineQuotaType outputType;
		switch (type)
		{
		case QT_NULL:					outputType = stock::EKLQT_NULL;			break;
		case QT_MACD:					outputType = stock::EKLQT_MACD;			break;
		case QT_KDJ:					outputType = stock::EKLQT_KDJ;			break;
		case QT_RSI:					outputType = stock::EKLQT_RSI;			break;
		case QT_ARBR:					outputType = stock::EKLQT_BRAR;			break;
		case QT_DMI:					outputType = stock::EKLQT_DMI;			break;
		case QT_CR:						outputType = stock::EKLQT_CR;			break;
		case QT_PSY:					outputType = stock::EKLQT_PSY;			break;
		case QT_LMR:					outputType = stock::EKLQT_KD;			break;
		case QT_DMA:					outputType = stock::EKLQT_DMA;			break;
		default:						outputType = stock::EKLQT_NULL;			break;
		}

		return outputType;
	}*/
}

FinancialWidget::FinancialWidget(QWidget * parent)
	: BasicWidget(*new FinancialWidgetPrivate, parent)
{
	InitializeUI();
}

FinancialWidget::~FinancialWidget()
{

}

//void FinancialWidget::SetPlotType(stock::KViewType type)
//{
//	Q_D(FinancialWidget);
//	d->m_pPlot->SetPlotType(QCP::KType2UItype(type));
//}
//
//stock::KViewType FinancialWidget::GetPlotType() const
//{
//	Q_D(const FinancialWidget);
//	return QCP::UIType2KType(d->m_pPlot->GetPlotType());
//}
//
//void FinancialWidget::SetQuotaType(stock::KLineQuotaType type)
//{
//	Q_D(FinancialWidget);
//	d->m_pPlot->SetQuotaType(QCP::LineQuota2UIQuota(type));
//}
//
//stock::KLineQuotaType FinancialWidget::GettQuotaType() const
//{
//	Q_D(const FinancialWidget);
//	return QCP::UIQuota2LineQuota(d->m_pPlot->GetQuotaType());
//}

FinancialPlot * FinancialWidget::GetFinancialPlot() const
{
	Q_D(const FinancialWidget);
	return dynamic_cast<FinancialPlot *>(d->m_pPlot);
}

// void FinancialWidget::OnUpdate(const DataContainer<stock::KLineData> & data)
// {
// 
// }
// 
// void FinancialWidget::OnUpdate2(const stock::KLineQuotaType & p1, const DataContainer<stock::LineData> & p2)
// {
// 
// }

void FinancialWidget::InitializeUI()
{
	Q_D(FinancialWidget);
	QVBoxLayout * mainLayout = new QVBoxLayout;

	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(d->m_pPlot);

	setLayout(mainLayout);
}
