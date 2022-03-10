#include "timetable.h"
#include <QLabel>

TimeTable::TimeTable(QWidget *parent):
    QWidget(parent)
{
    int len=150,hgt=50;
    this->setFixedSize(len,100);
    minBoard=new QLabel(this);
    secBoard=new QLabel(this);
    colon=new QLabel(this);
    note=new QLabel(this);

    //this->setStyleSheet("border: 3px solid green;");
    this->setStyleSheet("QLabel{font-size: 49px; font: bold; color: green;}"
                            "border: 3px solid blue;");

    //this->setStyleSheet("border: 3px solid green;");

    minBoard->setFixedSize(hgt,hgt);
    secBoard->setFixedSize(hgt,hgt);
    colon->setFixedSize(hgt,hgt);
    note->setFixedSize(2*hgt,hgt);

    minBoard->setText("00");
    secBoard->setText("00");
    colon->setText(":");
    note->setText("TIME:");

    minBoard->move(0,hgt);
    colon->move(hgt,hgt);
    secBoard->move(2*hgt,hgt);
    note->move(0,0);

    note->setStyleSheet("font-size: 30px; font: bold;");
    //minBoard->setStyleSheet("font-size: 49px; font: bold; color: green;");
    //secBoard->setStyleSheet("font-size: 49px; font: bold; color: green;");
    //colon->setStyleSheet("font-size: 49px; font: bold; color: green;");

}

void TimeTable::showtime(int a,int b)
{
    QString minstr,secstr;
    minstr=QString::number(a);
    secstr=QString::number(b);


    if(a<10)
    {
        minstr="0"+minstr;
    }
    if(b<10)
    {
        secstr="0"+secstr;
    }

    minBoard->setText(minstr);
    secBoard->setText(secstr);
}
