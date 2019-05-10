#include "stdafx.h"

#include "PlotCallback.h"
#include "BasicPlot.h"

#include "CrossLinePlot.h"

std::vector<CrossLinePlot *>CrossLinePlot::m_BrotherLine;

struct CrossLinePlotPrivate
{
	QCP::LineStates m_bIsVisible;
	bool m_bLeftButtonPress = false;
	double m_dAxisXValue = -1;
	QPoint m_MousePoint;
	QCPPainter * m_pPainter = nullptr;
	QPen m_Pen = QPen(Qt::black, 1, Qt::DashDotLine);
	PlotCallback * m_pParentPlot = nullptr;
};

CrossLinePlot::CrossLinePlot(PlotCallback * basePlot, QCustomPlot * plot)
	: QCPLayerable(plot)
	, d_ptr(new CrossLinePlotPrivate)
{
	d_ptr->m_pParentPlot = basePlot;
	mParentPlot->addLayer(LayerName());
	
	setLayer(LayerName());

	connect(mParentPlot, &QCustomPlot::mousePress, this, [this](QMouseEvent * event){
		if (event->button() & Qt::LeftButton)
		{
			d_ptr->m_bLeftButtonPress = true;
		}
	});
	connect(mParentPlot, &QCustomPlot::mouseRelease, this, [this](QMouseEvent * event){
		if (event->button() & Qt::LeftButton)
		{
			d_ptr->m_bLeftButtonPress = false;
		}
	});
	connect(mParentPlot, &QCustomPlot::mouseMove, this, &CrossLinePlot::MouseMoveHandle);

	QVector<qreal> dashes;
	qreal space = 4;
	dashes << 3 << space << 9 << space;
	d_ptr->m_Pen.setDashPattern(dashes);
}

CrossLinePlot::~CrossLinePlot()
{

}

QString CrossLinePlot::LayerName() const
{
	return QStringLiteral("crossline");
}

void CrossLinePlot::SetVisible(bool visible)
{
	QCPLayer * layer = mParentPlot->layer(LayerName());
	if (layer)
	{
		layer->setVisible(visible);
	}
}

void CrossLinePlot::SetPen(const QPen & pen)
{
	d_ptr->m_Pen = pen;
}

bool CrossLinePlot::MouseButtonDown() const
{
	return d_ptr->m_bLeftButtonPress;
}

bool CrossLinePlot::GetLineVisible(QCP::LineState line) const
{
	switch (line)
	{
	case Qt::Horizontal:
		return d_ptr->m_bIsVisible.testFlag(QCP::E_Horizontal);
		break;
	case Qt::Vertical:
		return d_ptr->m_bIsVisible.testFlag(QCP::E_Vertical);
		break;
	}

	return false;
}

void CrossLinePlot::SetLineShow(QCP::LineState lines)
{
	switch (lines)
	{
	case QCP::E_NULL:
		d_ptr->m_bIsVisible = QCP::E_NULL;
		break;
	case QCP::E_Horizontal:
		d_ptr->m_bIsVisible = QCP::E_Horizontal;
		break;
	case QCP::E_Vertical:
		d_ptr->m_bIsVisible = QCP::E_Vertical;
		break;
	case QCP::E_ALL:
		d_ptr->m_bIsVisible = QCP::E_ALL;
		break;
	}

	if (QCPLayer * layer = mParentPlot->layer(LayerName()))
	{
		layer->replot();
	}

	if (d_ptr->m_bIsVisible == QCP::E_NULL)
	{
		for (CrossLinePlot * crossline : CrossLinePlot::m_BrotherLine)
		{
			if (crossline != this)
			{
				crossline->SyncLinePosition(QPoint(), d_ptr->m_dAxisXValue);
			}
		}
	}
}

void CrossLinePlot::draw(QCPPainter * painter)
{
	Q_UNUSED(painter);

	d_ptr->m_pPainter = painter;
	d_ptr->m_pPainter->setPen(d_ptr->m_Pen);

	if (BasicPlot * plot = dynamic_cast<BasicPlot *>(d_ptr->m_pParentPlot))
	{
		if (d_ptr->m_bIsVisible.testFlag(QCP::E_Vertical))
		{
			if (mParentPlot->xAxis->visible())
			{
				plot->SetToopTipVisible(QCPAxis::atBottom, true);
			}
			//绘制所有坐标轴竖直方向坐标轴十字线(来自同一个plot)
			for (int i = 0; i < mParentPlot->axisRectCount(); ++i)
			{
				DrawLine(mParentPlot->axisRect(i)->axis(QCPAxis::atBottom), Qt::Vertical);
			}
		}
		if (d_ptr->m_bIsVisible.testFlag(QCP::E_Horizontal))
		{
			DrawLine(mParentPlot->yAxis, Qt::Horizontal);
			if (plot->GetAxis(QCPAxis::atRight)->visible())
			{
				plot->SetToopTipVisible(QCPAxis::atLeft | QCPAxis::atRight, true);
			}
			else
			{
				plot->SetToopTipVisible(QCPAxis::atLeft, true);
			}
		}
		if (d_ptr->m_bIsVisible.testFlag(QCP::E_NULL))
		{
			plot->SetToopTipVisible(QCPAxis::atLeft | QCPAxis::atRight | QCPAxis::atBottom, false);
			plot->SetLineTracerVisible(false);
		}
		else
		{
			plot->SetLineTracerVisible(true);
		}
	}
}

void CrossLinePlot::DrawLine(QCPAxis * axis, Qt::Orientation orientation)
{
	if (axis == nullptr)
	{
		return;
	}

	if (d_ptr->m_MousePoint.isNull())
	{
		return;
	}

	double pret, t;
	double epsilon = axis->range().size()*1E-6;
	double minLength = 100000;

	QVector<double> sumTick = axis->tickVector();
	sumTick += axis->subTickVector();
	qSort(sumTick.begin(), sumTick.end());

	if (sumTick.size() <= 2)
	{
		return;//日志
	}

	if (Qt::Vertical == orientation)
	{
		double step = sumTick[1] - sumTick[0];//axis->ticker();
		double value, tickPos;
		int pos = FindNearlyindex(sumTick, axis->pixelToCoord(d_ptr->m_MousePoint.x()));
		value = sumTick[pos];
		tickPos = axis->coordToPixel(value);
		d_ptr->m_dAxisXValue = tickPos;

		QLineF verLine(tickPos, axis->axisRect()->rect().bottom(), tickPos, axis->axisRect()->rect().top());
		d_ptr->m_pPainter->drawLine(verLine);
	}
	else
	{
		t = d_ptr->m_MousePoint.y();
		QLineF horLine(axis->axisRect()->rect().left(), t, axis->axisRect()->rect().right(), t);

		d_ptr->m_pPainter->drawLine(horLine);
	}
}

void CrossLinePlot::SyncLinePosition(const QPoint & pos, double x)
{
	if (pos.isNull())
	{
		d_ptr->m_bIsVisible = QCP::E_NULL;
	}
	else
	{
		d_ptr->m_bIsVisible = QCP::E_Vertical;
	}
	d_ptr->m_MousePoint = pos;
	d_ptr->m_dAxisXValue = x;

	if (QCPLayer * layer = mParentPlot->layer(LayerName()))
	{
		layer->replot();
	}

	if (d_ptr->m_pParentPlot)
	{
		if (d_ptr->m_pParentPlot->TipLabelEnable())
		{
			d_ptr->m_pParentPlot->MoveTipLabel(QPoint(d_ptr->m_dAxisXValue, d_ptr->m_MousePoint.y()));
		}
		if (d_ptr->m_pParentPlot->LineTracerEnable())
		{
			d_ptr->m_pParentPlot->MoveLineTracer(pos);
		}
	}
}

bool CrossLinePlot::RegisiterBortherLine(CrossLinePlot * line)
{
	if (line == nullptr)
	{
		return false;
	}

	if (std::find(CrossLinePlot::m_BrotherLine.begin(), CrossLinePlot::m_BrotherLine.end(), this) == CrossLinePlot::m_BrotherLine.end())
	{
		CrossLinePlot::m_BrotherLine.push_back(this);
	}

	auto iter = std::find(CrossLinePlot::m_BrotherLine.begin(), CrossLinePlot::m_BrotherLine.end(), line);
	if (iter == CrossLinePlot::m_BrotherLine.end())
	{
		if (line->parentPlot() && line->parentPlot()->xAxis)
		{
			line->parentPlot()->xAxis->setTickLabels(false);
		}
		CrossLinePlot::m_BrotherLine.push_back(line);
		return true;
	}

	return false;
}

bool CrossLinePlot::UnregisiterBortherLine(CrossLinePlot * line)
{
	if (line == nullptr)
	{
		return false;
	}

	auto iter = std::find(CrossLinePlot::m_BrotherLine.begin(), CrossLinePlot::m_BrotherLine.end(), line);
	if (iter != CrossLinePlot::m_BrotherLine.end())
	{
		if (line->parentPlot() && line->parentPlot()->xAxis)
		{
			line->parentPlot()->xAxis->setTickLabels(true);
		}
		CrossLinePlot::m_BrotherLine.erase(iter);
		return true;
	}

	return false;
}

void CrossLinePlot::MouseMoveHandle(QMouseEvent * event)
{
	d_ptr->m_MousePoint = event->pos();
	bool containFlag = false;
	for (int i = 0; i < mParentPlot->axisRectCount(); ++i)
	{
		if (mParentPlot->axisRect(i)->rect().contains(d_ptr->m_MousePoint))
		{
			containFlag = true; break;
		}
	}

	if (containFlag)
	{
		SetLineShow(QCP::E_ALL);
	}
	else
	{
		SetLineShow(QCP::E_NULL);
	}
	if (d_ptr->m_bIsVisible.testFlag(QCP::E_NULL) == false)
	{
		for (CrossLinePlot * crossline : CrossLinePlot::m_BrotherLine)
		{
			if (crossline != this)
			{
				crossline->SyncLinePosition(d_ptr->m_MousePoint, d_ptr->m_dAxisXValue);
			}
		}
		mParentPlot->layer(LayerName())->replot();
	}
	if (d_ptr->m_pParentPlot)
	{
		if (d_ptr->m_pParentPlot->TipLabelEnable())
		{
			d_ptr->m_pParentPlot->MoveTipLabel(QPoint(d_ptr->m_dAxisXValue, d_ptr->m_MousePoint.y()));
		}
		if (d_ptr->m_pParentPlot->LineTracerEnable())
		{
			d_ptr->m_pParentPlot->MoveLineTracer(d_ptr->m_MousePoint);
		}
	}
}
