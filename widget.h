#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class TimeTable;
class SudokuGame;
class my_button;
class My_Stack;

class QPushButton;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void init();

public slots:
    void run_pause_check();
    void time_update();
    void level_choose(int);
    void sym_ui(int**);
    void isFinished();
    void infoToGame();
    void menuRequest();
    void retime();
public:
    void gameWindowHide();
    void gameWindowShow();
    void showInfo(bool);

public:
    bool rowFinished();
    bool colFinished();
    bool blockFinished();

//signals:
    //void newgame();
private:
    Ui::Widget *ui;
    QTimer *p_timer;
    int min;
    int sec;
    TimeTable* timetable;
    QWidget* welcomeWindow;
    SudokuGame* gameController;
    my_button** a;
    QWidget* infoBoard;
    QPushButton* getInfo;
    QPushButton* restart;
    My_Stack* actList;
};

#endif // WIDGET_H
