#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

//全局变量
int position_x, position_y;             //飞机位置
int bullet_x, bullet_y;                 //子弹位置
int enemy_x, enemy_y;                  //敌机位置
int high, width;                        //游戏画面尺寸
int score;                              //得分

void startup()                          //游戏的初始化
{
    high = 20;
    width = 30;
    position_x = high / 2;
    position_y = width / 2;
    bullet_x = -2;
    bullet_y = position_y;
    enemy_x = 0;
    enemy_y = position_y;
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
            if((i == position_x) && (j == position_y))
                printf("*");                              //输出飞机
            else if((i == enemy_x) && (j == enemy_y))
                printf("@");                              //输入敌机
            else if((i == bullet_x) && (j == bullet_y))
                printf("|");                                //输出子弹
            else
                printf(" ");                                //输出空格
        }
        printf("\n");
    }
    printf("得分： %d\n", score);
}

void updateWithoutInput()                     //与用户无关的更新
{
    if((bullet_x == enemy_x) && (bullet_y == enemy_y))
    {
        score++;                                //分数加1
        enemy_x = -1;                           //产生新的飞机
        enemy_y = rand()%width;
        bullet_x = -2;                          //子弹无效
    }
    if(enemy_x > high)                     //敌机跑出显示屏幕
    {
        enemy_x = -1;                      //产生新的飞机
        enemy_y = rand()%width;
    }
    if(bullet_x > -1)
        bullet_x--;
    //用来控制敌机向下移动速度，每隔几次循环才移动一次敌机
    //这样修改，虽然用户按键的交互速度还是很快，但NPC的移动显示可以降速
    static int speed = 0, levelspeed;
    levelspeed = 15 - score;
    if(speed < levelspeed)
        speed++;
    if(speed == levelspeed)
    {
        enemy_x++;
        speed = 0;
    }
}

void updateWithInput()
{
    char input;
    if(kbhit())                               //判断用户是否有输入
    {
        input = getch();                      //根据用户的不同输入来移动。不必输入回车
        if(input == 'a' && position_y > 0)                      //不超出屏幕位置左移
            position_y--;
        if(input == 'd' && position_y < width - 1)                      //不超出屏幕位置右移
            position_y++;
        if(input == 'w' && position_x > 0)                      //不超出屏幕位置上移
            position_x--;
        if(input == 's'&& position_x < high - 1)                      //不超出屏幕位置下移
            position_x++;
        if(input == ' ')
        {
            bullet_x = position_x - 1;        //发射子弹初始位置在飞机的正上方
            bullet_y = position_y;
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
