#include <QGraphicsView>
#include <QTimer>

#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this))
{
    setCentralWidget(view);
    resize(600, 600);

    initScene();
    initSceneBackground();

    //它的作用是方便使用，无需重写timerEvent()函数或者是创建一个局部的QTimer对象
    //意思是，在下一次事件循环开始时，立刻调用指定的槽函数
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}
//设置场景的范围，是左上角在 (-100, -100)，长和宽都是 200px 的矩形,实际是设置了场景的坐标系
void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}
//作为背景画刷，铺满整个视图
void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);   // 创建一个边长TILE_SIZE的QPixmap
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));       // 将其使用灰色填充矩形
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));//作为背景画刷，铺满整个视图
}
