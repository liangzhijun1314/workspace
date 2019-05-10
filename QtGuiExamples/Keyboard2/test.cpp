#include "test.h"
#include "ui_test.h"
#include "this_config.h"
bool open_flag;
test::test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(showKeyBoard()));
    ui->label->setPixmap(QPixmap("ico/Keyboard.png"));
  //  QObject::connect(ui->label,SIGNAL(clicked()),this,SLOT(showKeyBoard()));
  //  connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(showKeyBoard()));
    connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(showKeyBoard()));
}
void test::mousePressEvent(QMouseEvent *e)
{
    showKeyBoard();

}
void test::showKeyBoard()
{
    Window_show.ShowKeyBoard(this);
}

test::~test()
{
    delete ui;
}
