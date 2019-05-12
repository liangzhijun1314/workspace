#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QDebug>
#include "StandardItemModelEx.h"

#define ROLE_MARK Qt::UserRole + 1
#define ROLE_MARK_FOLDER Qt::UserRole + 2
#define ROLE_MARK_ITEM Qt::UserRole + 2

//对应ROLE_MARK
#define MARK_PROJECT 1
#define MARK_FOLDER 2
#define MARK_ITEM 3

//对应ROLE_MARK_FOLDER，标记folder种类
#define MARK_FOLDER_H 1
#define MARK_FOLDER_CPP 2

//对应ROLE_MARK_ITEM标记item种类
#define MARK_ITEM_H 1
#define MARK_ITEM_CPP 2
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
    initMenu();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QString::fromLocal8Bit("项目"));

    //添加项目文件夹
    QStandardItem* root = new QStandardItem(QIcon(":/icon/icon/p.png"),QString::fromLocal8Bit("项目"));
    root->setData(MARK_PROJECT,ROLE_MARK);//首先它是项目中目录
    root->setData(MARK_FOLDER,ROLE_MARK_FOLDER);//其次它属于文件夹
    root->setData(
                QString::fromLocal8Bit("这是关于QStandardItemModel设定角色的教程\n详细介绍见：http://blog.csdn.net/czyt1988/article/details/26018513")
                ,Qt::ToolTipRole
                );
    root->setData(
                QColor(255,0,0)
                ,Qt::TextColorRole
                );
    model->appendRow(root);
    QStandardItem* folder = new QStandardItem(QIcon(":/icon/icon/h-f.png"),QString::fromLocal8Bit("头文件"));
    folder->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
    folder->setData(MARK_FOLDER_H,ROLE_MARK_FOLDER);//其次它属于头文件文件夹
    root->appendRow(folder);
    folder = new QStandardItem(QIcon(":/icon/icon/c-f.png"),QString::fromLocal8Bit("源文件"));
    folder->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
    folder->setData(MARK_FOLDER_CPP,ROLE_MARK_FOLDER);//其次它属于源文件文件夹
    root->appendRow(folder);
    ui->treeView->setModel(model);
}

void Widget::initMenu()
{
    m_projectMenu = new QMenu(this);
    m_itemMenu = new QMenu(this);

    QAction* ac = NULL;
    ac = new QAction(QString::fromLocal8Bit("构建"),this);
    m_projectMenu->addAction(ac);

    ac = new QAction(QString::fromLocal8Bit("执行qmake"),this);
    m_projectMenu->addAction(ac);

    ac = new QAction(QString::fromLocal8Bit("部署"),this);
    ac->setEnabled(false);
    m_projectMenu->addAction(ac);

    ac = new QAction(QString::fromLocal8Bit("运行"),this);
    m_projectMenu->addAction(ac);

    m_projectMenu->addSeparator();

    ac = new QAction(QString::fromLocal8Bit("重新构建"),this);
    m_projectMenu->addAction(ac);

    ac = new QAction(QString::fromLocal8Bit("清除"),this);
    m_projectMenu->addAction(ac);

    m_projectMenu->addSeparator();

    ac = new QAction(QString::fromLocal8Bit("添加新文件……"),this);
    m_projectMenu->addAction(ac);

    ac = new QAction(QString::fromLocal8Bit("余下的省略……"),this);
    m_projectMenu->addAction(ac);

    //

    ac = new QAction(QString::fromLocal8Bit("打开文件"),this);
    m_itemMenu->addAction(ac);
    ac = new QAction(QString::fromLocal8Bit("在explorer中显示"),this);
    m_itemMenu->addAction(ac);
    ac = new QAction(QString::fromLocal8Bit("在此弹出命令提示"),this);
    m_itemMenu->addAction(ac);

    QMenu* itemChildMenu = new QMenu(m_itemMenu);
    itemChildMenu->setTitle(QString::fromLocal8Bit("用…打开"));
    ac = new QAction(QString::fromLocal8Bit("C++编辑器"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString::fromLocal8Bit("普通文本编辑器"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString::fromLocal8Bit("二进制编辑器"),this);
    itemChildMenu->addAction(ac);
    ac = new QAction(QString("System Editor"),this);
    itemChildMenu->addAction(ac);

    m_itemMenu->addAction(itemChildMenu->menuAction());

    ac = new QAction(QString::fromLocal8Bit("余下省略n条"),this);
    m_itemMenu->addAction(ac);
}

QStandardItemModel* Widget::getTreeModel()
{
    return qobject_cast<QStandardItemModel*>(ui->treeView->model());
}

QStandardItem* Widget::getHeaderFolder()
{
    QStandardItem* project = getProjectFolder();
    if(NULL == project)
        return NULL;

    qDebug()<<"project->rowCount() = "<<project->rowCount();
    for(int i=0;i < project->rowCount();++i)
    {
        QStandardItem* child = project->child(i);
        QVariant var = child->data(ROLE_MARK_FOLDER);
        if(!var.isValid())
            continue;//说明不是ROLE_MARK_FOLDER，有可能是一些项目，对应项目结构树那个xxx.pro就是一个非文件夹条目
        if(MARK_FOLDER_H == var.value<int>())
            return child;
    }
    return NULL;
}

QStandardItem* Widget::getSrcFolder()
{
    QStandardItem* project = getProjectFolder();
    if(NULL == project)
        return NULL;
    for(int i=0;i < project->rowCount();++i)
    {
        QStandardItem* child = project->child(i);
        QVariant var = child->data(ROLE_MARK_FOLDER);
        if(!var.isValid())
            continue;//说明不是ROLE_MARK_FOLDER，有可能是一些项目，对应项目结构树那个xxx.pro就是一个非文件夹条目
        if(MARK_FOLDER_CPP == var.value<int>())
            return child;
    }
    return NULL;
}

QList<QStandardItem*> Widget::getRoots()
{
    QList<QStandardItem*> roots;
    QStandardItemModel* model = getTreeModel();
    for(int i=0;i < model->rowCount();++i)
    {
        roots.append(model->item(i));
    }
    return roots;
}

QStandardItem* Widget::getProjectFolder()
{
    QList<QStandardItem*> roots = getRoots();
    qDebug()<<"roots count = "<<roots.count();
    for(QList<QStandardItem*>::iterator  i=roots.begin();i!=roots.end();++i){
        if((*i)->data(ROLE_MARK) == MARK_PROJECT){
            return (*i);
        }
    }
    return NULL;
}

void Widget::on_pushButton_clicked()
{
    static int s_header_count = 1;
    //找到头文件文件夹
    QStandardItem* headerFolder = getHeaderFolder();
    /*
    QModelIndexList ls = getTreeModel()->match(
                getRoots().value(0)->index()
                ,ROLE_MARK_FOLDER
                ,MARK_FOLDER_H
                );
    if(ls.size() == 0)
    {
        qDebug()<<"no match";
        return;
    }
    QStandardItem* headerFolder = getTreeModel()->itemFromIndex(ls.value(0));
    */
    if(headerFolder)
    {
        QStandardItem* item = new QStandardItem(QIcon(":/icon/icon/i.png")
                                                ,QString("%1.h").arg(s_header_count));
        item->setData(MARK_ITEM,ROLE_MARK);//首先标定条目的类型 - 文件夹、项目、条目…
        item->setData(MARK_ITEM_H,ROLE_MARK_ITEM);//再次标定项目的类型
        headerFolder->appendRow(item);
        ++s_header_count;
    }
}

void Widget::on_pushButton_2_clicked()
{
    static int s_cpp_count = 1;
    //找到头文件文件夹
    QStandardItem* cppFolder = getSrcFolder();
    if(cppFolder)
    {
        QStandardItem* item = new QStandardItem(QIcon(":/icon/icon/i.png")
                                                ,QString("%1.cpp").arg(s_cpp_count));
        item->setData(MARK_ITEM,ROLE_MARK);//首先标定条目的类型 - 文件夹、项目、条目…
        item->setData(MARK_ITEM_H,ROLE_MARK_ITEM);//再次标定项目的类型
        cppFolder->appendRow(item);
        ++s_cpp_count;
    }
}

void Widget::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    QVariant var = index.data(ROLE_MARK);
    if(var.isValid())
    {
        if(MARK_PROJECT == var.toInt())
            m_projectMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
        else if(MARK_ITEM == var.toInt())
            m_itemMenu->exec(QCursor::pos());
    }
}

void Widget::on_pushButton_3_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid())
        return;
    getTreeModel()->itemFromIndex(index)->setData(QColor(232,209,57,200),Qt::BackgroundRole);
}

void Widget::on_pushButton_4_clicked()
{
    //涉及到遍历，因此使用回调函数，把遍历需要执行的函数传给封装好的遍历
//    StandardItemModelEx::ergodicAllItem(getTreeModel()
//                                        ,std::bind(&Widget::callback_clearColor,this,std::placeholders::_1));


    StandardItemModelEx::ergodicAllItem(getTreeModel());
}

void Widget::callback_clearColor(QStandardItem* item)
{
    item->setData(QVariant(),Qt::BackgroundRole);
}
