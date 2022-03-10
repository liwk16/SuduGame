#include "sudokugame.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>

SudokuGame::SudokuGame(QObject* parent):
    QObject(parent)
{

    a=new int*[9];
    pa=new int*[9];
    final=new int*[9];

    randList = new int[9];
    randList[0] = 3;
    randList[1] = 7;
    randList[2] = 2;
    randList[3] = 9;
    randList[4] = 5;
    randList[5] = 1;
    randList[6] = 4;
    randList[7] = 8;
    randList[8] = 6;

    for(int i=0;i<9;i++)
    {
        a[i]=new int[9];
        pa[i]=new int[9];
        final[i]=new int[9];

        for(int j=0;j<9;j++)
        {
            a[i][j]=0;
            pa[i][j]=0;
        }
    }
    cur_numcount=0;
    total_numcount=0;
    resolve_count=0;

    srand((unsigned)time(NULL));
}

void SudokuGame::finalGenerator()
{
    this->fill();
    this->rowExchange();
    this->colExchange();

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            final[i][j]=a[i][j];
        }
    }
}

void SudokuGame::fill()
{
        fillBox(0,0);
}

void SudokuGame::fillBox(int bn,int num)
{
    int row=bn/3;
    int col=bn%3;


    for(int i=3*row;i<3*row+3;i++)
    {
        for(int j=3*col;j<3*col+3;j++)
        {
            if(canfill(i,j,randList[num]))
            {
                //a[i][j]=num;
                //pa[i][j]=1;
                /*
                cur_numcount++;
                if(cur_numcount<9)
                {
                    fillBox(bn+1,num);
                }
                else if(cur_numcount==9)
                {
                    total_numcount++;
                    cur_numcount=0;
                    fillBox(0,num+1);
                }

                if(cur_numcount>0)
                {
                    a[i][j]=0;
                    pa[i][j]=0;
                    cur_numcount--;
                }
                else if(cur_numcount==0)
                {

                }

                */
                a[i][j]=randList[num];
                pa[i][j]=1;
                bn++;
                if(bn<9)
                {
                    fillBox(bn,num);
                }
                else if(bn==9)
                {
                    total_numcount++;
                    if(num==8)
                    {
                       qDebug()<<"success!";
                    }
                    else
                    {
                        fillBox(0,num+1);
                    }
                }

                if(total_numcount==9)
                {
                    break;break;
                }
                a[i][j]=0;
                pa[i][j]=0;
                bn--;

                if(bn==8)
                {
                    total_numcount--;
                }

            }
        }
    }
}

bool SudokuGame::rowCheck(int row,int num)
{
    int count=0;
    for(int i=0;i<9;i++)
    {
        if(a[row][i]==num)
        {
            count++;
        }
    }
    if(count==0)return 1;

    return 0;
}

bool SudokuGame::colCheck(int col, int num)
{
    int count=0;
    for(int i=0;i<9;i++)
    {
        if(a[i][col]==num)
        {
            count++;
        }
    }
    if(count==0)return 1;

    return 0;
}

bool SudokuGame::blockCheck(int bn, int num)
{
    int count=0;
    int br=bn/3;
    int bc=bn%3;

    for(int i=3*br;i<3*br+3;i++)
    {
        for(int j=3*bc;j<3*bc+3;j++)
        {
            if(a[i][j]==num)
            {
                count++;
            }
        }
    }
    if(count==0)return 1;

    return 0;
}

bool SudokuGame::canfill(int row, int col,int num)
{
    return (pa[row][col]==0&&rowCheck(row,num)&&colCheck(col,num));
}


void SudokuGame::rowExchange()
{
    int temp=0;
    int ex_times=rand()%5+5;
    while(ex_times--)
    {
        int bar=rand()%3;

        int f=rand()%3;
        int b=rand()%3;

        while(f==b)
        {
            b=rand()%3;
        }

        f+=bar*3;
        b+=bar*3;

        for(int i=0;i<9;i++)
        {
            temp=a[f][i];
            a[f][i]=a[b][i];
            a[b][i]=temp;
        }

    }
}

void SudokuGame::colExchange()
{
    int temp=0;
    int ex_times=rand()%5+5;
    while(ex_times--)
    {
        int bar=rand()%3;

        int f=rand()%3;
        int b=rand()%3;

        while(f==b)
        {
            b=rand()%3;
        }

        f+=bar*3;
        b+=bar*3;

        for(int i=0;i<9;i++)
        {
            temp=a[i][f];
            a[i][f]=a[i][b];
            a[i][b]=temp;
        }

    }
}

void SudokuGame::digHole(int num)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            a[i][j]=final[i][j];
            pa[i][j]=1;
        }
    }
    num=18+2*num;
    qDebug()<<"hole num: "<<num;
    if((num==20))num=8;

    int block_id=0;
    int r,c,hole,br,bc;
    int x,y;
    while(num--)
    {
        hole=rand()%9;
        r=hole/3;
        c=hole%3;

        br=block_id/3;
        bc=block_id%3;

        x=3*br+r;
        y=3*bc+c;

        a[x][y]=0;
        pa[x][y]=0;

        block_id++;
        if(block_id==9)
            block_id=0;

    }
    emit init_ui(this->a);
}

void SudokuGame::showAns()
{
    emit init_ui(final);
}

void SudokuGame::vectorStructor()
{
    for (int i = 1; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            //cout << "di " << j << "kuai" << endl;
            if (blockCheck(j , i))
            {
                this->num.push_back(i);
                this->loc.push_back(j);

                //cout << "(" << i << "," << j << ")";
            }
        }
        //cout << endl;
    }
}

void SudokuGame::resolve(int step)
{
    resolve_count = step;
    int number = num[step];
    int bn = loc[step];

    int row = bn / 3;
    int col = bn % 3;


        for (int i = 3 * row; i < 3 * row + 3; i++)
        {
            for (int j = 3 * col; j < 3 * col + 3; j++)
            {

                if (canfill(i, j, number))
                {
                    a[i][j] = number;
                    pa[i][j] = 1;


                    if (step<num.size()-1)
                    {
                        resolve(step + 1);
                    }

                    if (resolve_count == loc.size()-1)

                    {
                        break;
                        break;
                    }
                    //cout << loc.size() << endl;
                    //cout << "re: " << resolve_count << endl;
                    a[i][j] = 0;
                    pa[i][j] = 0;
                }

        }
    }
}


