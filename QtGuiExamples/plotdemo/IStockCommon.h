#ifndef IStockCommon_h__
#define IStockCommon_h__

namespace stock {
    // K线类型
    enum KLineType
    {
        KLINE_UNKNOW,
        KLINE_DAY,          // 日K
        KLINE_WEEK,			// 周K
        KLINE_MONTH			// 月K
    };

    // 复权方式
    enum FuQuanType
    {
        FUQUAN_UNKNOW,
        FUQUAN_NONE,        // 不复权
        FUQUAN_FORWARD,		// 前复权
        FUQUAN_BACKWARD		// 后复权
    };
}
#endif // IStockCommon_h__
