#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ���
int bar1_y, bar1_xDown, bar1_xTop, bar2_y, bar2_xDown, bar2_xTop;      //�ϰ���
int bird_x, bird_y;                     //С�������
int high, width;                        //��Ϸ����ߴ�
int score;                              //�÷֣������ϰ������
float gv;                                 //����Ӱ��Ӱ�����ٶ�

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

void show()                             //��ʾ����
{
    gotoxy(0, 0);                      //����ƶ���ԭ��λ�ã������ػ�����
    int i, j;

    for(i = 0; i < high; i++)
    {
        for(j = 0; j < width; j++)
        {
            if((i == bird_x) && (j == bird_y))
                printf("@");                              //���С��
            else if( (j == bar1_y) && ((i > bar1_xDown) || (i < bar1_xTop)))
                printf("*");                              //���ǽ��1
            else if( (j == bar2_y) && ((i > bar2_xDown) || (i < bar2_xTop)))
                printf("*");                              //���ǽ��2
            else
                printf(" ");                              //����ո�
        }
        printf("\n");
    }
    printf("�÷֣� %d\n", score);
}

void updateWithoutInput()                     //���û��޹صĸ���
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
            printf("��Ϸʧ��\n");
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
            printf("��Ϸʧ��\n");
            system("pause");
            exit(0);
        }
    }
    if(bird_x > high && bird_x < 0)
    {
        printf("��Ϸʧ��\n");
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

void updateWithInput()                        //���û��йصĸ���
{
    char input;
    if(kbhit())                               //�ж��û��Ƿ�������
    {
        input = getch();                      //�����û��Ĳ�ͬ�������ƶ�����������س�
        if(input == ' ')
        {
            bird_x = bird_x - 2;
            gv = 0;
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
