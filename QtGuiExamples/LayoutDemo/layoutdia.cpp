#include "layoutdia.h"
#include "ui_layoutdia.h"
#include <QDebug>

LayoutDia::LayoutDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayoutDia)
{
    ui->setupUi(this);

    for (int i = 0; i < 25; i++){
        playViews.append(NULL);
    }

    m_currentState = NoLayout;
    setPlayScreenLayout(Number_10,0);

    ui->comboBox->addItem("1", 1);
    ui->comboBox->addItem("4", 2);
    ui->comboBox->addItem("6", 3);
    ui->comboBox->addItem("8", 4);
    ui->comboBox->addItem("9", 5);

    ui->comboBox->addItem("10", 6);
    ui->comboBox->addItem("10_2", 7);
    ui->comboBox->addItem("13", 8);
    ui->comboBox->addItem("13_2", 9);
    ui->comboBox->addItem("14", 10);

    ui->comboBox->addItem("16", 11);
    ui->comboBox->addItem("17", 12);
    ui->comboBox->addItem("19", 13);
    ui->comboBox->addItem("22", 14);
    ui->comboBox->addItem("25", 15);

    ui->comboBox->setCurrentIndex(5);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxCurrentIndexChanged(int)));
}

LayoutDia::~LayoutDia()
{
    delete ui;
}

void LayoutDia::onComboBoxCurrentIndexChanged(int item)
{
    //qDebug()<<item; //0 - 14
    switch(item)
    {
        case 0:{
            setPlayScreenLayout(JustOne,0);
            break;
        }
        case 1:{
            setPlayScreenLayout(Number_4,0);
            break;
        }
        case 2:{
            setPlayScreenLayout(Number_6,0);
            break;
        }
        case 3:{
            setPlayScreenLayout(Number_8,0);
            break;
        }
        case 4:{
            setPlayScreenLayout(Number_9,0);
            break;
        }
        case 5:{
            setPlayScreenLayout(Number_10,0);
            break;
        }
        case 6:{
            setPlayScreenLayout(Number_10_2,0);
            break;
        }
        case 7:{
            setPlayScreenLayout(Number_13,0);
            break;
        }
        case 8:{
            setPlayScreenLayout(Number_13_2,0);
            break;
        }
        case 9:{
            setPlayScreenLayout(Number_14,0);
            break;
        }
        case 10:{
            setPlayScreenLayout(Number_16,0);
            break;
        }
        case 11:{
            setPlayScreenLayout(Number_17,0);
            break;
        }
        case 12:{
            setPlayScreenLayout(Number_19,0);
            break;
        }
        case 13:{
            setPlayScreenLayout(Number_22,0);
            break;
        }
        default:{
            setPlayScreenLayout(Number_25,0);
            break;
        }
    }
}

ControlWin *LayoutDia::getView(uint num)
{
    if (playViews[num] == NULL)
    {
        ControlWin *newView = new ControlWin;
        newView->setStyleSheet("QFrame{ border: 1px solid #0000CD;}"); //蓝色
        playViews[num] = newView;
        return newView;
    }
    return playViews[num];
}

void LayoutDia::setPlayScreenLayout(ChildState state, int start)
{
    int newSize = 0;
    int oldSize = 0;
    int totalCount = playViews.count();

    if(m_currentState != 0)
    {
        QLayout *oldlayout = ui->frame->layout();
        oldSize = oldlayout->count();
        for(uint i = 0; i < oldSize; i ++)
        {
            getView((m_layoutStart + i) % totalCount)->setVisible(false);
        }
        delete oldlayout;
        oldlayout=NULL;
    }

    QGridLayout *newLayout = new QGridLayout();
    newLayout->setContentsMargins(1, 1, 1, 1);
    newLayout->setSpacing(0);

    switch(state)
    {
           case JustOne:
           {
               newLayout->addWidget(getView(start % totalCount));
               newSize = 1;
               break;
           }
           case Number_4:
           {
               newLayout->addWidget(getView(start), 0, 0);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 1);
               newLayout->addWidget(getView((start + 2) % totalCount), 1, 0);
               newLayout->addWidget(getView((start + 3) % totalCount), 1, 1);
               newSize = 4;
               break;
           }
           case Number_6:
           {
               newLayout->addWidget(getView(start), 0, 0, 2, 2);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 2);
               newLayout->addWidget(getView((start + 2) % totalCount), 1, 2);
               newLayout->addWidget(getView((start + 3) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 4) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 5) % totalCount), 2, 2);
               newSize = 6;
               break;
           }
           case Number_9:
           {
               newLayout->addWidget(getView(start), 0, 0);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 1);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 2);
               newLayout->addWidget(getView((start + 3) % totalCount), 1, 0);
               newLayout->addWidget(getView((start + 4) % totalCount), 1, 1);
               newLayout->addWidget(getView((start + 5) % totalCount), 1, 2);
               newLayout->addWidget(getView((start + 6) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 7) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 8) % totalCount), 2, 2);
               newSize = 9;
               break;
           }
           case Number_8:
           {
               newLayout->addWidget(getView(start), 0, 0, 3, 3);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 3);
               newLayout->addWidget(getView((start + 2) % totalCount), 1, 3);
               newLayout->addWidget(getView((start + 3) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 4) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 5) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 6) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 7) % totalCount), 3, 3);
               newSize = 8;
               break;
           }
           case Number_10:
           {
               newLayout->addWidget(getView(start), 0, 0, 2, 2);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 2, 2, 2);
               newLayout->addWidget(getView((start + 2) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 3) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 4) % totalCount), 2, 2);
               newLayout->addWidget(getView((start + 5) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 6) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 7) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 8) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 9) % totalCount), 3, 3);
               newSize = 10;
               break;
           }
           case Number_13:
           {
               newLayout->addWidget(getView(start), 0, 0);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 1);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 2);
               newLayout->addWidget(getView((start + 3) % totalCount), 0, 3);
               newLayout->addWidget(getView((start + 4) % totalCount), 1, 0);
               newLayout->addWidget(getView((start + 5) % totalCount), 1, 1, 2, 2);
               newLayout->addWidget(getView((start + 6) % totalCount), 1, 3);
               newLayout->addWidget(getView((start + 7) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 8) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 9) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 10) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 11) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 12) % totalCount), 3, 3);
               newSize = 13;
               break;
           }
           case Number_16:
           {
               newLayout->addWidget(getView(start), 0, 0);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 1);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 2);
               newLayout->addWidget(getView((start + 3) % totalCount), 0, 3);
               newLayout->addWidget(getView((start + 4) % totalCount), 1, 0);
               newLayout->addWidget(getView((start + 5) % totalCount), 1, 1);
               newLayout->addWidget(getView((start + 6) % totalCount), 1, 2);
               newLayout->addWidget(getView((start + 7) % totalCount), 1, 3);
               newLayout->addWidget(getView((start + 8) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 9) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 10) % totalCount), 2, 2);
               newLayout->addWidget(getView((start + 11) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 12) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 13) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 14) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 15) % totalCount), 3, 3);
               newSize = 16;
               break;
           }
           case Number_10_2:
           {
               newLayout->addWidget(getView(start), 0, 0, 4, 4);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 4);
               newLayout->addWidget(getView((start + 2) % totalCount), 1, 4);
               newLayout->addWidget(getView((start + 3) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 4) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 5) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 6) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 7) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 8) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 9) % totalCount), 4, 4);
               newSize = 10;
               break;
           }
           case Number_13_2:
           {
               newLayout->addWidget(getView(start), 0, 0, 2, 2);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 2, 2, 2);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 4);
               newLayout->addWidget(getView((start + 3) % totalCount), 1, 4);
               newLayout->addWidget(getView((start + 4) % totalCount), 2, 0, 2, 2);
               newLayout->addWidget(getView((start + 5) % totalCount), 2, 2, 2, 2);
               newLayout->addWidget(getView((start + 6) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 7) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 8) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 9) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 10) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 11) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 12) % totalCount), 4, 4);
               newSize = 13;
               break;
           }
           case Number_14:
           {
               newLayout->addWidget(getView(start), 0, 0, 3, 3);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 3, 2, 2);
               newLayout->addWidget(getView((start + 2) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 3) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 4) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 5) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 6) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 7) % totalCount), 3, 3);
               newLayout->addWidget(getView((start + 8) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 9) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 10) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 11) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 12) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 13) % totalCount), 4, 4);
               newSize = 14;
               break;
           }
           case Number_17:
           {
               newLayout->addWidget(getView(start), 0, 0, 3, 3);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 3);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 4);
               newLayout->addWidget(getView((start + 3) % totalCount), 1, 3);
               newLayout->addWidget(getView((start + 4) % totalCount), 1, 4);
               newLayout->addWidget(getView((start + 5) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 6) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 7) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 8) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 9) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 10) % totalCount), 3, 3);
               newLayout->addWidget(getView((start + 11) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 12) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 13) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 14) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 15) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 16) % totalCount), 4, 4);
               newSize = 17;
               break;
           }
           case Number_19:
           {
               newLayout->addWidget(getView(start), 0, 0, 2, 2);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 2, 2, 2);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 4);
               newLayout->addWidget(getView((start + 3) % totalCount), 1, 4);
               newLayout->addWidget(getView((start + 4) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 5) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 6) % totalCount), 2, 2);
               newLayout->addWidget(getView((start + 7) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 8) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 9) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 10) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 11) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 12) % totalCount), 3, 3);
               newLayout->addWidget(getView((start + 13) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 14) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 15) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 16) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 17) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 18) % totalCount), 4, 4);
               newSize = 19;
               break;
           }
           case Number_22:
           {
               newLayout->addWidget(getView(start), 0, 0, 2, 2);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 2);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 3);
               newLayout->addWidget(getView((start + 3) % totalCount), 0, 4);
               newLayout->addWidget(getView((start + 4) % totalCount), 1, 2);
               newLayout->addWidget(getView((start + 5) % totalCount), 1, 3);
               newLayout->addWidget(getView((start + 6) % totalCount), 1, 4);
               newLayout->addWidget(getView((start + 7) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 8) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 9) % totalCount), 2, 2);
               newLayout->addWidget(getView((start + 10) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 11) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 12) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 13) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 14) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 15) % totalCount), 3, 3);
               newLayout->addWidget(getView((start + 16) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 17) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 18) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 19) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 20) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 21) % totalCount), 4, 4);
               newSize = 22;
               break;
           }
           default:
           {
               newLayout->addWidget(getView(start), 0, 0);
               newLayout->addWidget(getView((start + 1) % totalCount), 0, 1);
               newLayout->addWidget(getView((start + 2) % totalCount), 0, 2);
               newLayout->addWidget(getView((start + 3) % totalCount), 0, 3);
               newLayout->addWidget(getView((start + 4) % totalCount), 0, 4);
               newLayout->addWidget(getView((start + 5) % totalCount), 1, 0);
               newLayout->addWidget(getView((start + 6) % totalCount), 1, 1);
               newLayout->addWidget(getView((start + 7) % totalCount), 1, 2);
               newLayout->addWidget(getView((start + 8) % totalCount), 1, 3);
               newLayout->addWidget(getView((start + 9) % totalCount), 1, 4);
               newLayout->addWidget(getView((start + 10) % totalCount), 2, 0);
               newLayout->addWidget(getView((start + 11) % totalCount), 2, 1);
               newLayout->addWidget(getView((start + 12) % totalCount), 2, 2);
               newLayout->addWidget(getView((start + 13) % totalCount), 2, 3);
               newLayout->addWidget(getView((start + 14) % totalCount), 2, 4);
               newLayout->addWidget(getView((start + 15) % totalCount), 3, 0);
               newLayout->addWidget(getView((start + 16) % totalCount), 3, 1);
               newLayout->addWidget(getView((start + 17) % totalCount), 3, 2);
               newLayout->addWidget(getView((start + 18) % totalCount), 3, 3);
               newLayout->addWidget(getView((start + 19) % totalCount), 3, 4);
               newLayout->addWidget(getView((start + 20) % totalCount), 4, 0);
               newLayout->addWidget(getView((start + 21) % totalCount), 4, 1);
               newLayout->addWidget(getView((start + 22) % totalCount), 4, 2);
               newLayout->addWidget(getView((start + 23) % totalCount), 4, 3);
               newLayout->addWidget(getView((start + 24) % totalCount), 4, 4);
               newSize = 25;
               break;
           }
       }

    for (uint i = 0; i < newSize; i++)
    {
        getView((start + i) % totalCount)->setVisible(true);
    }

    ui->frame->setLayout(newLayout);

    m_layoutStart = start;
    m_currentState = state;

    qDebug()<< "----------- layout over ..............";
}
