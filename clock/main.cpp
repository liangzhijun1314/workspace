/*******************************************************************************
** @file:     main.cpp
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-2-5
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#include "clock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clock w;
    w.show();

    return a.exec();
}
