#include "listwidget.h"
#include <QStyle>
#include <QFile>
#include <QScrollBar>
#include <QLayout>

ListWidget::ListWidget(QWidget *parent)
    : QWidget(parent)
{

//    QFile file(":/scrollbar.qss");
//    file.open(QFile::ReadOnly);

    label = new QLabel;
    label->setFixedWidth(70);
    listWidget = new QListWidget;

    QSize size;
    size.setWidth(80);
    size.setHeight(100);

    listWidget->setIconSize(size);
//    listWidget->setStyleSheet(file.readAll());
    listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical"
                                                   "{"
                                                   "width:8px;"
                                                   "background:rgba(0,0,0,0%);"
                                                   "margin:0px,0px,0px,0px;"
                                                   "padding-top:9px;"
                                                   "padding-bottom:9px;"
                                                   "}"
                                                   "QScrollBar::handle:vertical"
                                                   "{"
                                                   "width:8px;"
                                                   "background:rgba(0,0,0,25%);"
                                                   " border-radius:4px;"
                                                   "min-height:20;"
                                                   "}"
                                                   "QScrollBar::handle:vertical:hover"
                                                   "{"
                                                   "width:8px;"
                                                   "background:rgba(0,0,0,50%);"
                                                   " border-radius:4px;"
                                                   "min-height:20;"
                                                   "}"
                                                   "QScrollBar::add-line:vertical"
                                                   "{"
                                                   "height:9px;width:8px;"
                                                   "border-image:url(:/images/a/3.png);"
                                                   "subcontrol-position:bottom;"
                                                   "}"
                                                   "QScrollBar::sub-line:vertical"
                                                   "{"
                                                   "height:9px;width:8px;"
                                                   "border-image:url(:/images/a/1.png);"
                                                   "subcontrol-position:top;"
                                                   "}"
                                                   "QScrollBar::add-line:vertical:hover"
                                                   "{"
                                                   "height:9px;width:8px;"
                                                   "border-image:url(:/images/a/4.png);"
                                                   "subcontrol-position:bottom;"
                                                   "}"
                                                   "QScrollBar::sub-line:vertical:hover"
                                                   "{"
                                                   "height:9px;width:8px;"
                                                   "border-image:url(:/images/a/2.png);"
                                                   "subcontrol-position:top;"
                                                   "}"

                                                   "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                                                   "{"
                                                   "background:rgba(0,0,0,10%);"
                                                   "border-radius:4px;"
                                                   "}"

                                                   );

    this->setStyleSheet("background:white;");
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/indigo.jpg"), tr("Line"));
    item->setSizeHint(QSize(200,80));
    listWidget->addItem(item);
    listWidget->setStyleSheet("QListWidget::item{background-color:#000000;} QListWidget::item:hover{background-color:#fff000;}");
    item= new QListWidgetItem(QIcon(":/images/green.jpg"), tr("Rectangle"));
    item->setSizeHint(QSize(200,80));
    listWidget->addItem(item);
    item = new QListWidgetItem(QIcon(":/images/green.jpg"), tr("Oval"));
    item->setSizeHint(QSize(200,80));
    listWidget->addItem(item);
    item = new QListWidgetItem(QIcon(":/images/indigo.jpg"), tr("Triangle"));
    item->setSizeHint(QSize(200,80));
    listWidget->addItem(item);
    item = new QListWidgetItem(QIcon(":/images/test.png"), tr("test"));
    item->setSizeHint(QSize(200,80));
    listWidget->addItem(item);

    item = new QListWidgetItem(QIcon(":/images/rabit.png"), tr(""));

    item->setSizeHint(QSize(200,80));
    listWidget->addItem(item);

    listWidget->setViewMode(QListView::ListMode);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(listWidget);

    setLayout(layout);


    connect(listWidget, SIGNAL(currentTextChanged(QString)), label, SLOT(setText(QString)));
}

ListWidget::~ListWidget()
{
    
}
