#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    int i, j;
    int x = 5, y =10;
    char input;
    int isFire = 0;
    int ny = 5;                                //һ�����ӣ����ڵ�һ��ny����
    int isKilled = 0;

    while(1)
    {
        system("cls");                     //��������

        if(!isKilled)                      //��ӡ����
        {
            for(j = 0; j < ny; j++)
                printf(" ");
            printf("+\n");
        }
        if(isFire == 0)                    //δ���𣬴�ӡ�ɻ��������
        {
            for(i = 0; i < x; i++)
                printf("\n");
        }
        else                               //���𣬴�ӡ����
        {
            for(i = 0; i < x; i++)
            {
                for(j = 0; j < y; j++)
                    printf(" ");
                printf("  |\n");
            }
            if(y + 2 == ny)                //����Ͱ�����һ���ϣ����ذ���
                isKilled = 1;
            isFire = 0;
        }
        for(j = 0; j < y; j++)
            printf(" ");
        printf("  *\n");
        for(j = 0; j < y; j++)
            printf(" ");
        printf("*****\n");
        for(j = 0; j < y; j++)
            printf(" ");
        printf(" * * \n");

        if(kbhit())                               //�ж��Ƿ�������
        {
            input = getch();                      //�ж��û��Ĳ�ͬ�������ƶ�����������س�
            if(input == 'a')                      //����
                y--;
            if(input == 'w')                      //����
                x--;
            if(input == 's')                      //����
                x++;
            if(input == 'd')                      //����
                y++;
            if(input == ' ')                      //����
                isFire = 1;
        }
    }
    return 0;
}
