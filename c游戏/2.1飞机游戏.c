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

//ȫ�ֱ���
int position_x, position_y;             //�ɻ�λ��
int bullet_x, bullet_y;                 //�ӵ�λ��
int enemy_x, enemy_y;                  //�л�λ��
int high, width;                        //��Ϸ����ߴ�
int score;                              //�÷�

void startup()                          //��Ϸ�ĳ�ʼ��
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

void show()                             //��ʾ����
{
    gotoxy(0, 0);                      //����ƶ���ԭ��λ�ã������ػ�����
    int i, j;
    for(i = 0; i < high; i++)
    {
        for(j = 0; j < width; j++)
        {
            if((i == position_x) && (j == position_y))
                printf("*");                              //����ɻ�
            else if((i == enemy_x) && (j == enemy_y))
                printf("@");                              //����л�
            else if((i == bullet_x) && (j == bullet_y))
                printf("|");                                //����ӵ�
            else
                printf(" ");                                //����ո�
        }
        printf("\n");
    }
    printf("�÷֣� %d\n", score);
}

void updateWithoutInput()                     //���û��޹صĸ���
{
    if((bullet_x == enemy_x) && (bullet_y == enemy_y))
    {
        score++;                                //������1
        enemy_x = -1;                           //�����µķɻ�
        enemy_y = rand()%width;
        bullet_x = -2;                          //�ӵ���Ч
    }
    if(enemy_x > high)                     //�л��ܳ���ʾ��Ļ
    {
        enemy_x = -1;                      //�����µķɻ�
        enemy_y = rand()%width;
    }
    if(bullet_x > -1)
        bullet_x--;
    //�������Ƶл������ƶ��ٶȣ�ÿ������ѭ�����ƶ�һ�εл�
    //�����޸ģ���Ȼ�û������Ľ����ٶȻ��Ǻܿ죬��NPC���ƶ���ʾ���Խ���
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
    if(kbhit())                               //�ж��û��Ƿ�������
    {
        input = getch();                      //�����û��Ĳ�ͬ�������ƶ�����������س�
        if(input == 'a' && position_y > 0)                      //��������Ļλ������
            position_y--;
        if(input == 'd' && position_y < width - 1)                      //��������Ļλ������
            position_y++;
        if(input == 'w' && position_x > 0)                      //��������Ļλ������
            position_x--;
        if(input == 's'&& position_x < high - 1)                      //��������Ļλ������
            position_x++;
        if(input == ' ')
        {
            bullet_x = position_x - 1;        //�����ӵ���ʼλ���ڷɻ������Ϸ�
            bullet_y = position_y;
        }
    }
}
int main()
{
    startup();                                //��Ϸ��ʼ��
    while(1)                                  //��Ϸѭ��ִ��
    {
        show();                               //��ʾ����
        updateWithoutInput();                 //���û������޹صĸ���
        updateWithInput();                     //���û������йصĸ���
    }

    return 0;
}
