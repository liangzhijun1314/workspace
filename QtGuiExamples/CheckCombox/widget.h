#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}
class CCheckCombox;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void addComboItem();
private slots:

    void on_comboBox_checkedStateChange(int index, bool bChecked);

signals:
    //状态改变后发送一个信号，告诉外界。
    void checkedStateChange(int index, bool bChecked);
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
