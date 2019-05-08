#include <QtWidgets>
#include "mainwindow.h"
//#include <QDomElement>
#include <QDomDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString::fromLocal8Bit("DOM 处理Xml"));
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
        QMessageBox::critical(this, tr("Error"),
                              tr("Cannot read file %1").arg(fileName));
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    //使用其setContent()函数填充 DOM 树
    if (!doc.setContent(&file, false, &errorStr, &errorLine,
                        &errorColumn)) {
        QMessageBox::critical(this, tr("Error"),
                              tr("Parse error at line %1, column %2: %3")
                              .arg(errorLine).arg(errorColumn).arg(errorStr));
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "bookindex") {
        QMessageBox::critical(this, tr("Error"),
                              tr("Not a bookindex file"));
        return false;
    }

    parseBookindexElement(root);
    return true;
}

void MainWindow::parseBookindexElement(const QDomElement &element)
{
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "entry") {
            parseEntryElement(child.toElement(),treeWidget->invisibleRootItem());
        }
        child = child.nextSibling();
    }
}

void MainWindow::parseEntryElement(const QDomElement &element, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(0, element.attribute("term"));

    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "entry") {
            parseEntryElement(child.toElement(), item);
        } else if (child.toElement().tagName() == "page") {
            parsePageElement(child.toElement(), item);
        }
        child = child.nextSibling();
    }
}

void MainWindow::parsePageElement(const QDomElement &element, QTreeWidgetItem *parent)
{
    QString page = element.text();
    QString allPages = parent->text(1);
    if (!allPages.isEmpty()) {
        allPages += ", ";
    }
    allPages += page;
    parent->setText(1, allPages);
}
