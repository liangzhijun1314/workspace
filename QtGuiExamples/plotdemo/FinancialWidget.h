#ifndef FINANCIALWIDGET_H
#define FINANCIALWIDGET_H

#include <QWidget>

#include "BasicWidget.h"

struct FinancialWidgetPrivate;

class FinancialPlot;

class FinancialWidget : public BasicWidget//, public stock::IKLineObserve
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(FinancialWidget)

public:
	FinancialWidget(QWidget * parent = nullptr);
	~FinancialWidget();

public:	//图表类型
	//void SetPlotType(stock::KViewType type);
	//stock::KViewType GetPlotType() const;

	////指标类型，当图表类型为空时，该接口才有用
	//void SetQuotaType(stock::KLineQuotaType type);
	//stock::KLineQuotaType GettQuotaType() const;

	FinancialPlot * GetFinancialPlot() const;

protected:
	//stock::ITimeLineObserve
// 	virtual void OnUpdate(const DataContainer<stock::KLineData> & data) override;
// 	virtual void OnUpdate2(const stock::KLineQuotaType & p1, const DataContainer<stock::LineData> & p2) override;

private:
	void InitializeUI();
};

#endif // FINANCIALWIDGET_H
