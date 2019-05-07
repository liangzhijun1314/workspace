#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QPushButton>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    CustomButton(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void onClicked();
};

class CustomButtonEx : public CustomButton
{
    Q_OBJECT
public:
    CustomButtonEx(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent * event);
};

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    CustomWidget(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent * event);
};
#endif // CUSTOMBUTTON_H
