#include <QApplication>
#include "threaddialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ThreadDialog *threaddialog = new ThreadDialog;
    threaddialog->exec();
    
    return a.exec();
}
