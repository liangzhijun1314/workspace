#include "DefineCalendar.h"
#include <QWidget>
#include <QComboBox>
#include <QtGui>
#include <QPushButton>
#include <QListView>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimeEdit>

DefineCalendar::DefineCalendar(QWidget *parent)
	: QCalendarWidget(parent)
{
	setMinimumDate(QDate(2000,1,1));
	setMaximumDate(QDate(2050,1,1));
	InitWidgets();
	setMinimumHeight(240);
	setNavigationBarVisible(false);
	setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
//	this->layout()->setSizeConstraint(QLayout::SetFixedSize);
	connect(this, SIGNAL(currentPageChanged(int,int)), this, SLOT(CurPageChange(int,int)));
	UpdateYear();
	
}

DefineCalendar::~DefineCalendar()
{

}

void DefineCalendar::paintCell( QPainter *painter, const QRect &rect, const QDate &date ) const
{
 	if (date == this->selectedDate())
 	{
 		painter->save();
 		painter->setRenderHint(QPainter::Antialiasing);
 		painter->setPen(Qt::NoPen);
 		painter->setBrush(QColor(0, 159, 149));
 		painter->drawRect(rect);
 		//int nR = (rect.width()>rect.height()?rect.height():rect.width())/2.-2;
 		//painter->drawEllipse(rect.center(),nR,nR);
 		painter->setPen(Qt::white);
 		painter->drawText(rect,Qt::AlignCenter,QString::number(date.day()));
 		painter->restore();
 	}
 	else
	{
		QCalendarWidget::paintCell(painter,rect,date);
	}
	
}

void DefineCalendar::InitWidgets()
{
	//顶部
	widget_top = new QWidget(this);
	comboBox_Year = new QComboBox(this);
	comboBox_Month = new QComboBox(this);
	pushBtn_YL = new QPushButton(this);
	pushBtn_YR = new QPushButton(this);
	pushBtn_ML = new QPushButton(this);
	pushBtn_MR = new QPushButton(this);

	comboBox_Year->setView(new QListView());
	comboBox_Month->setView(new QListView());

	QStringList monthList;
	monthList<<tr("Jan")<<tr("Feb")<<tr("Mar")<<tr("Apr")<<tr("May")<<tr("Jun")
		<<tr("Jul")<<tr("Aug")<<tr("Sep")<<tr("Oct")<<tr("Nov")<<tr("Dec");
	comboBox_Month->addItems(monthList);

	
	int nO = 24;
	int nI = 20;
	pushBtn_YL->setFixedSize(nO,nO);
	pushBtn_YL->setIconSize(QSize(nI,nI));
	pushBtn_YL->setIcon(QPixmap("Resources/al.png"));

	pushBtn_YR->setFixedSize(nO,nO);
	pushBtn_YR->setIconSize(QSize(nI,nI));
	pushBtn_YR->setIcon(QPixmap("Resources/ar.png"));

	pushBtn_ML->setFixedSize(nO,nO);
	pushBtn_ML->setIconSize(QSize(nI,nI));
	pushBtn_ML->setIcon(QPixmap("Resources/al.png"));

	pushBtn_MR->setFixedSize(nO,nO);
	pushBtn_MR->setIconSize(QSize(nI,nI));
	pushBtn_MR->setIcon(QPixmap("Resources/ar.png"));

	QHBoxLayout *HTopLayout = new QHBoxLayout;
	HTopLayout->setContentsMargins(4,4,4,4);
	HTopLayout->setSpacing(0);
	widget_top->setLayout(HTopLayout);
	HTopLayout->addWidget(pushBtn_YL);
	HTopLayout->addWidget(comboBox_Year);
	HTopLayout->addWidget(pushBtn_YR);
	HTopLayout->addStretch(1);
	HTopLayout->addWidget(pushBtn_ML);
	HTopLayout->addWidget(comboBox_Month);
	HTopLayout->addWidget(pushBtn_MR);

	//底部
	widget_bottom = new QWidget(this);
	label_Time = new QLabel(this);
	timeEdit = new QTimeEdit(this);
	pushBtn_clear = new QPushButton(this);
	pushBtn_Ok = new QPushButton(this);
	pushBtn_today = new QPushButton(this);

	label_Time->setText(tr("Time"));
	timeEdit->setDisplayFormat("hh:mm:ss");
	pushBtn_clear->setText(tr("Clear"));
	pushBtn_Ok->setText(tr("Ok"));
	pushBtn_today->setText(tr("Today"));

	QSize btnSize(50,24);
	pushBtn_today->setFixedSize(btnSize);
	pushBtn_clear->setFixedSize(btnSize);
	pushBtn_Ok->setFixedSize(btnSize);

	QHBoxLayout *HBtnLayout = new QHBoxLayout;
	//HBtnLayout->setContentsMargins(4,4,4,4);
	HBtnLayout->setSpacing(0);
	widget_bottom->setLayout(HBtnLayout);
	HBtnLayout->addWidget(label_Time);
	HBtnLayout->addWidget(timeEdit);
	HBtnLayout->addSpacing(4);
	HBtnLayout->addStretch(1);
	HBtnLayout->addWidget(pushBtn_clear);
	HBtnLayout->addWidget(pushBtn_today);
	HBtnLayout->addWidget(pushBtn_Ok);

	QVBoxLayout *VMainLayout = qobject_cast<QVBoxLayout *>(this->layout());
	VMainLayout->insertWidget(0,widget_top);
	VMainLayout->addWidget(widget_bottom);

	//类名，信号和槽
	widget_top->setObjectName("CalTopWidget");
	comboBox_Year->setObjectName("CalComboBox");
	comboBox_Month->setObjectName("CalComboBox");
	pushBtn_YL->setObjectName("CalPushBtnT1");
	pushBtn_YR->setObjectName("CalPushBtnT1");
	pushBtn_ML->setObjectName("CalPushBtnT1");
	pushBtn_MR->setObjectName("CalPushBtnT1");

	widget_bottom->setObjectName("CalBottomWidget");
	label_Time->setObjectName("CalLabel");
	timeEdit->setObjectName("CalTimeEdit");
	pushBtn_clear->setObjectName("CalPushBtnT2");
	pushBtn_Ok->setObjectName("CalPushBtnT2");
	pushBtn_today->setObjectName("CalPushBtnT2");

	connect(pushBtn_YL, SIGNAL(clicked()), this, SLOT(BtnSlots()));
	connect(pushBtn_YR, SIGNAL(clicked()), this, SLOT(BtnSlots()));
	connect(pushBtn_ML, SIGNAL(clicked()), this, SLOT(BtnSlots()));
	connect(pushBtn_MR, SIGNAL(clicked()), this, SLOT(BtnSlots()));
	connect(pushBtn_today, SIGNAL(clicked()), this, SLOT(SetToday()));
	connect(pushBtn_clear, SIGNAL(clicked()), this, SLOT(ClearTime()));
	connect(pushBtn_Ok, SIGNAL(clicked()), this, SLOT(BtnSlots()));

	connect(comboBox_Year, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxSlots(int)));
	connect(comboBox_Month, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxSlots(int)));
}

void DefineCalendar::UpdateYear()
{
	comboBox_Year->clear();
	QDate d1 = this->minimumDate();
	QDate d2 = this->maximumDate();
	for (int i = d1.year(); i<= d2.year(); i++)
	{
		comboBox_Year->addItem(tr("%1").arg(i));
	}
}

void DefineCalendar::SetToday()
{
	QDate curDate = QDate::currentDate();
	int year = curDate.year();
	int month = curDate.month();
	this->setSelectedDate(curDate);
//	comboBox_Year->setCurrentText(QString::number(year));
	comboBox_Month->setCurrentIndex(month-1);
	timeEdit->setTime(QTime::currentTime());
}

void DefineCalendar::ClearTime()
{
	timeEdit->setTime(QTime(0,0,0));
}

void DefineCalendar::BtnSlots()
{
	QPushButton *pBtn = qobject_cast<QPushButton *>(sender());
	if (pBtn == pushBtn_Ok)
	{
		QDateTime curDateTime;
		curDateTime.setDate(this->selectedDate());
		curDateTime.setTime(timeEdit->time());
		emit setFinished(curDateTime);
		emit clicked(curDateTime.date());
		emit activated(curDateTime.date());
	}
	else
	{
		if (pBtn == pushBtn_YL)
		{
			int curInt = comboBox_Year->currentIndex()-1;
			if (curInt<=0)
			{
				curInt = 0;
			}
			comboBox_Year->setCurrentIndex(curInt);
		}
		else if (pBtn == pushBtn_YR)
		{
			int curInt = comboBox_Year->currentIndex()+1;
			if (curInt > comboBox_Year->count()-1)
			{
				curInt = comboBox_Year->count()-1;
			}
			comboBox_Year->setCurrentIndex(curInt);
		}
		else if (pBtn == pushBtn_ML)
		{
			int curInt = comboBox_Month->currentIndex()-1;
			if (curInt<=0)
			{
				curInt = 0;
			}
			comboBox_Month->setCurrentIndex(curInt);
		}
		else if (pBtn == pushBtn_MR)
		{
			int curInt = comboBox_Month->currentIndex()+1;
			if (curInt > comboBox_Month->count()-1)
			{
				curInt = comboBox_Month->count()-1;
			}
			comboBox_Month->setCurrentIndex(curInt);
		}
		UpdatePage();
	}
}

void DefineCalendar::ComboBoxSlots( int index )
{
	UpdatePage();
}

void DefineCalendar::UpdatePage()
{
	int nYear = comboBox_Year->currentText().toInt();
	int nMonth = comboBox_Month->currentIndex()+1;
	this->setCurrentPage(nYear,nMonth);
}

void DefineCalendar::CurPageChange( int year, int month )
{
//	comboBox_Year->setCurrentText(QString::number(year));
	comboBox_Month->setCurrentIndex(month-1);
}


