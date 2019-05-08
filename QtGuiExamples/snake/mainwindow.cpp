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

    //���������Ƿ���ʹ�ã�������дtimerEvent()���������Ǵ���һ���ֲ���QTimer����
    //��˼�ǣ�����һ���¼�ѭ����ʼʱ�����̵���ָ���Ĳۺ���
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}
//���ó����ķ�Χ�������Ͻ��� (-100, -100)�����Ϳ��� 200px �ľ���,ʵ���������˳���������ϵ
void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}
//��Ϊ������ˢ������������ͼ
void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);   // ����һ���߳�TILE_SIZE��QPixmap
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));       // ����ʹ�û�ɫ������
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));//��Ϊ������ˢ������������ͼ
}
