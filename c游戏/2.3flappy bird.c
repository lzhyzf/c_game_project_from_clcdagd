#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int bar1_y, bar1_xDown, bar1_xTop, bar2_y, bar2_xDown, bar2_xTop;      //障碍物
int bird_x, bird_y;                     //小鸟的坐标
int high, width;                        //游戏画面尺寸
int score;                              //得分，经过障碍物个数
float gv;                                 //重力影响影响下速度

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void startup()                          //游戏的初始化
{
    high = 20;
    width = 50;
    bird_x = high / 2;
    bird_y = 3;
    bar1_y = width / 2;
    bar1_xDown = high / 2;
    bar1_xTop = high / 3;
    bar2_y = bar1_y + 15;
    bar2_xDown = high / 2;
    bar2_xTop = high / 3;
    score = 0;
}

void show()                             //显示画面
{
    gotoxy(0, 0);                      //光标移动到原点位置，以下重画清屏
    int i, j;

    for(i = 0; i < high; i++)
    {
        for(j = 0; j < width; j++)
        {
            if((i == bird_x) && (j == bird_y))
                printf("@");                              //输出小鸟
            else if( (j == bar1_y) && ((i > bar1_xDown) || (i < bar1_xTop)))
                printf("*");                              //输出墙壁1
            else if( (j == bar2_y) && ((i > bar2_xDown) || (i < bar2_xTop)))
                printf("*");                              //输出墙壁2
            else
                printf(" ");                              //输出空格
        }
        printf("\n");
    }
    printf("得分： %d\n", score);
}

void updateWithoutInput()                     //与用户无关的更新
{
    gv += 0.5;
    bird_x += gv;
    bar1_y--;
    bar2_y--;
    if(bird_y == bar1_y)
    {
        if(bird_x >= bar1_xTop && bird_x <= bar1_xDown)
            score++;
        else
        {
            printf("游戏失败\n");
            system("pause");
            exit(0);
        }
    }
    if(bird_y == bar2_y)
    {
        if(bird_x >= bar2_xTop && bird_x <= bar2_xDown)
            score++;
        else
        {
            printf("游戏失败\n");
            system("pause");
            exit(0);
        }
    }
    if(bird_x > high && bird_x < 0)
    {
        printf("游戏失败\n");
        system("pause");
        exit(0);
    }
    if(bar1_y <= 0)
    {
        bar1_y = width;
        int temp = rand()%(int)(high * 0.8);
        bar1_xDown = temp + high / 10;
        bar1_xTop = temp - high / 10;
    }
    if(bar2_y <= 0)
    {
        bar2_y = width;
        int temp = rand()%(int)(high * 0.8);
        bar2_xDown = temp + high / 10;
        bar2_xTop = temp - high / 10;
    }
    Sleep(150);
}

void updateWithInput()                        //与用户有关的更新
{
    char input;
    if(kbhit())                               //判断用户是否有输入
    {
        input = getch();                      //根据用户的不同输入来移动。不必输入回车
        if(input == ' ')
        {
            bird_x = bird_x - 2;
            gv = 0;
        }
    }
}
int main()
{
    startup();                                //游戏初始化
    while(1)                                  //游戏循环执行
    {
        show();                               //显示画面
        updateWithoutInput();                 //与用户输入无关的更新
        updateWithInput();                     //与用户输入有关的更新
    }

    return 0;
}
