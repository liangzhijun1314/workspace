#include <QtWidgets>
#include "mainwindow.h"
//#include <QTreeWidget>
//#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);//Qt设置无边框自定义菜单
    setWindowTitle(QString::fromLocal8Bit("流处理Xml"));
    treeWidget = new QTreeWidget(this);
    QStringList headers;
    headers << "Item" << "Pages";

    treeWidget->setHeaderLabels(headers);
    this->setCentralWidget(treeWidget);
}

MainWindow::~MainWindow()
{

}

bool MainWindow::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("不能读取文件%1").arg(fileName));
        return false;
    }
    reader.setDevice(&file);  //将其设置为QXmlStreamReader的设备
    while (!reader.atEnd()) {   //只要没读到文件末尾，就要一直循环处理
        if (reader.isStartElement()) {  //判断是不是StartElement
            qDebug() << "reader name = " << reader.name();
            if(reader.name() == "bookindex") {
                readBookindexElement();
            } else {
                reader.raiseError(QString::fromLocal8Bit("不是一个有效的Xml文件"));
            }
        } else {
            reader.readNext();
        }
    }
    file.close();

    if (reader.hasError()) {
        QMessageBox::critical(this,QString::fromLocal8Bit("错误"),
                              QString::fromLocal8Bit("解析xml文件：%1失败。").arg(fileName));
        return false;
    } else if (file.error() != QFile::NoError) {
        QMessageBox::critical(this,QString::fromLocal8Bit("错误"),
                              QString::fromLocal8Bit("xml文件：%1不可读。").arg(fileName));
        return false;
    }

    return true;
}

void MainWindow::readBookindexElement()
{
    //进入函数的时候，reader 不是StartElement状态，或者说标签不是 bookindex，就认为出错
    Q_ASSERT(reader.isStartElement() && (reader.name() == "bookindex")); //加了一个断言

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            if (reader.name() == "entry") {
                readEntryElement(treeWidget->invisibleRootItem());
            } else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MainWindow::readEntryElement(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(0,reader.attributes().value("term").toString()); // 设置根节点
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }
        if (reader.isStartElement()) {
            if (reader.name() == "entry") {
                readEntryElement(item);
            } else if (reader.name() == "page") {
                readPageElement(item);
            } else {
                skipUnknownElement();
            }
        } else {
            reader.readNext();
        }
    }
}

void MainWindow::readPageElement(QTreeWidgetItem *parent)
{
    QString page = reader.readElementText();
    if (reader.isEndElement()) {
        reader.readNext();
    }

    QString allPages = parent->text(1);
    if (!allPages.isEmpty()) {
        allPages += ", ";
    }
    allPages += page;
    parent->setText(1,allPages);
}

void MainWindow::skipUnknownElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            skipUnknownElement();
        } else {
            reader.readNext();
        }
    }
}
