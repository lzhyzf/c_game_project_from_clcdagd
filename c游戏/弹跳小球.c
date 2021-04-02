#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    int i, j;
    int x = 0;
    int y = 5;

    int top = 0, bottom = 10, left = 0, right = 20;
    int velocity_x = 1, velocity_y = 1;

    while(1)
    {
        x += velocity_x;
        y += velocity_y;

        system("cls");                     //ÇåÆÁº¯Êý
        for(i = 0; i < x; i++)
            printf("\n");
        for(j = 0; j < y; j++)
            printf(" ");
        printf("o");
        printf("\n");
        Sleep(50);

        if(x == top || x == bottom){
            velocity_x = -velocity_x;
            printf("\a");
        }
        if(y == left || y == right){
            velocity_y = -velocity_y;
            printf("\a");
        }
    }
    return 0;
}
