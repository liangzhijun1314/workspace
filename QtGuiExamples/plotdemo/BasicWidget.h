#ifndef BASCIWIDGET_H
#define BASCIWIDGET_H

#include <QWidget>

#include "BasicPlot.h"

struct BasicWidgetPrivate;

class QuotaItem;
class PlotWidget;

namespace QCP
{
	inline PlotElementKind Quota2ElementKind(QuotaLineType type)
	{
		PlotElementKind output;
		switch (type)
		{
		case QT_TIME:
			output = PEK_GRAPH2;
			break;
		case QT_AVERAGE:
		case QT_LMR:
			output = PEK_GRAPH;
			break;
		case QT_VOL:
			output = PEK_BAR;
			break;
		case QT_KLINE:
			output = PEK_FINACIAL;
			break;
		default:
			break;
		}
	}
}


/// 描述：包装绘图组件类基类，可以通过关联PlotWidget类来操作指标线、或者直接调用共有槽接口操作指标线
/// 指标线：指标下的线，通常情况下一个指标下有多个指标线


class BasicWidget : public QWidget
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(BasicWidget);

public:
	BasicWidget(QWidget * parent);
	~BasicWidget();

public:
	void SetWrapWidget(PlotWidget * widget);
	virtual void SetPresentPriceVisible(bool visible){};//是否启用现价线

public slots:
	void AddQuotaSlot(QCP::QuotaLineType id);
	void RemoveQuotaSlot(QCP::QuotaLineType id);
	void ShowQuotaSlot(QCP::QuotaLineType id, bool);

protected:
	BasicWidget(BasicWidgetPrivate & pd, QWidget * parent = nullptr);

protected:
	QScopedPointer<BasicWidgetPrivate> d_ptr;
};

#endif // BASCIWIDGET_H
