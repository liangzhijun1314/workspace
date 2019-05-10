#ifndef DEFINECALENDAR_H
#define DEFINECALENDAR_H

#include <QCalendarWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QPushButton;
class QTimeEdit;
class QDateTime;
QT_END_NAMESPACE

class DefineCalendar : public QCalendarWidget
{
	Q_OBJECT

public:
	DefineCalendar(QWidget *parent);
	~DefineCalendar();

signals:
	void setFinished(const QDateTime &dateTime);

public slots:
	void UpdateYear();
	void UpdatePage();
	void SetToday();
	void ClearTime();

protected slots:
	void BtnSlots();
	void ComboBoxSlots(int index);
	void CurPageChange(int year, int month);

protected:
	void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
	void InitWidgets();
	QWidget *widget_top;
	QPushButton *pushBtn_YL;
	QComboBox *comboBox_Year;
	QPushButton *pushBtn_YR;
	QPushButton *pushBtn_ML;
	QComboBox *comboBox_Month;
	QPushButton *pushBtn_MR;

	QWidget *widget_bottom;
	QLabel *label_Time;
	QTimeEdit *timeEdit;
	QPushButton *pushBtn_clear;
	QPushButton *pushBtn_today;
	QPushButton *pushBtn_Ok;
};

#endif // DEFINECALENDAR_H
