#ifndef DEFDATETIMEEDIT_H
#define DEFDATETIMEEDIT_H

#include <QDateTimeEdit>
#include "DefineCalendar.h"

class DefDateTimeEdit : public QDateTimeEdit
{
	Q_OBJECT

public:
	DefDateTimeEdit(QWidget *parent);
	~DefDateTimeEdit();
	void setMyStytle();

protected slots:
	void getDateTime(const QDateTime &dateTime);

private:
	DefineCalendar *m_DefCalendar;
	
};

#endif // DEFDATETIMEEDIT_H
