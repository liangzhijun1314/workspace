#include "stdafx.h"

#include "AxisFixedPixelTicker.h"

struct AxisFixedPixelTickerPrivate
{
	int m_iPixel = 25;
	QCPAxis * m_pDependAxis = nullptr;
};

AxisFixedPixelTicker::AxisFixedPixelTicker(QCPAxis * axis)
	: QCPAxisTicker()
	, d_ptr(new AxisFixedPixelTickerPrivate)
{
	d_ptr->m_pDependAxis = axis;
}

AxisFixedPixelTicker::~AxisFixedPixelTicker()
{

}

void AxisFixedPixelTicker::SetTickPixelStep(int pixel)
{
	d_ptr->m_iPixel = pixel;
}

int AxisFixedPixelTicker::GetTickPixelStep() const
{
	return d_ptr->m_iPixel;
}

double AxisFixedPixelTicker::getTickStep(const QCPRange & range) 
{
	if (d_ptr->m_pDependAxis)
	{
		bool vertical;
		if (d_ptr->m_pDependAxis->axisType() == QCPAxis::atLeft
			|| d_ptr->m_pDependAxis->axisType() == QCPAxis::atRight)
		{
			vertical = true;
		}
		else
		{
			vertical = false;
		}

		int screenLength = vertical ? d_ptr->m_pDependAxis->axisRect()->rect().height() : d_ptr->m_pDependAxis->axisRect()->rect().width();
		return d_ptr->m_iPixel * range.size() / screenLength;
	}
	else
	{
        return QCPAxisTicker::getTickStep(range);
	}
}
