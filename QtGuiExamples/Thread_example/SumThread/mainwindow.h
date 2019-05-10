#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Thread;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_sumBtn_clicked();

    void on_showBtn_clicked();

    void displayResult(long);

private:
    Ui::MainWindow *ui;
    Thread *thread;
};

#endif // MAINWINDOW_H
