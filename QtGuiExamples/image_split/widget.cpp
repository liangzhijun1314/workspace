#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    setFixedSize(300, 200);
    level_button = new QPushButton();
    grade_button = new QPushButton();
    
    //分别获取0-9数字图标
    QPixmap pixmap_0 = getPixmap(QString(":/level/level_value.jpg"), 10, 0);
    QPixmap pixmap_1 = getPixmap(QString(":/level/level_value.jpg"), 10, 1);
    QPixmap pixmap_2 = getPixmap(QString(":/level/level_value.jpg"), 10, 2);
    QPixmap pixmap_3 = getPixmap(QString(":/level/level_value.jpg"), 10, 3);
    QPixmap pixmap_4 = getPixmap(QString(":/level/level_value.jpg"), 10, 4);
    QPixmap pixmap_5 = getPixmap(QString(":/level/level_value.jpg"), 10, 5);
    QPixmap pixmap_6 = getPixmap(QString(":/level/level_value.jpg"), 10, 6);
    QPixmap pixmap_7 = getPixmap(QString(":/level/level_value.jpg"), 10, 7);
    QPixmap pixmap_8 = getPixmap(QString(":/level/level_value.jpg"), 10, 8);
    QPixmap pixmap_9 = getPixmap(QString(":/level/level_value.jpg"), 10, 9);
    
    int count = 3;
    int pixmap_width = pixmap_8.width();
    int pixmap_height = pixmap_8.height();
    
    //最前面LV图标
    QPixmap pixmap_lv(":/level/lv.jpg");
    int lv_width = pixmap_lv.width();
    QPixmap total_pixmap(QSize(pixmap_width*count + lv_width, pixmap_height));
    QPainter painter(&total_pixmap);
    
    //绘制LV图标
    painter.drawPixmap(QRect(0, 0, lv_width, pixmap_height), pixmap_lv);
    
    //再绘制LV888图标
    for(int i=0; i<3;i++)
    {
        painter.drawPixmap(QRect(lv_width+pixmap_width*i, 0, pixmap_width, pixmap_height), pixmap_8);
    }
    
    level_button->setFixedHeight(30);
    level_button->setIcon(total_pixmap);
    level_button->setIconSize(total_pixmap.size());
    
    //分别获取皇冠、太阳、月亮、星星、...等图标
    QPixmap pixmap_grade_0 = getPixmap(QString(":/level/grade.jpg"), 5, 0);
    QPixmap pixmap_grade_1 = getPixmap(QString(":/level/grade.jpg"), 5, 1);
    QPixmap pixmap_grade_2 = getPixmap(QString(":/level/grade.jpg"), 5, 2);
    QPixmap pixmap_grade_3 = getPixmap(QString(":/level/grade.jpg"), 5, 3);
    QPixmap pixmap_grade_4 = getPixmap(QString(":/level/grade.jpg"), 5, 4);
    
    //绘制5个皇冠
    int grade_count = 5;
    int pixmap_grade_width = pixmap_grade_0.width();
    int pixmap_grade_height = pixmap_grade_0.height();
    QPixmap total_grade_pixmap(QSize(pixmap_grade_width*grade_count, pixmap_grade_height));
    QPainter grade_painter(&total_grade_pixmap);
    for(int i=0; i<grade_count;i++)
    {
        grade_painter.drawPixmap(QRect(pixmap_grade_width*i, 0, pixmap_grade_width, pixmap_grade_height), pixmap_grade_0);
    }
    grade_button->setFixedHeight(30);
    grade_button->setIcon(total_grade_pixmap);
    grade_button->setIconSize(total_grade_pixmap.size());

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addStretch();
    main_layout->addWidget(level_button);
    main_layout->addWidget(grade_button);
    main_layout->addStretch();
    main_layout->setSpacing(20);
    main_layout->setContentsMargins(0, 0, 0, 0);
    
    setLayout(main_layout);
    
}


QPixmap Widget::getPixmap(QString pixmap_name, int count, int index)
{
    QPixmap final_pixmap;
    if(!pixmap_name.isEmpty() && count > 0)
    {
        QPixmap pixmap(pixmap_name);
        int pixmap_width = pixmap.width()/count;
        int pixmap_height = pixmap.height();
        final_pixmap = pixmap.copy(pixmap_width*index, 0, pixmap_width, pixmap_height);
    }
    
    return final_pixmap;
}  
