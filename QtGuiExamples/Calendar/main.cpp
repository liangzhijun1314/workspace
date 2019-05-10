#include "mycalendar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyCalendar w;
	w.show();
	return a.exec();
}
