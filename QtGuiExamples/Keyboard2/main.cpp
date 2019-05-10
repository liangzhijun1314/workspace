#include <QtWidgets/QApplication>
#include "keyboard.h"
#include "test.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName(GLOBAL_CODEC);
    QTextCodec::setCodecForLocale(codec);
    test *t = new test();
    t->show();
    return a.exec();
}
