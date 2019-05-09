/*******************************************************************************
** @file:     mainwindow.h
** @class:    MainWindow
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-4-9
** @version:
** -------------File modification record-------------
** @modify date:    // Modification time
** @editor:         // Modifier
** @content:		// Modify content
*******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTextDocument>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void getConnect();
    void execCommand(const char *command, int length, const char *add, int clientCode);
    void ShowText(const char *text);
signals:
    void writeFile(int clientCode);
public:
    QTextDocument *textDocument;
    Server *server;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
