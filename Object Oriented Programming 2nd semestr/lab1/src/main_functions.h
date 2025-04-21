#include <QApplication>
#include <qboxlayout.h>
#include <qwidget.h>

#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

void unlockButtons(QHBoxLayout *Layout, bool flag)
{
    for (int i=0;i<Layout->count();i++)
    {
        Layout->itemAt(i)->widget()->setDisabled(not(flag));
    }
}


#endif // MAIN_FUNCTIONS_H

