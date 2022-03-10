#include "my_stack.h"
#include <QDebug>

void My_Stack::getAction(int x, int y, QString str)
{
    qDebug()<<"getaction called";
    int xx=x/40;
    int yy=y/40;

    Act act{xx,yy,str};

    stk.push(act);
    qDebug()<<xx<<","<<yy<<","<<str;
    qDebug()<<"stk.top:"<<stk[stk.length()-1].xx<<","<<stk[stk.length()-1].yy<<','<<stk[stk.length()-1].msg;


}

void My_Stack::getBack()
{
    if(!stk.isEmpty())
    {
        while(!reregret.isEmpty())
        {
            reregret.pop_front();
        }
        change=stk.pop();
        reregret.push(change);

        emit sendGeo(change.xx*40,change.yy*40,"");
    }

}

void My_Stack::getForward()
{
    if(!reregret.isEmpty())
    {
        change=reregret.pop();
        stk.push(change);

        emit sendGeo(change.xx*40,change.yy*40,change.msg);
    }
}

void My_Stack::reStartAct()
{
    while(!stk.empty())
    {
        stk.pop_back();
    }
    while(!reregret.empty())
    {
        reregret.pop_back();
    }
}
