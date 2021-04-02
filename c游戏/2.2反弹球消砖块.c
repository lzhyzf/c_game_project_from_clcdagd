#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int ball_x, ball_y;             //小球的坐标
int high, width;                //游戏画面尺寸
int ball_vx, ball_vy;           //小球的速度
int position_x, position_y;     //挡板的中心坐标
int ridus;                      //挡板的半径大小
int left, right;                //挡板的左右位置
int ball_number;                //反弹小球的次数
int block_x, block_y;           //砖块的位置
int score;                      //消掉的砖块个数

void gotoxy(int x, int y)       //将光标移动到（x，y）位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void startup()                          //游戏的初始化
{
    high = 15;
    width = 20;
    ball_x = 0;
    ball_y = width / 2;
    ball_vx = 1;
    ball_vy = 1;
    ridus = 5;
    position_x = high;
    position_y = width / 2;
    left = position_y - ridus;
    right = position_y + ridus;
    ball_number = 0;
    block_x = 0;
    block_y = width / 2 + 1;
    score = 0;
}

void show()                             //显示画面
{
    gotoxy(0, 0);                      //光标移动到原点位置，以下重画清屏
    int i, j;
    for(i = 0; i <= high + 1; i++)
    {
        for(j = 0; j <= width; j++)
        {
            if((i == ball_x) && (j == ball_y))
                printf("o");                              //输出小球
            else if(j == width)
                printf("|");                              //输出右边框
            else if(i == high + 1)
                printf("-");                              //输出下边框
            else if((i == high) && (j >= left) && (j <= right))      //输出挡板
                printf("*");
            else if((i == block_x) && (j == block_y))              //输出砖块
                printf("B");
            else
                printf(" ");                              //输出空格
        }
        printf("\n");
    }
    printf("反弹小球数： %d\n", ball_number);
    printf("消掉的砖块数： %d\n", score);
}

void updateWithoutInput()                     //与用户无关的更新
{
    if(ball_x == high - 1)
    {
        if(ball_y >= left && ball_y <= right)
        {
           ball_number++;
           printf("\a");
           //ball_y = ball_y + rand()%4 - 2;
        }
        else
        {
            printf("游戏失败\n");
            system("pause");
            exit(0);
        }
    }
    if((ball_x == block_x) && (ball_y == block_y))     //小球击中砖块
    {
        score++;                      //分数加一
        block_y = rand()%width;       //随机产生新的砖块
    }
    ball_x = ball_x + ball_vx;
    ball_y = ball_y + ball_vy;
    if(ball_x == 0 || ball_x == high - 1)
        ball_vx = -ball_vx;
    if(ball_y == 0 || ball_y == width - 1)
        ball_vy = -ball_vy;
        Sleep(80);
}

void updateWithInput()          //与用户输入有关的更新
{
    char input;
    if(kbhit())                 //判断是否有输入
    {
        input = getch();
        if(input == 'a')        //位置左移
        {
            position_y--;
            left = position_y - ridus;
            right = position_y + ridus;
        }
        if(input == 'd')        //位置右移
        {
            position_y++;
            left = position_y - ridus;
            right = position_y + ridus;
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

