#include "layoutdia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LayoutDia w;
    w.show();

    return a.exec();
}
