#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QDomElement>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool readFile(const QString &fileName);
private:
    void parseBookindexElement(const QDomElement &element);
    void parseEntryElement(const QDomElement &element, QTreeWidgetItem *parent);
    void parsePageElement(const QDomElement &element, QTreeWidgetItem *parent);
private:
    QTreeWidget *treeWidget;
};

#endif // MAINWINDOW_H
