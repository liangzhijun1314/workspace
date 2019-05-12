#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QList>
#include <QMenu>
#include <QAction>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    void init();
    void initMenu();
    QStandardItemModel* getTreeModel();
    QStandardItem* getHeaderFolder();
    QStandardItem* getSrcFolder();
    QList<QStandardItem*> getRoots();
    QStandardItem* getProjectFolder();
    void callback_clearColor(QStandardItem* item);
private:
    Ui::Widget *ui;
    QMenu* m_projectMenu;
    QMenu* m_itemMenu;

};

#endif // WIDGET_H
