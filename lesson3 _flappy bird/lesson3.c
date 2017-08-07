#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define WID 100
#define HEI 30
#define numOfwall 5

typedef struct{
    int x;
    int y;
    int vx;
    int vy;
    int ax;
    int ay;
} coor;

typedef struct{
    int x;
    int top;
    int length;
    int isDisp;
} barr;

coor bird;
barr wall[numOfwall];

int  score;
char playing;


void gotoxy(int x, int y);
void init(void);

void fetchInput(void);
void birdJump(void);

void draw(void);
void drawBird(void);
void drawWall(void);

void wallSpawner(int n);

void update(void);
void updateBird(void);
void updateWall(void);
void updateCrash(void);

void gameover(void);


int main(){
    init();
    while(playing){
        draw();
        update();
        Sleep(50);
    }
    gameover();
    
    return 0;
}


void init(void){
    bird.x = 2;
    bird.y = HEI/2;
    bird.vx= 0;
    bird.vy= 0;
    bird.ax= 0;
    bird.ay= 1;
    
    score  = 0;
    playing= 1;

    srand((unsigned)time(NULL));
}


void birdJump(void){
    bird.y -= 2;
    bird.vy = -5;
}


void wallSpawner(int n){
    double tmp;
    static int last=0;
    if( rand() < (int)(RAND_MAX-(RAND_MAX/100)) )
        return;
    if( (WID - wall[last].x) <= 20 )
        return;

    if(!wall[n].isDisp){
        wall[n].x = WID;
        tmp = (double)rand()/RAND_MAX;
        wall[n].top = (int)(tmp * HEI);
        tmp = (double)rand()/RAND_MAX;
        wall[n].length = (int)(tmp * (HEI-wall[n].top));

        if(wall[n].top>=HEI-8)
            wall[n].top = HEI-10;
        if(wall[n].length <= 8)
            wall[n].length = 8;

        wall[n].isDisp = 1;

        last = n;
    }
}


void draw(void){
    system("cls");
    drawBird();
    drawWall();
    gotoxy(0, HEI+1);
    printf("score: %d",score);
}


void drawBird(void){
    gotoxy(bird.x, bird.y);
    if(bird.vy > 0)
        printf("@");
    if(bird.vy <= 0)
        printf("O");
}


void drawWall(void){
    static int i,j;
    for(i=0;i<numOfwall;i++){
        if(wall[i].isDisp){
            for(j=0;j<wall[i].top;j++){
                gotoxy(wall[i].x, j);
                printf("|");
            }
            /* the crack of the wall */
            for(j=wall[i].length+wall[i].top;j<HEI;j++){
                gotoxy(wall[i].x, j);
                printf("|");
            }
        }
    }
}


void update(void){
    fetchInput();
    updateBird();
    updateWall();
    updateCrash();
}

void updateBird(void){
    bird.vx += bird.ax;
    bird.vy += bird.ay;
    bird.x  += bird.vx;
    bird.y  += bird.vy;
    if(bird.y <= 0)
        bird.y = 0;
    if(bird.y >= HEI)
        playing=0;
}


void updateWall(void){
    static int i;
    for(i=0;i<numOfwall;i++){
        wall[i].x--;
        if(wall[i].x<=0)
            wall[i].isDisp = 0;
            wallSpawner(i);
    }
}


void updateCrash(void){
    static int i;
    for(i=0;i<numOfwall;i++){
        if(bird.x == wall[i].x){
            if( (bird.y <= wall[i].top) || (bird.y >= (wall[i].top + wall[i].length)) )
                playing = 0;
            score++;
        }
    }
}


void fetchInput(void){
    static char kb;
    if(kbhit()){
        kb = getch();
        switch(kb){
            case ' ':
                birdJump();
            break;
        }
    }
}


void gotoxy(int x, int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}


void gameover(void){
    system("cls");
    gotoxy((WID/2)-5, HEI/2);
    printf("Game Over");
}
