#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ���
int ball_x, ball_y;             //С�������
int high, width;                //��Ϸ����ߴ�
int ball_vx, ball_vy;           //С����ٶ�
int position_x, position_y;     //�������������
int ridus;                      //����İ뾶��С
int left, right;                //���������λ��
int ball_number;                //����С��Ĵ���
int block_x, block_y;           //ש���λ��
int score;                      //������ש�����

void gotoxy(int x, int y)       //������ƶ�����x��y��λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void startup()                          //��Ϸ�ĳ�ʼ��
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

void show()                             //��ʾ����
{
    gotoxy(0, 0);                      //����ƶ���ԭ��λ�ã������ػ�����
    int i, j;
    for(i = 0; i <= high + 1; i++)
    {
        for(j = 0; j <= width; j++)
        {
            if((i == ball_x) && (j == ball_y))
                printf("o");                              //���С��
            else if(j == width)
                printf("|");                              //����ұ߿�
            else if(i == high + 1)
                printf("-");                              //����±߿�
            else if((i == high) && (j >= left) && (j <= right))      //�������
                printf("*");
            else if((i == block_x) && (j == block_y))              //���ש��
                printf("B");
            else
                printf(" ");                              //����ո�
        }
        printf("\n");
    }
    printf("����С������ %d\n", ball_number);
    printf("������ש������ %d\n", score);
}

void updateWithoutInput()                     //���û��޹صĸ���
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
            printf("��Ϸʧ��\n");
            system("pause");
            exit(0);
        }
    }
    if((ball_x == block_x) && (ball_y == block_y))     //С�����ש��
    {
        score++;                      //������һ
        block_y = rand()%width;       //��������µ�ש��
    }
    ball_x = ball_x + ball_vx;
    ball_y = ball_y + ball_vy;
    if(ball_x == 0 || ball_x == high - 1)
        ball_vx = -ball_vx;
    if(ball_y == 0 || ball_y == width - 1)
        ball_vy = -ball_vy;
        Sleep(80);
}

void updateWithInput()          //���û������йصĸ���
{
    char input;
    if(kbhit())                 //�ж��Ƿ�������
    {
        input = getch();
        if(input == 'a')        //λ������
        {
            position_y--;
            left = position_y - ridus;
            right = position_y + ridus;
        }
        if(input == 'd')        //λ������
        {
            position_y++;
            left = position_y - ridus;
            right = position_y + ridus;
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

