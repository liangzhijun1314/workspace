#ifndef CCHECKCOMBOX_H
#define CCHECKCOMBOX_H

#include <QComboBox>
#include <QMouseEvent>
#include <QAbstractItemView>
#include <QItemSelectionModel>
/**
 * @brief The CCheckCombox class
 * 思路：看下QComboBox 的addItem接口
 * void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant());
 * 第一个为图片,第二个为内容,第三个为参数可以保存的状态,那么我们准备两张图片 选中与未选中
 * 1 鼠标点击复选框图片时,判断点击了哪一项
 * 2 取出那一项的userData判断当前是什么状态
 * 3 根据状态更新图片
 */
class Widget;
class CCheckCombox : public QComboBox
{
    Q_OBJECT
public:
    explicit CCheckCombox(QWidget *parent = 0);

    //添加下拉框内容
    void appendItem(const QString &text, bool bChecked);

    //QComboBox的虚函数用来隐藏列表框,当单击是复选框时不让隐藏，用来改变状态
    void hidePopup();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    //更新更改项的状态
    void updateIndexStatus(int index);

signals:
    //状态改变后发送一个信号，告诉外界。
    void checkedStateChange(int index, bool bChecked);

public slots:

};

#endif // CCHECKCOMBOX_H
