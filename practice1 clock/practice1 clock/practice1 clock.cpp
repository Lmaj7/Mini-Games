/* this program is using EasyX to draw all the elements of the clock */

#include "stdafx.h"
#include "graphics.h"
#include "conio.h"
#include "math.h"

const double PI = 3.14159265;
const int WID = 640;
const int HEI = 480;

typedef struct {
    int x;
    int y;
} coor;

typedef struct {
    int rho;
    double theta;
} polar;

const int RADIUS = WID > HEI ? HEI / 2 : WID / 2; 
const coor CEN = { WID / 2,HEI / 2 };


void drawInit(void);
void drawWidget(void);
void drawHands(void);
coor polarToOrth(polar x, coor center);


int main() {
    drawInit();

    while (1) {
        drawHands();
    }

    closegraph();

    return 0;
}


void drawInit(void) {
    initgraph(WID, HEI);
    setwritemode(R2_XORPEN);

    drawWidget();
}


void drawWidget(void) {
    polar widget1, widget2;
    coor tar1, tar2;
    int i;
    int length = 20;

    setlinecolor(0xdddddd);
    setlinestyle(PS_SOLID, 4, NULL);

    /* draw the dial gauge of the clock */
    for (i = 0; i < 12; i++) {
        widget1.rho = RADIUS;
        widget1.theta = widget2.theta = i*PI / 6;
        widget2.rho = RADIUS - length;
        
        tar1 = polarToOrth(widget1, CEN);
        tar2 = polarToOrth(widget2, CEN);

        line(tar1.x, tar1.y, tar2.x, tar2.y);
    }

    setlinecolor(0xcccccc);
    setlinestyle(PS_SOLID, 2, NULL);
    circle(WID / 2, HEI / 2, RADIUS);

    outtextxy(CEN.x - 20, CEN.y, _T("Major"));
}


void drawHands(void) {
    static const int lengthH = 70;
    static const int lengthM = 150;
    static const int lengthS = RADIUS - 50;
    int i;

    polar H1, M1, S1, H2, M2, S2;
    coor H1O, M1O, S1O, H2O, M2O, S2O;
    static SYSTEMTIME time;

    GetLocalTime(&time);

    /* the first parentheses calculate the position of the hands
       And the second one calculate the accurate position */
    H1.rho = RADIUS;
    H1.theta = H2.theta = (time.wHour % 12 * PI / 6 - PI / 2) + (time.wMinute * PI / 360); //360 for 2PI / 60 / 12
    H2.rho = RADIUS - lengthH;

    M1.rho = RADIUS;
    M1.theta = M2.theta = (time.wMinute * PI / 30 - PI / 2) + (time.wSecond * PI / 1800); //1800 for 2PI / 60 / 12 / 5 
    M2.rho = RADIUS - lengthM;

    S1.rho = RADIUS;
    S1.theta = S2.theta = time.wSecond * PI / 30 - PI / 2;
    S2.rho = RADIUS - lengthS;

    H1O = polarToOrth(H1, CEN);
    H2O = polarToOrth(H2, CEN);
    M1O = polarToOrth(M1, CEN);
    M2O = polarToOrth(M2, CEN);
    S1O = polarToOrth(S1, CEN);
    S2O = polarToOrth(S2, CEN);


    /* keep the hands for a second
       and then clear the hands */
    for (i = 0; i < 2; i++) {
        setlinecolor(0xdddddd);
        setlinestyle(PS_SOLID, 10, NULL);
        line(H1O.x, H1O.y, H2O.x, H2O.y);

        setlinecolor(0xbbbbbb);
        setlinestyle(PS_SOLID, 6, NULL);
        line(M1O.x, M1O.y, M2O.x, M2O.y);

        setlinecolor(0x999999);
        setlinestyle(PS_SOLID, 1, NULL);
        line(S1O.x, S1O.y, S2O.x, S2O.y);

        if(i==0)
            Sleep(1000);
    }
}


coor polarToOrth(polar in, coor center) {
    coor tmp;
    tmp.x = (int)in.rho*cos(in.theta) + center.x;
    tmp.y = (int)in.rho*sin(in.theta) + center.y;
    return tmp;
}
