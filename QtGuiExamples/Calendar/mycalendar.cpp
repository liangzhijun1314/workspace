#include "mycalendar.h"

MyCalendar::MyCalendar(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setFixedHeight(60);
	this->setFixedWidth(290);

	m_defDateTimeEdit = new DefDateTimeEdit(this);

	setCentralWidget(m_defDateTimeEdit);
}

MyCalendar::~MyCalendar()
{

}
