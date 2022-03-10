#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <QWidget>
#include <QLabel>
class TimeTable:public QWidget
{
    Q_OBJECT
public:
    explicit TimeTable(QWidget* parent=0);
private:
    QLabel* minBoard;
    QLabel* secBoard;
    QLabel* colon;
    QLabel* note;
public slots:
    void showtime(int,int);
};

#endif // TIMETABLE_H
