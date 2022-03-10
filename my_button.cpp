#include "my_button.h"
#include <QDebug>


int my_button::xpos=-1;
int my_button::ypos=-1;

QString my_button::cur_text="=";

my_button::my_button(QWidget* parent)
    :QPushButton(parent)
{
    setText("");
    setFixedSize(40,40);
    setStyleSheet(QStringLiteral("font: bold; font-size: 20px; background-color: rgb(255, 255, 255);border: 2px solid rgb(255,170,0);"));
    //connect(this,SIGNAL(clicked(),this,SLOT())
}

void my_button::enterEvent(QEvent *event)
{
    if(!this->hasFocus()&&this->x()!=xpos&&this->y()!=ypos/*&&this->text()!=cur_text*/)
        setStyleSheet(QStringLiteral("font: bold; font-size: 30px; background-color: rgb(255, 130, 0);border: 2px solid rgb(255,170,0);"));
}

void my_button::leaveEvent(QEvent *event)
{
    if(!this->hasFocus()&&this->x()!=xpos&&this->y()!=ypos/*&&this->text()!=cur_text*/)
        setStyleSheet(QStringLiteral("font: bold; font-size: 20px; background-color: rgb(255, 255, 255);border: 2px solid rgb(255,170,0);"));
}

void my_button::focusInEvent(QFocusEvent *e)
{
    if(this->hasFocus())setStyleSheet(QStringLiteral("font: bold; font-size: 20px; background-color: rgb(255, 250, 0);border: 2px solid rgb(255,170,0);"));
    xpos=this->x();
    ypos=this->y();//如何实现高亮所有？
    cur_text=this->text();

    qDebug()<<"focusInEvent():"<<xpos<<" "<<ypos;
    emit textChanged();

    //emit sendText(this->text());
}

void my_button::focusOutEvent(QFocusEvent *e)
{
    setStyleSheet(QStringLiteral("font: bold; font-size: 20px; background-color: rgb(255, 255, 255);border: 2px solid rgb(255,170,0);"));
}



//-------------------------------------------------------------------------------------------//

//filling action start//

//-------------------------------------------------------------------------------------------//







void my_button::setText_wrapper(QString str)
{
    //if(this->hasFocus()) // 点击了右边的数字键盘，focus就不在这边了，所以如果加了这条判断，所有的my_button都不会 修改文本
    if(this->x()==xpos&&this->y()==ypos)
    {
        int textLen=(this->text().length()+1)/2;

        switch (textLen) {
        case 0:
            setText(str);
            emit sendAction(xpos,ypos,str);
            break;

        case 1:
            setText(this->text()+' '+str);
            emit sendAction(xpos,ypos,str);
            break;

        case 2:
            setText(this->text()+'\n'+str);
            emit sendAction(xpos,ypos,str);
            break;

        case 3:
            setText(this->text()+' '+str);
            emit sendAction(xpos,ypos,str);
            break;

        default:
            break;
        }

        /*
        setText(str);

        emit sendAction(xpos,ypos,str);
        qDebug()<<"this"<<xpos<<","<<ypos;
        */
    }
}

void my_button::highlight()
{
    if(this->text()==cur_text&&cur_text!="")setStyleSheet(QStringLiteral("color: red; font: bold; font-size: 20px; background-color: rgb(255, 250, 0);border: 2px solid rgb(255,170,0);"));
    else
    {
        if(!this->hasFocus())
        {
            if(this->x()==xpos||this->y()==ypos)
                setStyleSheet(QStringLiteral("font: bold; font-size: 20px; background-color: rgb(200, 255, 255);border: 2px solid rgb(255,170,0);border-radius: 8px;"));
            else setStyleSheet(QStringLiteral("font: bold; font-size: 20px; background-color: rgb(255, 255, 255);border: 2px solid rgb(255,170,0);"));
        }
    }

    /*if((this->x()==xpos||this->y()==ypos)&&!this->hasFocus())
        setStyleSheet(QStringLiteral("background-color: rgb(100, 250, 0);"));
    else
    {
        if(!this->hasFocus())setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
    }*/
}

void my_button::getGeo(int x, int y, QString str)
{
    if(this->x()==x&&this->y()==y)
    {
        int curlen=this->text().length();

        if(str=="")
        {
            //this->setText(str);
            //int curlen=this->text().length();
            if(curlen<=1)
                setText("");
            else
                setText(this->text().left(curlen-2));
        }
        else
        {
            switch (curlen) {
            case 0:
                setText(str);
                break;

            case 1:
                setText(this->text()+' '+str);
                break;

            case 3:
                setText(this->text()+'\n'+str);
                break;

            case 5:
                setText(this->text()+' '+str);
                break;

            default:
                break;
            }
        }
    }
}

void my_button::reSetBtn()
{
    if(this->isEnabled())
        this->setText("");
}

void my_button::delBtn()
{
    if(this->x()==xpos&&this->y()==ypos)
        setText("");
}
