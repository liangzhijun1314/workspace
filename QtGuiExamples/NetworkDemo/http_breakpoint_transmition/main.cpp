#include "httpdownload.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpDownload w;
    w.show();

    return a.exec();
}
