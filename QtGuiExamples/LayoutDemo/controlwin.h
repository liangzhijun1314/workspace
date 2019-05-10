#ifndef CONTROLWIN_H
#define CONTROLWIN_H

#include <QWidget>
#include <QFrame>
#include <QtGui>

class ControlWin : public QFrame
{
    Q_OBJECT

public:
	explicit ControlWin(QWidget *parent = 0);
    ~ControlWin();

protected:
	void timerEvent(QTimerEvent *event);
	void paintEvent(QPaintEvent * event);

signals:
	void GoUpdata();

private:

};

#endif // CONTROLWIN_H
