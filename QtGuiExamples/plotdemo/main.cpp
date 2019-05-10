#include "stdafx.h"
#include "plotdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	plotdemo w;
	w.show();

	return a.exec();
}
