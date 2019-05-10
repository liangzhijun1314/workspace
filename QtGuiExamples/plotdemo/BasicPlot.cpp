#include "stdafx.h"

#include "QCustomplot.h"
#include "CrossLinePlot.h"
#include "AxisFixedPixelTicker.h"

#include "BasicPlot.h"
#include "BasicPlot_p.h"

namespace
{
	void ConfigureAxis(QCPAxis * axis)
	{
		//	axis->setAutoSubTicks(false);
		//	axis->setSubTickCount(0);
		// 		axis->ticker()->setAutoTickCount(false);
		//         axis->setAutoTickStep(false);

		switch (axis->axisType())
		{
		case QCPAxis::atLeft:
		{
			axis->setTickLabels(true);
		}
		break;
		case QCPAxis::atTop:
		{
			axis->setPadding(0);
			axis->setTickLabels(false);
		}
		break;
		case QCPAxis::atRight:
		{
			axis->setTickLabels(true);
			axis->setVisible(true);
		}
		break;
		case QCPAxis::atBottom:
		{
			axis->setPadding(0);
			axis->setTickLabels(true);
		}
		break;
		default:
			break;
		}
	}

	void ConfigureZeroLine(QCPAxis * axis)
	{
		axis->grid()->setZeroLinePen(QPen(Qt::NoPen));
		axis->setTickLength(0);

		//axis->setTicks(true);	
		axis->setTickPen(QPen(Qt::transparent));

		//axis->setSubTicks(false);  		
		axis->setSubTickPen(QPen(Qt::transparent));

		axis->setBasePen(QPen(Qt::transparent));//坐标轴线透明
		axis->grid()->setPen(QPen(Qt::white));//设置网格线画笔
	}
}

std::map<QCP::ViewType, BasicPlotPrivate::RectRange>BasicPlotPrivate::DefaultRange;
std::map<QCPAxis::AxisType, std::vector<PlotCallback *>>BasicPlotPrivate::m_BrotherAxisRange;

BasicPlot::BasicPlot(QWidget * parent)
	: QWidget(parent)
	, d_ptr(new BasicPlotPrivate)
{
	InitializeUI();
	EnableFixedTicker(QCPAxis::atLeft | QCPAxis::atRight);

	ConfigureAxis(GetAxis(QCPAxis::atLeft));
	ConfigureAxis(GetAxis(QCPAxis::atTop));
	ConfigureAxis(GetAxis(QCPAxis::atRight));
	ConfigureAxis(GetAxis(QCPAxis::atBottom));

// 	SetAxisPadding(QCPAxis::atLeft, 30);
// 	SetAxisPadding(QCPAxis::atRight, 30);

	//禁用零线
	ConfigureZeroLine(GetAxis(QCPAxis::atLeft));
	ConfigureZeroLine(GetAxis(QCPAxis::atTop));
	ConfigureZeroLine(GetAxis(QCPAxis::atRight));
	ConfigureZeroLine(GetAxis(QCPAxis::atBottom));

	connect(GetAxis(QCPAxis::atLeft), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged)
		, GetAxis(QCPAxis::atRight), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::setRange));

	d_ptr->m_pPlot->setNoAntialiasingOnDrag(true);//拖拽过程中不使用反锯齿绘制

	d_ptr->m_pPlot->setBackground(Qt::gray);
	d_ptr->m_pPlot->axisRect()->setMinimumMargins(QMargins(15, 0, 15, 0));
	d_ptr->m_pCrossLine = new CrossLinePlot(this, d_ptr->m_pPlot);
}

BasicPlot::BasicPlot(BasicPlotPrivate & pd, QWidget * parent /*= nullptr*/)
	: QWidget(parent)
	, d_ptr(&pd)
{
	InitializeUI();
	EnableFixedTicker(QCPAxis::atLeft | QCPAxis::atRight);

	ConfigureAxis(GetAxis(QCPAxis::atLeft));
	ConfigureAxis(GetAxis(QCPAxis::atTop));
	ConfigureAxis(GetAxis(QCPAxis::atRight));
	ConfigureAxis(GetAxis(QCPAxis::atBottom));

	// 	SetAxisPadding(QCPAxis::atLeft, 30);
	// 	SetAxisPadding(QCPAxis::atRight, 30);

	//禁用零线
	ConfigureZeroLine(GetAxis(QCPAxis::atLeft));
	ConfigureZeroLine(GetAxis(QCPAxis::atTop));
	ConfigureZeroLine(GetAxis(QCPAxis::atRight));
	ConfigureZeroLine(GetAxis(QCPAxis::atBottom));

	connect(GetAxis(QCPAxis::atLeft), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::rangeChanged)
		, GetAxis(QCPAxis::atRight), static_cast<void (QCPAxis:: *)(const QCPRange &)>(&QCPAxis::setRange));

	d_ptr->m_pPlot->setNoAntialiasingOnDrag(true);//拖拽过程中不使用反锯齿绘制

	d_ptr->m_pPlot->setBackground(Qt::gray);
	d_ptr->m_pPlot->axisRect()->setMinimumMargins(QMargins(15, 0, 15, 0));
	d_ptr->m_pCrossLine = new CrossLinePlot(this, d_ptr->m_pPlot);
}

BasicPlot::~BasicPlot()
{

}

QCPGraph * BasicPlot::GetGraph(int index) const
{
	return d_ptr->m_pPlot->graph(index);
}

QCPGraph * BasicPlot::GetGraph() const
{
	return d_ptr->m_pPlot->graph();
}

QCPGraph * BasicPlot::AddGraph(QCPAxis * keyAxis /*= 0*/, QCPAxis * valueAxis /*= 0*/)
{
	return d_ptr->m_pPlot->addGraph(keyAxis, valueAxis);
}

bool BasicPlot::RemoveGraph(QCPGraph * graph)
{
	return d_ptr->m_pPlot->removeGraph(graph);
}

bool BasicPlot::RemoveGraph(int index)
{
	return d_ptr->m_pPlot->removeGraph(index);
}

bool BasicPlot::RemoveGraph(const QString & name)
{
	for (int i = 0; i < d_ptr->m_pPlot->graphCount(); ++i)
	{
		if (d_ptr->m_pPlot->graph(i)->name() == name)
		{
			return d_ptr->m_pPlot->removeGraph(i);
		}
	}
	return false;
}

int BasicPlot::ClearGraphs()
{
	return d_ptr->m_pPlot->clearGraphs();
}

int BasicPlot::GraphCount() const
{
	return d_ptr->m_pPlot->graphCount();
}

QList<QCPGraph *> BasicPlot::SelectedGraphs() const
{
	return d_ptr->m_pPlot->selectedGraphs();
}

//void BasicPlot::SetGraphData(const std::vector<stock::LineData> & datas, QCPGraph * graph /*= nullptr*/)
//{
//	if (datas.size() == 0)
//	{
//		return;
//	}
//
//	QSharedPointer<QCPDataContainer<QCPGraphData>> data(new QCPDataContainer<QCPGraphData>);
//	QVector<QCPGraphData> tempData(datas.size());
//	QVector<QCPGraphData>::iterator it = tempData.begin();
//	const QVector<QCPGraphData>::iterator itEnd = tempData.end();
//	int i = 0;
//	while (it != itEnd)
//	{
//		it->key = datas[i].x;
//		it->value = datas[i].y;
//		++it;
//		++i;
//	}
//	data->add(tempData); // don't modify tempData beyond this to prevent copy on write
//
//	if (graph)
//	{
//		graph->setData(data);
//	}
//	else
//	{
//		if (d_ptr->m_pPlot->graph())
//		{
//			d_ptr->m_pPlot->graph()->setData(data);
//		}
//		else
//		{
//			//当前无图表
//		}
//	}
//}

void BasicPlot::SetGraphData(const std::vector<double> & key, const std::vector<double> & value, QCPGraph * graph)
{
	if (key.size() == 0 || value.size() || key.size() != value.size())
	{
		//输入日志
		return;
	}
	QVector<double> qkey = QVector<double>::fromStdVector(key);
	QVector<double> qvalue = QVector<double>::fromStdVector(value);

	if (graph)
	{
		graph->setData(qkey, qvalue);
	}
	else
	{
		if (d_ptr->m_pPlot->graph())
		{
			d_ptr->m_pPlot->graph()->setData(qkey, qvalue);
		}
		else
		{
			//当前无图表
		}
	}
}

void BasicPlot::AddPointData(double key, double value, QCPGraph * graph)
{
	if (graph)
	{
		graph->addData(key, value);
	}
	else
	{
		if (d_ptr->m_pPlot->graph())
		{
			d_ptr->m_pPlot->graph()->addData(key, value);
		}
	}
}

QCPBars * BasicPlot::AddBars(QCPAxis * keyAxis /*= 0*/, QCPAxis * valueAxis /*= 0*/)
{
	QCPBars * bars = new QCPBars(keyAxis, valueAxis);
	return bars;
}

bool BasicPlot::RemovePlottable(QCPAbstractPlottable * plottable)
{
	return d_ptr->m_pPlot->removePlottable(plottable);
}

bool BasicPlot::RemovePlottable(const QString & name)
{
	for (int i = 0; i < d_ptr->m_pPlot->plottableCount(); ++i)
	{
		if (d_ptr->m_pPlot->plottable(i)->name() == name)
		{
			return d_ptr->m_pPlot->removePlottable(i);
		}
	}
	return false;
}

//void BasicPlot::SetBarsData(const std::vector<stock::LineData> & datas, QCPBars * bars /*= nullptr*/)
//{
//	if (datas.size() == 0)
//	{
//		return;
//	}
//
//	QSharedPointer<QCPDataContainer<QCPBarsData>> data(new QCPDataContainer<QCPBarsData>);
//	QVector<QCPBarsData> tempData(datas.size());
//	QVector<QCPBarsData>::iterator it = tempData.begin();
//	const QVector<QCPBarsData>::iterator itEnd = tempData.end();
//	int i = 0;
//	while (it != itEnd)
//	{
//		it->key = datas[i].x;
//		it->value = datas[i].y;
//		++it;
//		++i;
//	}
//
//	data->add(tempData);  
//
//	if (bars)
//	{
//		bars->setData(data);
//	}
//	else
//	{
//		for (int i = 0; i < d_ptr->m_pPlot->plottableCount(); ++i)
//		{
//			if (QCPBars * firstBars = dynamic_cast<QCPBars *>(d_ptr->m_pPlot->plottable()))
//			{
//				firstBars->setData(data);
//				break;
//			}
//		}
//	}
//}

void BasicPlot::SetBarsData(const std::vector<double> & key, const std::vector<double> & value, QCPBars * bars /*= nullptr*/)
{
	if (key.size() == 0 || value.size() || key.size() != value.size())
	{
		//输入日志
		return;
	}
	QVector<double> qkey = QVector<double>::fromStdVector(key);
	QVector<double> qvalue = QVector<double>::fromStdVector(value);
	if (bars)
	{
		bars->setData(qkey, qvalue);
	}
	else
	{
		for (int i = 0; i < d_ptr->m_pPlot->plottableCount(); ++i)
		{
			if (QCPBars * firstBars = dynamic_cast<QCPBars *>(d_ptr->m_pPlot->plottable()))
			{
				firstBars->setData(qkey, qvalue);
				break;
			}
		}
	}
}

void BasicPlot::AddBarData(double key, double value, QCPBars * bars /*= nullptr*/)
{
	if (bars)
	{
		bars->addData(key, value);
	}
	else
	{
		for (int i = 0; i < d_ptr->m_pPlot->plottableCount(); ++i)
		{
			if (QCPBars * firstBars = dynamic_cast<QCPBars *>(d_ptr->m_pPlot->plottable()))
			{
				firstBars->addData(key, value);
				break;
			}
		}
	}
}

void BasicPlot::SetPlotType(QCP::ViewType type)
{
	d_ptr->m_ePlotType = type;
}

QCP::ViewType BasicPlot::GetPlotType() const
{
	return d_ptr->m_ePlotType;
}

void BasicPlot::SetQuotaType(QCP::QuotaLineType type)
{
	//if (d_ptr->m_ePlotType == stock::EKVT_NULL)
	//{
	//	d_ptr->m_eQuotaType = type;
	//}
}

QCP::QuotaLineType BasicPlot::GetQuotaType() const
{
	return d_ptr->m_eQuotaType;
}

void BasicPlot::SetAxisLower(QCPAxis::AxisType type, double lower)
{
	GetAxis(type)->setRangeLower(lower);
}

void BasicPlot::SetAxisUpper(QCPAxis::AxisType type, double upper)
{
	GetAxis(type)->setRangeUpper(upper);
}

void BasicPlot::SetAxisRange(QCPAxis::AxisType type, double lower, double upper)
{
	GetAxis(type)->setRange(lower, upper);
}

void BasicPlot::SetAxisLabelFormat(QCPAxis::AxisTypes axse, const QString & format)
{
	if (axse.testFlag(QCPAxis::atLeft))
	{
		GetAxis(QCPAxis::atLeft)->setNumberFormat(format);
	}
	if (axse.testFlag(QCPAxis::atTop))
	{
		GetAxis(QCPAxis::atTop)->setNumberFormat(format);
	}
	if (axse.testFlag(QCPAxis::atRight))
	{
		GetAxis(QCPAxis::atRight)->setNumberFormat(format);
	}
	if (axse.testFlag(QCPAxis::atBottom))
	{
		GetAxis(QCPAxis::atBottom)->setNumberFormat(format);
	}
}

void BasicPlot::SetAxisLabelPrecision(QCPAxis::AxisTypes axse, int precision)
{
	if (axse.testFlag(QCPAxis::atLeft))
	{
		GetAxis(QCPAxis::atBottom)->setNumberPrecision(precision);
	}
	if (axse.testFlag(QCPAxis::atTop))
	{
		GetAxis(QCPAxis::atTop)->setNumberPrecision(precision);
	}
	if (axse.testFlag(QCPAxis::atRight))
	{
		GetAxis(QCPAxis::atRight)->setNumberPrecision(precision);
	}
	if (axse.testFlag(QCPAxis::atBottom))
	{
		GetAxis(QCPAxis::atBottom)->setNumberPrecision(precision);
	}
}

void BasicPlot::ResetPlot()
{
	auto iter = BasicPlotPrivate::DefaultRange.find(GetPlotType());
	if (iter != BasicPlotPrivate::DefaultRange.end())
	{
		for (int i = 0; i < d_ptr->m_pPlot->axisRectCount(); ++i)
		{
			d_ptr->m_pPlot->axisRect(i)->axis(QCPAxis::atBottom)->setRange(iter->second.bottom);
		}
	}
}

void BasicPlot::SyncAxisRange(QCPAxis::AxisType type, const QCPRange & range)
{
	GetAxis(type)->setRange(range);
	d_ptr->m_pPlot->replot();
}

bool BasicPlot::TipLabelEnable() const
{
	return d_ptr->m_bAxisTipEnable;
}

void BasicPlot::MoveTipLabel(const QPoint & pos)
{
	if (d_ptr->m_LeftAxisTip == nullptr)
	{
		d_ptr->m_LeftAxisTip = new QLabel(this);
		d_ptr->m_LeftAxisTip->setAttribute(Qt::WA_TransparentForMouseEvents);
		d_ptr->m_LeftAxisTip->setWindowFlags(Qt::WindowStaysOnTopHint);
		d_ptr->m_LeftAxisTip->setAlignment(Qt::AlignCenter);
		d_ptr->m_LeftAxisTip->setFixedSize(60, 20);
		d_ptr->m_LeftAxisTip->setText("<p style='color:red;'>l");
	}
	if (d_ptr->m_RightAxisTip == nullptr)
	{
		d_ptr->m_RightAxisTip = new QLabel(this);
		d_ptr->m_RightAxisTip->setAttribute(Qt::WA_TransparentForMouseEvents);
		d_ptr->m_RightAxisTip->setWindowFlags(Qt::WindowStaysOnTopHint);
		d_ptr->m_RightAxisTip->setAlignment(Qt::AlignCenter);
		d_ptr->m_RightAxisTip->setFixedSize(60, 20);
		d_ptr->m_RightAxisTip->setText("<p style='color:red;'>r");
	}
	if (d_ptr->m_BottomAxisTip == nullptr)
	{
		d_ptr->m_BottomAxisTip = new QLabel(this);
		d_ptr->m_BottomAxisTip->setAttribute(Qt::WA_TransparentForMouseEvents);
		d_ptr->m_BottomAxisTip->setWindowFlags(Qt::WindowStaysOnTopHint);
		d_ptr->m_BottomAxisTip->setAlignment(Qt::AlignCenter);
		d_ptr->m_BottomAxisTip->setFixedSize(88, 20);
		d_ptr->m_BottomAxisTip->setText("<p style='color:red;'>b");
	}

	if (d_ptr->m_LeftAxisTip->isVisible())
	{
		d_ptr->m_LeftAxisTip->setText(QString::number(d_ptr->m_pPlot->yAxis->pixelToCoord(pos.y()), 'f', 3));
		d_ptr->m_LeftAxisTip->move(QPoint(0, pos.y() - d_ptr->m_LeftAxisTip->height() / 2));
	}
	if (d_ptr->m_RightAxisTip->isVisible())
	{
		d_ptr->m_RightAxisTip->setText(QString::number(d_ptr->m_pPlot->yAxis->pixelToCoord(pos.y()), 'f', 3));
		d_ptr->m_RightAxisTip->move(QPoint(width() - d_ptr->m_RightAxisTip->width(), pos.y() - d_ptr->m_RightAxisTip->height() / 2));
	}
	if (d_ptr->m_BottomAxisTip->isVisible())
	{
		d_ptr->m_BottomAxisTip->setText(QString::number(d_ptr->m_pPlot->yAxis->pixelToCoord(pos.x()), 'f', 3));
		d_ptr->m_BottomAxisTip->move(QPoint(pos.x() - d_ptr->m_BottomAxisTip->width() / 2, height() - d_ptr->m_BottomAxisTip->height()+4));
	}
}

bool BasicPlot::LineTracerEnable() const
{
	return d_ptr->m_bTracerEnable;
}

void BasicPlot::MoveLineTracer(const QPoint & pos)
{
	if (d_ptr->m_bTracerVisible == false)
	{
		return;
	}

	for (auto iter = d_ptr->m_LineTracers.begin(); iter != d_ptr->m_LineTracers.end(); ++iter)
	{
		if (iter->first->visible())
		{
			iter->second->setGraphKey(d_ptr->m_pPlot->xAxis->pixelToCoord(pos.x()));
		}
	}
}

void BasicPlot::SetLineTracerEnable(bool enable)
{
	if (d_ptr->m_bTracerEnable != enable)
	{
		d_ptr->m_bTracerEnable = enable;
	}
}

void BasicPlot::SetLineTracerVisible(bool visible, QCPGraph * graph /*= nullptr*/)
{
	if (d_ptr->m_bTracerEnable == false)
	{
		return;
	}

	d_ptr->m_bTracerVisible = visible;
	if (d_ptr->m_bTracerVisible)
	{
		if (graph == nullptr)
		{
			for (int i = 0; i < d_ptr->m_pPlot->graphCount(); ++i)
			{
				if (QCPGraph * itemGraph = d_ptr->m_pPlot->graph(i))
				{
					if (d_ptr->m_LineTracers.find(itemGraph) != d_ptr->m_LineTracers.end())
					{
						d_ptr->m_LineTracers[itemGraph]->setVisible(true);
						continue;
					}
					QCPItemTracer * phaseTracer = new QCPItemTracer(itemGraph->parentPlot());
					phaseTracer->setGraph(itemGraph);
					phaseTracer->setInterpolating(true);
					phaseTracer->setStyle(QCPItemTracer::tsCircle);
					phaseTracer->setPen(itemGraph->pen());
					phaseTracer->setBrush(QBrush(itemGraph->pen().color()));
					phaseTracer->setSize(7);
					d_ptr->m_LineTracers[itemGraph] = phaseTracer;
				}
			}
		}
		else
		{
			QCPItemTracer * phaseTracer = new QCPItemTracer(graph->parentPlot());
			phaseTracer->setGraph(graph);
			phaseTracer->setGraphKey(100);
			phaseTracer->setInterpolating(true);
			phaseTracer->setStyle(QCPItemTracer::tsCircle);
			phaseTracer->setPen(graph->pen());
			phaseTracer->setBrush(QBrush(graph->pen().color()));
			phaseTracer->setSize(7);
			d_ptr->m_LineTracers[graph] = phaseTracer;
		}
	}
	else
	{
		for (int i = 0; i < d_ptr->m_pPlot->graphCount(); ++i)
		{
			if (QCPGraph * itemGraph = d_ptr->m_pPlot->graph(i))
			{
				if (d_ptr->m_LineTracers.find(itemGraph) != d_ptr->m_LineTracers.end())
				{
					d_ptr->m_LineTracers[itemGraph]->setVisible(false);
				}
			}
		}
	}
}

void BasicPlot::SetMoveTipLabel(bool enable)
{
	if (d_ptr->m_bAxisTipEnable != enable)
	{
		d_ptr->m_bAxisTipEnable = enable;
	}
}

void BasicPlot::SetToopTipVisible(QCPAxis::AxisTypes axse, bool visible)
{
	if (axse.testFlag(QCPAxis::atLeft) && d_ptr->m_LeftAxisTip)
	{
		d_ptr->m_LeftAxisTip->setVisible(visible);
	}
	if (axse.testFlag(QCPAxis::atRight) && d_ptr->m_RightAxisTip)
	{
		d_ptr->m_RightAxisTip->setVisible(visible);
	}
	if (axse.testFlag(QCPAxis::atBottom) && d_ptr->m_BottomAxisTip && d_ptr->m_pPlot->xAxis->tickLabels())
	{
		d_ptr->m_BottomAxisTip->setVisible(visible);
	}
}

void BasicPlot::SetAutoAxisRange(QCP::AxisRange type, bool enable)
{
	if (enable)
	{
		d_ptr->m_AutoRange |= type;
	}
	else
	{
		d_ptr->m_AutoRange &= ~type;
	}
}

void BasicPlot::SetAutoAxisRange(QCP::AxisRanges axse)
{
	d_ptr->m_AutoRange = axse;
}

void BasicPlot::SetScatterStyle(QCPScatterStyle style, QCPGraph * graph /*= nullptr*/)
{
	if (graph)
	{
		graph->setScatterStyle(style);
	}
	else
	{
		if (d_ptr->m_pPlot->graph())
		{
			d_ptr->m_pPlot->graph()->setScatterStyle(style);
		}
	}
}

void BasicPlot::SetCrossLineVisible(bool visible)
{
	d_ptr->m_pCrossLine->SetVisible(visible);
}

CrossLinePlot * BasicPlot::GetCrossLine() const
{
	return d_ptr->m_pCrossLine;
}

bool BasicPlot::RegisiterBortherLine(CrossLinePlot * line)
{
	return d_ptr->m_pCrossLine->RegisiterBortherLine(line);
}

bool BasicPlot::UnregisiterBortherLine(CrossLinePlot * line)
{
	return d_ptr->m_pCrossLine->UnregisiterBortherLine(line);
}

QCPAxis * BasicPlot::GetAxis(QCPAxis::AxisType axis)
{
	return d_ptr->GetAxis(axis);
}

void BasicPlot::SetGridVisible(bool visible)
{
	if (QCPLayer * gridLayer = d_ptr->m_pPlot->layer(QStringLiteral("grid")))
	{
		gridLayer->setVisible(visible);
	}
}

void BasicPlot::SetAxisPen(QCPAxis::AxisTypes axse, const QPen & pen)
{
	if (axse.testFlag(QCPAxis::atLeft))
	{
		GetAxis(QCPAxis::atLeft)->setBasePen(pen);
	}
	if (axse.testFlag(QCPAxis::atTop))
	{
		GetAxis(QCPAxis::atTop)->setBasePen(pen);
	}
	if (axse.testFlag(QCPAxis::atRight))
	{
		GetAxis(QCPAxis::atRight)->setBasePen(pen);
	}
	if (axse.testFlag(QCPAxis::atBottom))
	{
		GetAxis(QCPAxis::atBottom)->setBasePen(pen);
	}
}

void BasicPlot::SetAxisPadding(QCPAxis::AxisType type, int padding)
{
	GetAxis(type)->setTickLabelPadding(padding);
}

void BasicPlot::enterEvent(QEvent * event)
{
    QWidget::enterEvent(event);
}

void BasicPlot::leaveEvent(QEvent * event)
{
	if (d_ptr->m_pCrossLine)
	{
		d_ptr->m_pCrossLine->SetLineShow(QCP::E_NULL);
	}
    QWidget::leaveEvent(event);
}

void BasicPlot::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void BasicPlot::EnableFixedTicker(QCPAxis::AxisTypes axse)
{
	for (int i = 0; i < d_ptr->m_pPlot->axisRectCount(); ++i)
	{
		if (d_ptr->m_pPlot->axisRect(i)->axis(QCPAxis::atLeft)->ticker().dynamicCast<QSharedPointer<AxisFixedPixelTicker>>() == false)
		{
			if (axse.testFlag(QCPAxis::atLeft))
			{
				QCPAxis * leftAxis = d_ptr->m_pPlot->axisRect(i)->axis(QCPAxis::atLeft);
				leftAxis->setTicker(QSharedPointer<AxisFixedPixelTicker>(new AxisFixedPixelTicker(leftAxis)));
				if (axse.testFlag(QCPAxis::atRight))
				{
					QCPAxis * rightAxis = d_ptr->m_pPlot->axisRect(i)->axis(QCPAxis::atRight);
					rightAxis->setTicker(leftAxis->ticker());
				}
			}
			if (axse.testFlag(QCPAxis::atRight))
			{
				QCPAxis * rightAxis = d_ptr->m_pPlot->axisRect(i)->axis(QCPAxis::atRight);
				rightAxis->setTicker(QSharedPointer<AxisFixedPixelTicker>(new AxisFixedPixelTicker(rightAxis)));
				if (axse.testFlag(QCPAxis::atLeft))
				{
					QCPAxis * leftAxis = d_ptr->m_pPlot->axisRect(i)->axis(QCPAxis::atRight);
					leftAxis->setTicker(rightAxis->ticker());
				}
			}
		}
	}
}

void BasicPlot::InitializeUI()
{
	d_ptr->m_pMainLayout = new QVBoxLayout;
	d_ptr->m_pPlot = new QCustomPlot;

	d_ptr->m_pMainLayout->setContentsMargins(10, 0, 10, 0);
	d_ptr->m_pMainLayout->addWidget(d_ptr->m_pPlot);

	setLayout(d_ptr->m_pMainLayout);
}

QCPAxis * BasicPlotPrivate::GetAxis(QCPAxis::AxisType axis)
{
	switch (axis)
	{
	case QCPAxis::atLeft:
		return m_pPlot->yAxis;
		break;
	case QCPAxis::atTop:
		return m_pPlot->xAxis2;
		break;
	case QCPAxis::atRight:
		return m_pPlot->yAxis2;
		break;
	case QCPAxis::atBottom:
		return m_pPlot->xAxis;
		break;
	default:
		return m_pPlot->xAxis;
		break;
	}
}
