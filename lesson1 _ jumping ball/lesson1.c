//lesson 1

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main(){
    int i, j; 
    int x = 5;
    int y = 10;
    int hight = 20;
    int velocity = 1;
    
    while(1){
        x = x + velocity;

        system("cls");
        
        for(i=0;i<x;i++)
               printf("\n");
        for(j=0;j<y;j++)
                printf(" ");
        printf("o");
        printf("\n");
    
        if((x == hight)||(x==0))
            velocity = -velocity;
        Sleep(50);
    }
    return 0;
}
