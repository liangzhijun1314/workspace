#include "mainwindow.h"
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QDateTime>
#include <QCoreApplication>

#include "SwitchControl.h"
#include "newspaper.h"
#include "reader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
// 文件拖拽的方式显示内容
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    textEdit->setAcceptDrops(false);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);//如果你必须在堆上创建对象，不妨增加一句：
    setAcceptDrops(true);

    setWindowTitle(tr("Text Editor"));

//  记录并显示上次窗口关闭时的geometry或者几何形状
    QCoreApplication::setOrganizationName("TEST_Org_NAME");
    QCoreApplication::setApplicationName("TEST_APP_NAME");
    readSettings();

//实现启动界面 目的加个延时
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
        QCoreApplication::processEvents();
    } while (n.secsTo(now)<=2);//2为需要延时的秒数

// 自定义 开关  start

    SwitchControl *pSwitchControl = new SwitchControl(this);
    SwitchControl *pGreenSwitchControl = new SwitchControl(this);
    SwitchControl *pDisabledSwitchControl = new SwitchControl(this);

    pSwitchControl->setGeometry(QRect(QPoint(100, 100),QSize(200, 50)));
    pGreenSwitchControl->setGeometry(QRect(QPoint(100, 200),QSize(200, 50)));
    pDisabledSwitchControl->setGeometry(QRect(QPoint(100, 300),QSize(200, 50)));

    // 设置状态、样式
    pGreenSwitchControl->setToggle(true);
    pGreenSwitchControl->setCheckedColor(QColor(0, 160, 230));
    pDisabledSwitchControl->setDisabled(true);
    pDisabledSwitchControl->setToggle(true);

    // 连接信号槽
    connect(pSwitchControl, SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));

    QVBoxLayout  * vLayout = new QVBoxLayout();
    vLayout->addWidget(pSwitchControl);
    vLayout->addWidget(pGreenSwitchControl);
    vLayout->addWidget(pDisabledSwitchControl);
    // 自定义 开关  end


//自定义信号槽
    Newspaper newSpaper("New spaper A");
    Reader reader;
    QObject::connect(&newSpaper, SIGNAL(newPaper(QString)),
                     &reader,    SLOT(receiveNewspaper(QString)));
    newSpaper.send();
    //自定义信号槽 end


    QObject::dumpObjectTree();
//    QObject::dumpObjectInfo();
}

MainWindow::~MainWindow()
{
}

void MainWindow::readSettings()
{
    //  恢复geometry()
    qDebug()<<"QCoreApplication::organizationName() = "<<QCoreApplication::organizationName();
    qDebug()<<"QCoreApplication::applicationName() = "<<QCoreApplication::applicationName();
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    //  恢复几何形状
//    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
//    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
//    if (geometry.isEmpty()) {
//        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
//        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
//        move((availableGeometry.width() - width()) / 2,
//             (availableGeometry.height() - height()) / 2);
//    } else {
//        restoreGeometry(geometry);
//    }
}

void MainWindow::writeSettings()
{
    //  保存 geometry()
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());

    //  保存几何形状
//    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
//    settings.setValue("geometry", saveGeometry());
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }

    if (readFile(fileName)) {
        setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::onToggled(bool bChecked)
{
    qDebug() << "State : " << bChecked;
}

bool MainWindow::readFile(const QString &fileName)
{
    bool r = false;
    QFile file(fileName);
    //判断文件是否存在
    if(file.exists()){
    }else{
        qDebug()<<"文件不存在";
        return r;
    }
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text)) {
        return r;
    } else {
        textEdit->clear();
    }

    QTextStream in(&file);
    QString lineStr;
    while(!in.atEnd())
    {
        lineStr = in.readLine();
        in << lineStr << endl;
        textEdit->append(lineStr);
    }
    r = true;

    file.close();
    return r;
}
