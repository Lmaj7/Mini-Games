#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define HEI 28
#define WID 100


int cells[HEI][WID];
int newcells[HEI][WID];

void gotoxy(int x, int y);
void init(void);

void draw(void);

void update(void);


int main(){
    init();
    while(1){
        draw();
        update();
        Sleep(30);
    }
    return 0;
}


void init(void){
    int i,j;
    
    srand((unsigned)time(NULL));
    
    for(i=0;i<HEI;i++){
        for(j=0;j<WID;j++){
            cells[i][j] = rand()%2;
        }
    }
}


void draw(void){
    static int i,j;

    gotoxy(0, 0);

    for(i=0;i<HEI;i++){
        for(j=0;j<WID;j++){
            if(cells[i][j])
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}


void update(){
    static int i,j,tmp;
    
    for(i=1;i<=HEI+1;i++){
        for(j=1;j<=WID+1;j++){
            tmp = cells[i-1][j-1] + cells[i-1][j] + cells[i-1][j+1] + cells[i][j-1] + cells[i][j+1] + cells[i+1][j-1] + cells[i+1][j] + cells[i+1][j+1];
            if(tmp==3)
                newcells[i][j] = 1;
            else if(tmp==2)
                newcells[i][j] = cells[i][j];
            else
                newcells[i][j] = 0;
        }
    }

    memcpy(cells, newcells, sizeof(cells));
    
}


void gotoxy(int x, int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
