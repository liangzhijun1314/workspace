#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <memory>
#include <functional>

#include <QColor>

#include <QWidget>

#include "PlotDefine.h"
using namespace std;
namespace QCP
{
//	Q_DECLARE_OPERATORS_FOR_FLAGS(QCP::WindowFlags);

	enum WindowFlag	{
		NOTHING = 0,
		TITLE = 0x1,//标题栏
		AVARGE = TITLE * 2,//均线
		QUOTAS = AVARGE * 2,//指标集，k线和k线指标分别拥有不同的指标项
		ZOOM_OUT = QUOTAS * 2,
		ZOOM_IN = ZOOM_OUT * 2,
		SETUP = ZOOM_IN * 2,
		FRUSH = SETUP * 2,
		CLOSE = FRUSH * 2,

		TIMESHARING = TITLE | AVARGE | FRUSH | ZOOM_OUT | ZOOM_IN,//分时快捷窗口属性
		KLINE = QUOTAS | ZOOM_OUT | ZOOM_IN | SETUP | FRUSH,//k线快捷窗口属性
		QUOTA = QUOTAS | SETUP | CLOSE,//k线指标快捷窗口属性
	};

	Q_DECLARE_FLAGS(WindowFlags, WindowFlag);
};

struct QuotaItemPrivate;


/// 描述：指标小条目

class QuotaItem : public QWidget
{
	Q_OBJECT

signals:
	void ItemClicked(QCP::QuotaLineType id, bool visible);

public:
	//quota指标名称，作为唯一id，不支持修改
    QuotaItem(QCP::QuotaLineType id, double value, QWidget * parent = 0);
	~QuotaItem();


public:
	const QString & QuotaName() const;
	void SetValue(double value);
	double GetValue() const;
	void SetTextColor(const QColor & color);
	const QColor & GetTextColor() const;

private:
	QScopedPointer<QuotaItemPrivate> d_ptr;
};

struct PlotWidgetPrivate;

class BasicWidget;


/// 描述：封装了带有标题栏的窗口，主要用于展示图表窗口，使用SetContentWidget接口进行图表窗口设置
/// 注意：不能直接嵌入绘图组建，例如TimeSharingTrendPlot。因为绘图组建没有收据接收能力。可以接收数据能力的窗口有TimeSharingTrendWidget
using namespace std;
class PlotWidget : public QWidget
{
	Q_OBJECT

signals:
	void AddQuotaSignal(QCP::QuotaLineType id);
	void ShowQuotaSignal(QCP::QuotaLineType id, bool);
	void RemoveQuotaSignal(QCP::QuotaLineType id);

public:
    PlotWidget(QWidget * parent = 0, QCP::WindowFlags flags = QCP::KLINE);
	~PlotWidget();

public:
	void SetTitleName(const QString & name);
	void SetAvarageName(const QString & name);
	void SetContentWidget(BasicWidget * widget);
        void RegisterToolBarCallback(std::function<void (QCP::WindowFlag flag)> & onclicked);

	QuotaItem * AddQuota(QCP::QuotaLineType id, double value);
	bool RemoveQuota(QCP::QuotaLineType id);
	bool SetQuotaValue(QCP::QuotaLineType id, double value);
	QColor GetQuotaColor(QCP::QuotaLineType id) const;

private slots:
	void ToobarButtonClicked(int);

private:
	void InitializeUI();
	void SetupTitile();
	void SetupContentWidget();

private:
	QScopedPointer<PlotWidgetPrivate> d_ptr;
};

#endif // PLOTWIDGET_H
