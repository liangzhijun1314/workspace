#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui>
#include <QObject>
#include <QTextEdit>

class SwitchControl;
class MainWindow : public QMainWindow
{
    Q_OBJECT    //比C++ 预处理器更早执行的预处理器 不仅仅是宏展开这么简单 moc 只处理头文件中的标记了Q_OBJECT的类声明

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readSettings(); // 读取配置文件
    void writeSettings(); // 保存配置文件

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void onToggled(bool bChecked);

private:
    bool readFile(const QString &fileName);
    QTextEdit *textEdit;
};
#endif // MAINWINDOW_H
