#ifndef PlotDefine_h__
#define PlotDefine_h__

namespace QCP
{
	enum AxisRange
	{
		AR_LEFT,
		AR_RIGHT,
		AR_TOP,
		AR_BOTTOm,
		AR_NULL,
		AR_ALLAxis,
	};

	enum ViewType
	{
		EVT_NULL,
		EVT_TIME_DAY_1,
		EVT_TIME_DAY_5,
		EVT_KLINE_DAY,
		EVT_KLINE_WEEK,
		EVT_KLINE_MONTH,
	};

	enum QuotaLineType
	{
		QT_NULL,

		//分时指标
		QT_TIME,               // 分时线
		QT_AVERAGE,               // 均线
		QT_VOL,
		QT_LMR,//量比

		//k线指标
		QT_KLINE,
		QT_MACD,
		QT_KDJ,
		QT_RSI,
		QT_ARBR,
		QT_DMI,
		QT_CR,
		QT_PSY,
		QT_KD,
		QT_DMA,
	};
	Q_DECLARE_FLAGS(QuotaLineTypes, QuotaLineType);

	enum PlotElementKind
	{
		PEK_BAR,//柱状图
		PEK_GRAPH,//图通折线图
		PEK_GRAPH2,//带有画刷折线图
		PEK_GRAPH3,//当前点画垂直线到x轴折线图
		PEK_GRAPH4,//圆圈折线图
		PEK_AREA,//面积图
		PEK_FINACIAL,//实体图
	};
}
#endif // PlotDefine_h__