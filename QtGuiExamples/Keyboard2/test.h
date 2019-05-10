#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include "this_config.h"
#include "keyboard.h"
namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT
    
public:
    explicit test(QWidget *parent = 0);
    ~test();
    private:
     Keyboard    *k_board;
protected:
    void mousePressEvent ( QMouseEvent * e );
private slots:
    void showKeyBoard();

private:
    Ui::test *ui;
};

#endif // TEST_H
