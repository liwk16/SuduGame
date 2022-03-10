#ifndef MY_BUTTON_H
#define MY_BUTTON_H
#include <QPushButton>

class my_button:public QPushButton
{
    Q_OBJECT
public:
    my_button(QWidget* parent=0);
    ~my_button(){return;}
protected:
    virtual void enterEvent(QEvent* event);//鼠标经过操作                                                   //其实这两个函数可以使用qss直接在对象初始化时设定select-color，hover等来实现
    virtual void leaveEvent(QEvent* event);//鼠标离开操作
    void focusInEvent(QFocusEvent* e);//鼠标点击，焦点选中操作
    void focusOutEvent(QFocusEvent *e);//焦点转移操作
public slots:
    void setText_wrapper(QString);//修改按钮文本的装饰函数
    void highlight();//高亮操作，包含数字高亮以及对应行列选中高亮
    void getGeo(int,int,QString);//后退，前进按钮对应槽函数，前两个int记录位置，将对应位置的按钮内容置为QString
    void reSetBtn();//重置按钮操作
    void delBtn();//清空按钮中的多个数据
signals:
     void textChanged();
     void sendAction(int,int,QString);
private:
    static int xpos,ypos;//记录焦点框所在位置
    static QString cur_text;//记录当前焦点框内按钮文本

};

#endif // MY_BUTTON_H
