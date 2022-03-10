#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H
#include <QObject>
#include <vector>
class SudokuGame:public QObject
{
    Q_OBJECT

public:
    explicit SudokuGame(QObject* parent);
    void finalGenerator();
public:
    void fill();
    void fillBox(int,int);
    bool canfill(int,int,int);
    bool rowCheck(int,int);
    bool colCheck(int,int);
    bool blockCheck(int,int);
    void resolve(int);
    void rowExchange();
    void colExchange();
    void vectorStructor();

public:
    void digHole(int);
public slots:
    void showAns();
signals:
    void init_ui(int**);

private:
    int **a;
    int **pa;
    int **final;
    int cur_numcount;
    int total_numcount;
    int *randList;

    int resolve_count;
    std::vector<int> num;
    std::vector<int> loc;
};


#endif // SUDOKUGAME_H
