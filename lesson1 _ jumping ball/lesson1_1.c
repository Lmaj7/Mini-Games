/* lesson 1 with accelerated velocity */

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define numOfBalls 10
#define HEI 30
#define WID 50

typedef struct{
    int x;
    int y;
    int vx;
    int ax;
    int vy;
    int ay;
} obj;

obj ball;

void update(void);
void init(void);
void draw(void);
void gotoxy(int x, int y);

int main(){
    
    init();
    while(1){
        draw();
        update();
        Sleep(50);
    }
    
    
}

void init(void){
    /* Hide Cursor */
    CONSOLE_CURSOR_INFO cursor_info = {0, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    
    ball.x = WID / 2;
    ball.y = 0;
    ball.vx= 0;
    ball.vy= 0;
    ball.ax= 0;
    ball.ay= 1;
}

void update(void){
    ball.vx += ball.ax;
    ball.x  += ball.vx;
    ball.vy += ball.ay;
    ball.y  += ball.vy;
    
    if(ball.x <= 0){
        ball.vx = -ball.vx;
        ball.x  = -ball.x;
    }
    if(ball.x >= WID){
        ball.vx = -ball.vx;
        ball.x  = 2 * WID - ball.x;
    }
    if(ball.y <= 0){
        ball.vy = -ball.vy;
        ball.y  = -ball.y;
    }
    if(ball.y >= HEI){
        ball.vy = -ball.vy;
        ball.y  = 2 * HEI - ball.y;
    }

}

void draw(void){
    system("cls");
    gotoxy(ball.x, ball.y);
    printf("o");
}

void gotoxy(int x, int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
