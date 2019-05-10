#include "frmshowapi.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmShowAPI w;
    w.show();

    return a.exec();
}
