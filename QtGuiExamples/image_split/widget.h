#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include<QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    QPixmap getPixmap(QString pixmap_name, int count, int index);

private:
    Ui::Widget *ui;
    QPushButton *level_button;
    QPushButton *grade_button;

};

#endif // WIDGET_H
