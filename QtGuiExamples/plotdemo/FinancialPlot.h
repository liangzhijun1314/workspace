#ifndef FINANCIALPLOT_H
#define FINANCIALPLOT_H

#include "BasicPlot.h"


struct FinancialPlotPrivate;

class FinancialPlot : public BasicPlot
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(FinancialPlot)

protected:
    FinancialPlot(QWidget * parent = 0);

public:
	~FinancialPlot();

public: 
	//interacte operatation
	void SetInteractions(const QCP::Interactions & interactions);//设置交互模式 不建议主动调用
	void SetDragOrientation(Qt::Orientations orientations);//设置拖拽时放向  
	void SetZoomOrientation(Qt::Orientations orientations);
	void SetCursorShape(Qt::CursorShape shape);

	void SetVerticalAxisSynch(bool synch);//是否启用坐标轴同步

	//坐标轴同步注册接口
	bool RegisiterBrotherRange(QCPAxis::AxisType type, PlotCallback * plot);
	bool UnregisiterBrotherRange(QCPAxis::AxisType type, PlotCallback * plot);

	//add entity
	QCPFinancial * AddFinancial(QCPAxis * keyAxis = 0, QCPAxis * valueAxis = 0);
	void SetFinancialData(const std::vector<double> & keys
		, const std::vector<double> & open
		, const std::vector<double> & high
		, const std::vector<double> & low
		, const std::vector<double> & close
		, QCPFinancial * financial = nullptr);
	void AddFinancialData(double key, double open, double high, double low, double close, QCPFinancial * financial = nullptr);
	void ModifyFinancialData(double key, double open, double high, double low, double close, QCPFinancial * financial = nullptr);

protected:
	FinancialPlot(FinancialPlotPrivate & pd, QWidget * parent = nullptr);

private:
	void AxisRangeChanged(QCPAxis::AxisType type, const QCPRange & range);

	friend class FinancialWidgetPrivate;
};

#endif // FINANCIALPLOT_H
