#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class CustomButton;
class CustomButtonEx;
class CustomWidget;
class CustomEvent;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent *event);
    bool event(QEvent *event);  //处理自定义事件方法1
    void processEvent(CustomEvent *event);
    void customEvent(QEvent *event);//处理自定义事件方法2
private:
    CustomButton * customBtn;
    CustomButtonEx *customBtnEx;
    CustomWidget *customWidget;
};

#endif // WIDGET_H
