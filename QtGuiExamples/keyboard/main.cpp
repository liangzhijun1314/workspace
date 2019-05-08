#include <QApplication>
#include "widgetkeyboard.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetKeyboard w;
    w.show();

    return a.exec();
}
