#ifndef QCPAXISTICKERPIXEL_H
#define QCPAXISTICKERPIXEL_H

#include "QCustomplot.h"

struct AxisFixedPixelTickerPrivate;

/// 描述：定制化坐标轴，实现了固定像素，使用setTickPixelStep接口设置

class AxisFixedPixelTicker : public QCPAxisTicker
{
public:
	AxisFixedPixelTicker(QCPAxis * axis);
	~AxisFixedPixelTicker();

public:
	void SetTickPixelStep(int pixel);
	int GetTickPixelStep() const;

protected:
	//QCPAxisTicker
	virtual double getTickStep(const QCPRange & range) override;

private:
	QScopedPointer<AxisFixedPixelTickerPrivate> d_ptr;
};

#endif // QCPAXISTICKERPIXEL_H
