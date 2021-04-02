#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 15  // ��Ϸ����ߴ�
#define Width 20

//ȫ�ֱ���
int ball_x, ball_y;                       //С�������
int ball_vx, ball_vy;                     //С����ٶ�
int position_x, position_y;               //������������
int radius;                               //����뾶��С
int left, right;                          //���������λ��
int canvas[High][Width] = {};             // ��ά���鴢����Ϸ�����ж�ӦԪ��
                                          //0λ�ո�1λС��,2Ϊ����,3Ϊש��

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void startup()                          //��Ϸ�ĳ�ʼ��
{
    ball_x = High / 3;
    ball_y = Width / 2;
    ball_vx = 1;
    ball_vy = 1;
    canvas[ball_x][ball_y] = 1;

    radius = 5;
    position_x = High - 1;
    position_y = Width / 2;
    left = position_y - radius;
    right = position_y + radius;

    int k, i;
    for(k = left; k <= right; k++)
        canvas[position_x][k] = 2;

    for(k = 0; k < Width; k++)               //�Ӽ���ש��
        for(i = 0; i < High / 4; i++)
            canvas[i][k] = 3;
}

void show()                             //��ʾ����
{
    gotoxy(0, 0);                      //����ƶ���ԭ��λ�ã������ػ�����
    int i, j;

    for(i = 0; i < High; i++)
    {
        for(j = 0; j < Width; j++)
        {
            if(canvas[i][j] == 0)
                printf(" ");                              //����ո�
            else if(canvas[i][j] == 1)
                printf("o");                              //���С��
            else if(canvas[i][j] == 2)
                printf("*");                              //�������
            else if(canvas[i][j] == 3)
                printf("$");                              //���ש��
        }
        printf("|\n");                                    //����ұ߽�
    }
    for(j = 0; j < Width; j++)                            //����±߽�
        printf("-");
}

void updateWithoutInput()                     //���û��޹صĸ���
{
    if(ball_x == High - 2)
    {
        if(ball_y >= left && ball_y <= right) //�򱻵��嵲ס
        {
        }
        else                                  //��û�б���ס
        {
            printf("��Ϸʧ��\n");
            system("pause");
            exit(0);
        }
    }

    static int speed = 0;
    if(speed < 7)
        speed++;
    if(speed == 7)
    {
        speed = 0;

        canvas[ball_x][ball_y] = 0;
        //����С������
        ball_x = ball_x + ball_vx;
        ball_y = ball_y + ball_vy;
        canvas[ball_x][ball_y] = 1;

        //�����߽�󷴵�
        if((ball_x == 0) || (ball_x == High - 2))
            ball_vx = -ball_vx;
        if((ball_y == 0) || (ball_y == Width - 1))
            ball_vy = -ball_vy;

        //����ש��󷴵�
        if(canvas[ball_x + ball_vx][ball_y + ball_vy] == 3)
        {
            canvas[ball_x + ball_vx][ball_y + ball_vy] = 0;
            ball_vx = -ball_vx;
            printf("\a");
        }
        Sleep(50);

    }
}

void updateWithInput()                        //���û��йصĸ���
{
    char input;
    if(kbhit())
    {
        input = getch();                     //�����û��Ĳ�ͬ�������ƶ�����������س�
        if(input == 'a' && left > 0)
        {
            canvas[position_x][right] = 0;
            position_y--;                   //λ������
            left = position_y - radius;
            right = position_y + radius;
            canvas[position_x][left] = 2;
        }
        else if(input == 'd' && right < Width - 1)
        {
            canvas[position_x][left] = 0;
            position_y++;                   //λ������
            left = position_y - radius;
            right = position_y + radius;
            canvas[position_x][right] = 2;
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
