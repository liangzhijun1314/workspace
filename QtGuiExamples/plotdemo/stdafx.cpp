#include "stdafx.h"
#include <QtCore/qmath.h>



void FindNearlyindex(double min, double max, double step, double value, double & resultValue)
{
	Q_ASSERT(step != 0);

	if (value <= min)
	{
		resultValue = min;
		return;
	}
	if (value >= max)
	{
		resultValue = max;
		return;
	}
	double key = (value - min) * 1.0 / step;

    // qCeil 返回大于或者等于指定表达式的最小整数
    //qFloor 其功能是“向下取整”,或者说“向下舍入”,即取不大于x的最大整数(与“四舍五入”不同,下取整是直接去掉小数部分)
    if (qCeil(key) - key > key - qFloor(key))
	{
		resultValue = min + qFloor(key) * step;
	}
	else
	{
		resultValue = min + qCeil(key) * step;
	}
}

namespace
{
	int BinaryFind(const QVector<double> & array, int left, int right, double value)
	{
		if (left == right)
		{
			return left;
		}

		int mid = (left + right) / 2;
		if (left + 1 == right)
		{
			if (qFabs(array[right] - value) <= qFabs(value - array[left]))
			{
				return right;
			}
			else
			{
				return left;
			}
		}

		if (array[mid] < value)
		{
			return BinaryFind(array, mid, right, value);
		}
		else if (array[mid] > value)
		{
			return BinaryFind(array, left, mid, value);
		}
		else
		{
			return mid;
		}
	}
}

int FindNearlyindex(const QVector<double> & array, double value)
{
	if (array.size() == 0)
	{
		return -1;
	}

	return BinaryFind(array, 0, array.size() - 1, value);
}
