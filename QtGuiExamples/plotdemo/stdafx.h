#include <QWidget>
#include <iostream>
#include <stdio.h>

//数据默认从小到大
int FindNearlyindex(const QVector<double> & array, double value);


//数组必须是等差数列
void FindNearlyindex(double min, double max, double step, double value, double & resultValue);
