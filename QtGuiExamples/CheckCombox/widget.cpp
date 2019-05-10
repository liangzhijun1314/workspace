#include "widget.h"
#include "ui_widget.h"
#include "ccheckcombox.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    addComboItem();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addComboItem()
{
    ui->comboBox->appendItem("1111", false);
    ui->comboBox->appendItem("2222", false);
    ui->comboBox->appendItem("3333", false);
    ui->comboBox->appendItem("4444", false);
    ui->comboBox->appendItem("5555", false);
    ui->comboBox->appendItem("6666", false);
}

void Widget::on_comboBox_checkedStateChange(int index, bool bChecked)
{
    qDebug()<<index<<bChecked;
}
