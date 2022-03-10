#include "widget.h"
#include "ui_widget.h"
#include "my_button.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QSignalMapper>
#include <QPushButton>
#include "my_stack.h"
#include <QTimer>
#include "timetable.h"
#include "sudokugame.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    p_timer(new QTimer(this)),
    min(0),sec(0),
    timetable(new TimeTable(this)),
    welcomeWindow(new QWidget(this)),
    gameController(new SudokuGame(this)),
    infoBoard(new QWidget(this)),
    getInfo(new QPushButton(this)),
    restart(new QPushButton(this)),
    actList(new My_Stack())
{
    ui->setupUi(this);
    gameController->finalGenerator();
    init();
}

Widget::~Widget()
{
    delete ui;
    delete p_timer;
}

void Widget::init()
{
    timetable->move(500,70);

    ui->widget->setFixedSize(360,360);
    ui->widget->move(100,70);

    ui->widget_2->setFixedSize(150,150);
    ui->widget_2->move(500,280);

    ui->widget_3->setFixedSize(150,37);
    ui->widget_3->move(500,230);

    ui->widget_4->setFixedSize(150,40);
    ui->widget_4->move(500,180);
    //qDebug()<<ui->widget_2->x()<<","<<ui->widget_2->y();
    QString str="1,2,3,4,5,6,7,8,9";
    QStringList strList=str.split(",");
    QSignalMapper *mapper=new QSignalMapper(this);

    for(int i=0;i<9;i++)
    {
        QPushButton* pbtn=new QPushButton(ui->widget_2);
        pbtn->setStyleSheet("color: rgb(255,100,0); font-size: 35px; background-color: rgb(255,255,100); border: 2px solid rgb(255,170,0); border-radius: 12px;");
        pbtn->setText(strList.at(i));
        pbtn->setFixedSize(50,50);
        pbtn->move(50*(i%3),50*(i/3));

        connect(pbtn,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(pbtn,pbtn->text());
    }

    QPushButton* delBtn=new QPushButton(ui->widget_3);

    delBtn->setText("DEL");

    delBtn->setFixedSize(37,37);

    delBtn->move(76,0);


    //my_button **a;
    a=new my_button*[9];
    for(int i=0;i<9;i++)
    {
        a[i]=new my_button[9];
        for(int j=0;j<9;j++)
        {
            a[i][j].setParent(ui->widget);
            a[i][j].move(40*j,40*i);
            connect(mapper,SIGNAL(mapped(QString)),&a[i][j],SLOT(setText_wrapper(QString)));
            connect(delBtn,SIGNAL(clicked()),&a[i][j],SLOT(delBtn()));
            /*for(int m=0;m<9;m++)
            {
                for(int n=0;n<9;n++)
                {
                    connect(&a[i][j],SIGNAL(textChanged()),&a[m][n],SLOT(highlight()));
                }
            }*/

            //qDebug()<<a[i][j].objectName();
        }
    }

    //action record part//


    //My_Stack* actList=new My_Stack();
    actList->setParent(this);

    restart->setParent(ui->widget_3);
    restart->setFixedSize(37,37);
    restart->move(113,0);
    restart->setText("R");

    //restart->setText(QString::fromLocal8Bit(""));

    connect(restart,SIGNAL(clicked()),actList,SLOT(reStartAct()));
    connect(restart,SIGNAL(clicked()),this,SLOT(retime()));
    //connect(this,SIGNAL(newgame()),this->restart,SLOT(click()));


    QPushButton* bbtn=new QPushButton(ui->widget_3);
    QPushButton* fbtn=new QPushButton(ui->widget_3);

    //bbtn->setStyleSheet("border-color: rgb(0,255,255);background-color: rgb(255,255,0);border-width: 15px;");

    bbtn->setFixedSize(37,37);
    fbtn->setFixedSize(37,37);

    bbtn->move(0,0);
    fbtn->move(37,0);

    bbtn->setText("<<");
    fbtn->setText(">>");

    connect(bbtn,SIGNAL(clicked()),actList,SLOT(getBack()));
    connect(fbtn,SIGNAL(clicked()),actList,SLOT(getForward()));

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            connect(&a[i][j],SIGNAL(sendAction(int,int,QString)),actList,SLOT(getAction(int,int,QString)));
            connect(actList,SIGNAL(sendGeo(int,int,QString)),&a[i][j],SLOT(getGeo(int,int,QString)));
            connect(restart,SIGNAL(clicked()),&a[i][j],SLOT(reSetBtn()));

            //qDebug()<<i<<j;
            for(int m=0;m<9;m++)
                for(int n=0;n<9;n++)
                {
                        connect(&a[i][j],SIGNAL(textChanged()),&a[m][n],SLOT(highlight()));

                }
        }
    //a[0][0].setText("9"); //指代测试良好

    /*for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            my_button *btn=new my_button(ui->widget);
            btn->move(40*j,40*i);
            //btn->show();
            qDebug()<<btn->objectName();//这样以后没有办法指代
        }
    }*/



    p_timer->setInterval(1000);

    QPushButton* run_pause=new QPushButton(timetable);

    run_pause->setFixedSize(50,50);
    run_pause->move(100,0);
    run_pause->setText("P/C");

    run_pause->setStyleSheet("font-size: 25px; font: bold;"
                             "border: 2px solid green;"
                             "border-radius: 8px;"
                             "color: green;"
                             "background-color: rgb(200,255,100);");

    connect(run_pause,SIGNAL(clicked()),this,SLOT(run_pause_check()));
    connect(p_timer,SIGNAL(timeout()),this,SLOT(time_update()));


    ui->widget_3->setStyleSheet("QPushButton{font-size: 25px; font: bold; "
                                "border: 2px solid rgb(0,100,255);"
                                "border-radius: 7px; "
                                "color: rgb(0,100,255); "
                                "background-color: rgb(200,255,255)};");



    welcomeWindow->setFixedSize(550,360);
    welcomeWindow->move(100,70);
    welcomeWindow->setStyleSheet("background-color: yellow;"
                                 "border: 3px solid blue;");

    QSignalMapper* mapper_2=new QSignalMapper(this);

    QPushButton *levelBtn;

    levelBtn=new QPushButton[10];

    for(int i=0;i<10;i++)
    {
        levelBtn[i].setParent(welcomeWindow);
        levelBtn[i].setFixedSize(200,50);
        levelBtn[i].move(25+(i%2)*300,60+(i/2)*60);

        levelBtn[i].setText("Level "+QString::number(i+1));
        levelBtn[i].setStyleSheet("font-size: 40px;font: bold;"
                                  "border: 3px solid white;");
        connect(&levelBtn[i],SIGNAL(clicked()),mapper_2,SLOT(map()));
        mapper_2->setMapping(&levelBtn[i],i+1);
    }

    connect(mapper_2,SIGNAL(mapped(int)),this,SLOT(level_choose(int)));

    connect(gameController,SIGNAL(init_ui(int**)),this,SLOT(sym_ui(int**)));


    /*QPushButton* level_1=new QPushButton(welcomeWindow);
    level_1->move(0,0);
    level_1->setText("Level 1");

    connect(level_1,SIGNAL(clicked()),this,SLOT(level_choose()));


*/

    QPushButton* check=new QPushButton(ui->widget_4);
    QPushButton* ans=new QPushButton(ui->widget_4);
    QPushButton* menu=new QPushButton(ui->widget_4);

    check->setFixedSize(40,40);
    ans->setFixedSize(40,40);
    menu->setFixedSize(40,40);

    check->move(0,0);
    ans->move(55,0);
    menu->move(110,0);

    check->setText("Win?");
    ans->setText("Ans");
    menu->setText("Menu");

    ui->widget_4->setStyleSheet("QPushButton{font-size: 15px; font: bold; "
                                "border: 2px solid rgb(255,0,0);"
                                "border-radius: 7px; "
                                "color: rgb(200,0,0); "
                                "background-color: rgb(255,200,255)};");

    connect(check,SIGNAL(clicked()),this,SLOT(isFinished()));
    connect(ans,SIGNAL(clicked(bool)),gameController,SLOT(showAns()));
    connect(menu,SIGNAL(clicked(bool)),this,SLOT(menuRequest()));

    infoBoard->setFixedSize(550,100);
    infoBoard->move(100,450);

    getInfo->setParent(infoBoard);
    getInfo->move(0,0);
    getInfo->setFixedSize(550,100);
    getInfo->setStyleSheet("font-size: 50px;"
                           "font: bold;"
                           "border: 2px solid rgb(255,0,0);"
                           "border-radius: 30px;"
                           "color: rgb(200,0,0);"
                           "background-color: rgb(255,200,255);");

    connect(getInfo,SIGNAL(clicked(bool)),this,SLOT(infoToGame()));


/*
    ui->widget->hide();
    ui->widget_2->hide();
    ui->widget_3->hide();
    timetable->hide();
    ui->widget_4->hide();
*/
    gameWindowHide();



}

void Widget::infoToGame()
{
    infoBoard->hide();
    gameWindowShow();
}

void Widget::gameWindowShow()
{
    ui->widget->show();
    ui->widget_2->show();
    ui->widget_3->show();
    ui->widget_4->show();
    timetable->show();
    infoBoard->show();
}

void Widget::gameWindowHide()
{
    ui->widget->hide();
    ui->widget_2->hide();
    ui->widget_3->hide();
    timetable->hide();
    ui->widget_4->hide();
    infoBoard->hide();
}

void Widget::sym_ui(int** sa)
{
    //restart->click();
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sa[i][j]!=0)
            {
                this->a[i][j].setText(QString::number(sa[i][j]));
                this->a[i][j].setDisabled(true);
            }
        }
    }
}

void Widget::run_pause_check()
{
    if(p_timer->isActive())
    {
        p_timer->stop();
        ui->widget->hide();
    }
    else
    {
        p_timer->start();
        ui->widget->show();
    }
}

void Widget::time_update()
{
    if(min<60)
    {
        if(sec<60)sec++;
        if(sec==60)
        {
            sec=0;
            min++;
        }
        if(min==60)
            p_timer->stop();
    }

    timetable->showtime(min,sec);
}

void Widget::level_choose(int i)
{

    //this->show();

    this->gameController->digHole(i);



    welcomeWindow->hide();

    gameWindowShow();
    p_timer->start();
}

void Widget::isFinished()
{
    showInfo(rowFinished()&&colFinished()&&blockFinished());
}

void Widget::showInfo(bool i)
{
    infoBoard->show();
    if(i==1)
        getInfo->setText("Congratulations!!!");
    else
        getInfo->setText("emmm....Sorry~");
}

bool Widget::rowFinished()
{
    QString temp="",cur;
    int row=0;
    while(row<9)
    {
        for(int i=0;i<9;i++)
        {
            cur=a[row][i].text();
            qDebug()<<cur;
            if(cur.length()!=1)return false;

            if(!temp.contains(cur))temp+=cur;
            else return false;
        }
        qDebug()<<"row "<<row<<" is complete!";
        temp="";
        row++;
    }
    return true;
}

bool Widget::colFinished()
{
    QString temp="",cur;
    int col=0;
    while(col<9)
    {
        for(int i=0;i<9;i++)
        {
            cur=a[i][col].text();
            qDebug()<<cur;
            if(cur.length()!=1)return false;

            if(!temp.contains(cur))temp+=cur;
            else return false;
        }
        qDebug()<<"col "<<col<<" is complete!";
        temp="";
        col++;
    }
    return true;
}

bool Widget::blockFinished()
{
    QString temp="",cur;
    int block_id=0;
    int r,c,br,bc,x,y;
    while(block_id<9)
    {
        br=block_id/3;
        bc=block_id%3;

        for(int i=0;i<9;i++)
        {
            r=i/3;
            c=i%3;

            x=3*br+r;
            y=3*bc+c;

            cur=a[x][y].text();
            qDebug()<<cur;
            if(cur.length()!=1)return false;
            if(!temp.contains(cur))temp+=cur;
            else return false;
        }
        qDebug()<<"block "<<block_id<<" is complete!";
        temp="";
        block_id++;
    }
    return true;
}

void Widget::menuRequest()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            a[i][j].setEnabled(true);
            a[i][j].setText("");
        }
    }
    retime();
    actList->reStartAct();

    welcomeWindow->show();
    gameWindowHide();
}

void Widget::retime()
{
    this->min=0;
    this->sec=0;
}
