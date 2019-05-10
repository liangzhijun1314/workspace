#include "ccheckcombox.h"
#include "widget.h"

CCheckCombox::CCheckCombox(QWidget *parent) :
    QComboBox(parent)
{

}

void CCheckCombox::appendItem(const QString &text, bool bChecked)
{
    QIcon icon;
    if( bChecked )
    {
        icon.addFile(":/Image/check.png");
    }
    else
    {
        icon.addFile(":/Image/uncheck.png");
    }

    addItem(icon, text, bChecked);
}

void CCheckCombox::updateIndexStatus(int index)
{
    bool bChecked = this->itemData(index).toBool();

    if( bChecked )
    {
        this->setItemIcon(index, QIcon(":/Image/uncheck.png"));
    }
    else
    {
        this->setItemIcon(index, QIcon(":/Image/check.png"));
    }

    setItemData(index, !bChecked);

    emit checkedStateChange(index, !bChecked);
}

void CCheckCombox::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();

    int iconWidth = this->iconSize().width();

    if( x <= iconWidth )
    {
        int index = this->currentIndex();

        updateIndexStatus(index);
    }
    else
    {
        QComboBox::mousePressEvent(event);
    }
}

void CCheckCombox::hidePopup()
{
    int iconWidth = this->iconSize().width();

    int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();

    int index = view()->selectionModel()->currentIndex().row();

    if( x >= 0 && x <= iconWidth )
    {
        updateIndexStatus(index);
    }
    else
    {
        QComboBox::hidePopup();
    }
}
