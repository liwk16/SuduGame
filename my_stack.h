#ifndef MY_STACK_H
#define MY_STACK_H
#include <QObject>
#include <QStack>

struct Act
{
    int xx;
    int yy;
    QString msg;
};

class My_Stack:public QObject
{
    Q_OBJECT

public slots:
    void getAction(int,int,QString);
    void getBack();
    void getForward();
    void reStartAct();
signals:
    void sendGeo(int,int,QString);
private:
    QStack<Act> stk;
    QStack<Act> reregret;
    Act change;
};

#endif // MY_STACK_H
