#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    int i, j;
    int x = 5, y =10;
    char input;
    int isFire = 0;
    int ny = 5;                                //一个靶子，放在第一行ny列上
    int isKilled = 0;

    while(1)
    {
        system("cls");                     //清屏函数

        if(!isKilled)                      //打印靶子
        {
            for(j = 0; j < ny; j++)
                printf(" ");
            printf("+\n");
        }
        if(isFire == 0)                    //未开火，打印飞机上面空行
        {
            for(i = 0; i < x; i++)
                printf("\n");
        }
        else                               //开火，打印激光
        {
            for(i = 0; i < x; i++)
            {
                for(j = 0; j < y; j++)
                    printf(" ");
                printf("  |\n");
            }
            if(y + 2 == ny)                //激光和靶子在一列上，隐藏靶子
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

        if(kbhit())                               //判断是否有输入
        {
            input = getch();                      //判断用户的不同输入来移动，不必输入回车
            if(input == 'a')                      //左移
                y--;
            if(input == 'w')                      //上移
                x--;
            if(input == 's')                      //下移
                x++;
            if(input == 'd')                      //右移
                y++;
            if(input == ' ')                      //开火
                isFire = 1;
        }
    }
    return 0;
}
