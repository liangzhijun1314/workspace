#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportexcelobject.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);

    myModel = new MyTestModel;
    ui->tableView->setModel(myModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    myModel->setMyData(400);
}

void MainWindow::on_pushButton_4_clicked()
{
    myModel->setMyData(4000);
}

void MainWindow::on_pushButton_5_clicked()
{
    myModel->setMyData(40000);
}

void MainWindow::on_pushButton_7_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableView);

    // you can change the column order and
    // choose which colum to export
    //obj.addField(0, "colum1", "char(20)");
    obj.addField(3, "colum4", "char(20)");
    obj.addField(1, "colum2", "char(20)");
    obj.addField(2, "colum3", "char(20)");

    obj.addField(4, "colum5", "char(20)");
    obj.addField(5, "colum6", "char(20)");
    //obj.addField(6, "colum7", "char(20)");

    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(ui->tableView->model()->rowCount());

    connect(&obj, SIGNAL(exportedRowCount(int)), ui->progressBar, SLOT(setValue(int)));

    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
