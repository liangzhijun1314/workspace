#include "listwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListWidget w;
    w.resize(400, 200);
    w.show();
    
    return a.exec();
}
