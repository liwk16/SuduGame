#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    /*my_button btn(&w);
    btn.show();
    my_button btn2(&w);
    btn2.move(100,0);

    w.show();*/
    return a.exec();
}
