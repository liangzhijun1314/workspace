#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QMainWindow>
#include "ui_mycalendar.h"
#include "DefDateTimeEdit.h"

class MyCalendar : public QMainWindow
{
	Q_OBJECT

public:
	MyCalendar(QWidget *parent = 0);
	~MyCalendar();

private:
	Ui::MyCalendarClass ui;
	DefDateTimeEdit* m_defDateTimeEdit;
};

#endif // MYCALENDAR_H
