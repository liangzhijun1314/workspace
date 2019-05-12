#include "mainwindow.h"
#include "tableview.h"
#include "tablemodel.h"
#include <QLayout>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)

{
    this->resize(800, 600);
    TableView *tv = new TableView(this);
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(tv);
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{

}
