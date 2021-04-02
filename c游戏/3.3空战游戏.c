#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 15  // ��Ϸ����ߴ�
#define Width 25
#define EnemyNum 5  //�л��ĸ���

//ȫ�ֱ���
int position_x, position_y;                   //�ɻ���λ��
int enemy_x[EnemyNum], enemy_y[EnemyNum];     //�л���λ��
int canvas[High][Width] = {};                 //��ά���鴢����Ϸ�����ж�Ӧ��Ԫ��
//0λ�ո�1Ϊ�ɻ�*,2Ϊ�ӵ�|��3Ϊ�л�@
int score;                                    //�÷�
int BulletWidth;                              //�ӵ��Ŀ��
int EnemyMoveSpeed;                           //�л����ƶ��ٶ�

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
    position_x = High - 1;
    position_y = Width / 2;
    canvas[position_x][position_y] = 1;
    int k;
    for(k = 0; k < EnemyNum; k++)
    {
        enemy_x[k] = rand()%2;
        enemy_y[k] = rand()%Width;
        canvas[enemy_x[k]][enemy_y[k]] = 3;
    }
    score = 0;
    BulletWidth = 0;
    EnemyMoveSpeed = 20;
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
                printf("*");                              //����ɻ�
            else if(canvas[i][j] == 2)
                printf("|");                              //����ӵ�
            else if(canvas[i][j] == 3)
                printf("@");                              //����л�
        }
        printf("\n");
    }
    printf("�÷֣�%d\n", score);
    Sleep(20);
}

void updateWithoutInput()                     //���û��޹صĸ���
{
    int i, j, k;
    for(i = 0; i < High; i++)
    {
        for(j = 0; j < Width; j++)
        {
            if(canvas[i][j] == 2)
            {
                for(k = 0; k < EnemyNum; k++)
                {
                    if((i == enemy_x[k]) && (j == enemy_y[k])) //�ӵ����зɻ�
                    {
                        score++;                          //�÷ּ�1
                        if (score % 5==0 && EnemyMoveSpeed > 3)   // �ﵽһ�����ֺ󣬵л����
                            EnemyMoveSpeed--;
                        if (score % 5==0)   // �ﵽһ�����ֺ��ӵ�������
                            BulletWidth++;
                        canvas[enemy_x[k]][enemy_y[k]] = 0;
                        enemy_x[k] = rand()%2;            //�����·ɻ�
                        enemy_y[k] = rand()%Width;
                        canvas[enemy_x[k]][enemy_y[k]] = 3;
                    }
                }
                //�ӵ������ƶ�
                canvas[i][j] = 0;
                if(i > 0)
                    canvas[i - 1][j] = 2;

            }
        }
    }

    static int speed = 0;
    if(speed < EnemyMoveSpeed)
        speed++;

    for(k = 0; k < EnemyNum; k++)
    {
        if((position_x == enemy_x[k]) && (position_y == enemy_y[k]))  //�л�ײ���һ�
        {
            printf("ʧ�ܣ�\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }
        if(enemy_x[k] > High)                  //�л��ܳ���Ļ��
        {
            canvas[enemy_x[k]][enemy_y[k]] = 0;
            enemy_x[k] = rand()%2;                    //�����µķɻ�
            enemy_y[k] = rand()%Width;
            canvas[enemy_x[k]][enemy_y[k]] = 3;
            system("pause");
            exit(0);
        }

        if(speed == EnemyMoveSpeed)
        {
            for(k = 0; k < EnemyNum; k++)
            {
                //�л�����
                canvas[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                speed = 0;
                canvas[enemy_x[k]][enemy_y[k]] = 3;
            }
        }
    }
}

void updateWithInput()                        //���û��йصĸ���
{
    char input;

    if(kbhit())                                 //�ж��Ƿ�������
    {
        input = getch();                             //�����û��Ĳ�ͬ�������ƶ�����������س�
        if(input == 'a' && position_y > 0)//λ������
        {
            canvas[position_x][position_y] = 0;
            position_y--;
            canvas[position_x][position_y] = 1;
        }
        else if(input == 'd' && position_y < Width - 1)//λ������
        {
            canvas[position_x][position_y] = 0;
            position_y++;
            canvas[position_x][position_y] = 1;
        }
        else if(input == 'w' && position_x > 0)//λ������
        {
            canvas[position_x][position_y] = 0;
            position_x--;
            position_y - BulletWidth;
            canvas[position_x][position_y] = 1;
        }
        else if(input == 's' && position_x < High - 1)//λ������
        {
            canvas[position_x][position_y] = 0;
            position_x++;
            canvas[position_x][position_y] = 1;
        }
        else if(input == ' ')//����
        {
            int left = position_y - BulletWidth;
            int right = position_y + BulletWidth;
            if(left < 0)
                left = 0;
            if(right > Width - 1)
                right = Width - 1;
            int k;
            for(k = left; k <= right; k++)
                canvas[position_x - 1][k] = 2;
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
