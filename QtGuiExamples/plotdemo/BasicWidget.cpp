#include "stdafx.h"

#include "PlotWidget.h"

#include "BasicWidget.h"
#include "BasicWidget_p.h"

Q_DECLARE_METATYPE(QuotaItem *)

BasicWidget::BasicWidget(QWidget * parent)
	: QWidget(parent)
	, d_ptr(new BasicWidgetPrivate)
{
}

BasicWidget::BasicWidget(BasicWidgetPrivate & pd, QWidget * parent /*= nullptr*/)
	: QWidget(parent)
	, d_ptr(&pd)
{

}

BasicWidget::~BasicWidget()
{

}

void BasicWidget::SetWrapWidget(PlotWidget * widget)
{
	if (d_ptr->m_pWrapwidget)
	{
		d_ptr->m_pWrapwidget->disconnect();
	}
	d_ptr->m_pWrapwidget = widget;
	connect(d_ptr->m_pWrapwidget, &PlotWidget::AddQuotaSignal, this, &BasicWidget::AddQuotaSlot);
	connect(d_ptr->m_pWrapwidget, &PlotWidget::ShowQuotaSignal, this, &BasicWidget::ShowQuotaSlot);
	connect(d_ptr->m_pWrapwidget, &PlotWidget::RemoveQuotaSignal, this, &BasicWidget::RemoveQuotaSlot);
}

void BasicWidget::AddQuotaSlot(QCP::QuotaLineType id)
{
	auto iter = d_ptr->m_QuotaGrahpMap.find(id);
	if (iter == d_ptr->m_QuotaGrahpMap.end())
	{
		QCPGraph * graphItem = d_ptr->m_pPlot->AddGraph();
		graphItem->setName(QString::number(id));//作为唯一标示
		graphItem->setPen(QPen(d_ptr->m_pWrapwidget->GetQuotaColor(id)));
		d_ptr->m_QuotaGrahpMap[id] = graphItem;
	}
}

void BasicWidget::RemoveQuotaSlot(QCP::QuotaLineType id)
{
	auto iter = d_ptr->m_QuotaGrahpMap.find(id);
	if (iter != d_ptr->m_QuotaGrahpMap.end())
	{
		d_ptr->m_QuotaGrahpMap.erase(iter);
		d_ptr->m_pPlot->RemovePlottable(iter->second);
	}
}

void BasicWidget::ShowQuotaSlot(QCP::QuotaLineType id, bool visible)
{
	auto iter = d_ptr->m_QuotaGrahpMap.find(id);
	if (iter != d_ptr->m_QuotaGrahpMap.end())
	{
		iter->second->setVisible(visible);
	}
}

