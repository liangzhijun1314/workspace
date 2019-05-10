#include "controlwin.h"

ControlWin::ControlWin(QWidget *parent) :
	QFrame(parent)
{
    //startTimer(1000);
	connect(this, SIGNAL(GoUpdata()), this, SLOT(update()), Qt::QueuedConnection);
    this->setFocusPolicy(Qt::ClickFocus);
}

ControlWin::~ControlWin()
{

}

void ControlWin::timerEvent(QTimerEvent *event) //计时器
{
	GoUpdata();
}

#include <QPainter>
void ControlWin::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	QRect crect;
	crect = contentsRect();
    QImage image(":images/160449439.png");
	painter.drawImage(crect, image);
}
