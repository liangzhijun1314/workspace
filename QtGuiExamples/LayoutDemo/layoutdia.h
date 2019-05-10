#ifndef LAYOUTDIA_H
#define LAYOUTDIA_H

#include <QDialog>
#include "controlwin.h"

namespace Ui {
class LayoutDia;
}

class LayoutDia : public QDialog
{
    Q_OBJECT

public:
    enum ChildState{NoLayout = 0, JustOne = 0x00000001, Number_4 = 0x00000002, Number_6 = 0x00000004,
                    Number_9 = 0x00000008, Number_8 = 0x00000010, Number_10 = 0x00000020,
                    Number_13 = 0x00000040, Number_16 = 0x00000080, Number_10_2 = 0x00000100, Number_13_2 = 0x00000200,
                    Number_14 = 0x00000400, Number_17 = 0x00000800,
                    Number_19 = 0x00001000, Number_22 = 0x00002000, Number_25 = 0x00004000};

    explicit LayoutDia(QWidget *parent = 0);
    ~LayoutDia();

private slots:
    void onComboBoxCurrentIndexChanged(int item);

private:
    Ui::LayoutDia *ui;
    QList<ControlWin *> playViews;
    ControlWin *getView(uint num);
    void setPlayScreenLayout(ChildState state, int start);
    ChildState m_currentState;
    int m_layoutStart;
};

#endif // LAYOUTDIA_H
