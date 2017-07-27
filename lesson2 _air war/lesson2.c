#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<math.h>

#define WID 80
#define HEI  25

#define numOfEnems 7
#define numOfBullets 10
#define difficulty 5


char airCraft[][3][4]={
    {
        " * ",
        "***",
        "* *"
    },
    {
        "* *",
        "***",
        " * "
    }
};

typedef struct{
    int x;
    int y;
} coor;

typedef struct{
    coor pos;
    char isbullet;
} bul;


coor craftPos;
bul  bullet[numOfBullets];
coor enemyPos[numOfEnems];

unsigned int score;
int smash;


void init(void);
void refresh(void);
void fetchInput(void);
void dataUpdate(void);
void updateBullet(void);
void updateEnemies(void);
void fire(void);

void spawn(int i);
int  spawnDetect(int x);
void hitDetect(void);

void drawAirCraft(int type);
void drawBullets(void);

void gotoxy(int x, int y);


int main(){
    init();
    while(1){
        dataUpdate();
        refresh();
        fetchInput();
        Sleep(50);
    }
    return 0;
}


void init(void){
    int i;
    
    /* Hide Cursor */
    CONSOLE_CURSOR_INFO cursor_info = {0, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    
    srand((unsigned)time(NULL));

    /* Init of player's craft */
    craftPos.x = WID / 2;
    craftPos.y = HEI - 3;

    /* Init of Enemies */
    for(i=0;i<numOfEnems;i++)
        spawn(i);

    score = 0;
    smash = 0;

    for(i=0;i<numOfBullets;i++)
        bullet[i].isbullet = 0;
}


void drawAirCraft(int type){
    static int i,j;
    
    for(i=0;i<3;i++){
        if(type){
            for(j=0;j<numOfEnems;j++){
                gotoxy(enemyPos[j].x,enemyPos[j].y+i);
                printf("%s",airCraft[type][i]); 
            }
        } else {
            gotoxy(craftPos.x,craftPos.y+i);
            printf("%s",airCraft[type][i]);
        }
    }

}


void drawBullets(void){
    static int i;
    
    for(i=0;i<numOfBullets;i++){
        if(bullet[i].isbullet){
            gotoxy(bullet[i].pos.x, bullet[i].pos.y);
            printf("|");
        }
    }
}


void dataUpdate(void){
    
    updateBullet();
    updateEnemies();
    hitDetect();
    
}


void hitDetect(void){
    static int i,j;
    int distTmp;
    
    for(i=0;i<numOfEnems;i++){
        for(j=0;j<numOfBullets;j++){
            distTmp = bullet[j].pos.x-enemyPos[i].x;
            if( (distTmp <= 2) && (distTmp >= 0) && bullet[j].pos.y == enemyPos[i].y ){
                smash = i;
                spawn(i);
                smash = 0;
                score++;
                bullet[j].isbullet = 0;
            }
        }
    }
    
}


void updateBullet(void){
    static int i;
    for(i=0;i<numOfBullets;i++){
        if(bullet[i].isbullet)
            bullet[i].pos.y--;
        if(bullet[i].pos.y <= 0)
            bullet[i].isbullet=0;
    }
}


void updateEnemies(void){
    static int i;
    static char diff = 10 - difficulty;
    static int ref = 0;

    if( (diff - ref) == 0 ){
        ref = 0;
        for(i=0;i<numOfEnems;i++){
            enemyPos[i].y++;
            if(enemyPos[i].y > HEI - 2)
                spawn(i);
        }
    }

    ref++;
}


void fire(void){
    static int earlist = 0;
    
    if(earlist == numOfBullets)
        earlist = 0;
    
    bullet[earlist].pos.x = craftPos.x + 1;
    bullet[earlist].pos.y = craftPos.y;
    bullet[earlist].isbullet = 1;
    
    earlist++;
}


void spawn(int x){
    double tx;

    enemyPos[x].y = 0;  

    do{
        tx = (double)rand() / RAND_MAX;
        enemyPos[x].x = (int)(tx * WID-3);  
    } while(spawnDetect(x));
}


int spawnDetect(int x){
    static int i;
    
    for(i=0;i<numOfEnems;i++){
        if(i == x)
            continue;
        if( (enemyPos[i].x - enemyPos[x].x >= 0)&&(enemyPos[i].x - enemyPos[x].x <= 3) )
            return 1;
        else
            continue;
    }
    return 0; 
}


void refresh(void){
    system("cls");
    
    drawAirCraft(0);
    drawAirCraft(1);
    drawBullets();
    
    gotoxy(0,HEI+1);
    
    printf("\nScore: %d\n",score);
}


void fetchInput(void){
    static char kb;
    if(kbhit()){
        kb=getch();
        switch(kb){
            case 'a':
            case 'A':
                craftPos.x--;
                break;
            case 'd':
            case 'D':
                craftPos.x++;
                break;
            case 'w':
            case 'W':
                craftPos.y--;
                break;
            case 's':
            case 'S':
                craftPos.y++;
                break;
            case ' ':
                fire();
                break;
        }
        if(craftPos.x <= 0)
            craftPos.x = 0;
        if(craftPos.x >= WID)
            craftPos.x = WID;
        if(craftPos.y <= 0)
            craftPos.y = 0;
        if(craftPos.y + 3 >= HEI)
            craftPos.y = HEI-3;
    }
}


void gotoxy(int x, int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
