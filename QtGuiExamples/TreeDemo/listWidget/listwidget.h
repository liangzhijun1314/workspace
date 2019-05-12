#ifndef LISTWIDGET_H
#define LISTWIDGET_H
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QListWidget>

class ListWidget : public QWidget
{
    Q_OBJECT
    
public:
    ListWidget(QWidget *parent = 0);
    ~ListWidget();

private:
    QLabel *label;
    QListWidget * listWidget;
};

#endif // LISTWIDGET_H
