//Name: Guadalupe Nunez
//Date: December 03, 2018
//Individual File
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"

using namespace std;
/*
class Timer {
    public:
    unsigned int sec;
    unsigned int milisec;
    unsigned int total;
    unsigned countDown;
    
    int startTime;
    int countTime;
    int downTime;
    Timer() {
    sec = 0;
    total = 0;
    countDown = 0;
    
    startTime = 100;
    countTime = 0;
    downTime = 100;
    Rect r;
    c = 0x0027c1ee;
    r.bot = y-50;
    r.left = x-900;
    r.center = 0;
    }
}time
*/
void showLupeName(int x, int y)
{
	Rect r;
    unsigned int c = 0x0027c1ee;
    r.bot = y;
    r.left = x-30;
    r.center = 0;
    ggprint8b(&r, 20, c, "Guadalupe Nunez");

}

void showLupePicture(int x, int y, GLuint texid)
{
    int wid = 40;
    static float angle = 0.0f;


    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 0.05);
    angle += 1.0;
    glTranslatef(x,y,0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();

    glPopMatrix();
    return;
}

void showHealth(int x, int y)
{
    Rect r;
    unsigned int c = 0x0027c1ee;
    r.bot = y-30;
    r.left = x-780;
    r.center = 0;

    int player1hp = 100;
    int player2hp = 100;
    int damage = 0;


    if(player1hp == 0) {
        ggprint8b(&r, 20, c, "Player 1 HP = %d", player1hp);
        ggprint8b(&r, 20, c, "Player 2 HP = %d", player2hp);
        ggprint8b(&r, 20, c, "PLAYER 2 WINS!!");
    }
    else if (player2hp == 0) {
        ggprint8b(&r, 20, c, "Player 1 HP = %d", player1hp);
        ggprint8b(&r, 20, c, "Player 2 HP = %d", player2hp);
        ggprint8b(&r, 20, c, "PLAYER 1 WINS!!");
    }
    else {
        ggprint8b(&r, 20, c, "Player 1 HP = %d", player1hp);
        ggprint8b(&r, 20, c, "Player 2 HP = %d", player2hp);
        ggprint8b(&r, 20, c, "Damage... %d", damage);
    } 
}
/*
void showTimer(int x, int y,int timeLeft)
{
    if (timeLeft !=0) {
        if (timeLeft == 100) {

        

    startTime = clock();
    timeLeft = downTime - sec;
        }

    //while (timeLeft > 0) {
       countTime = clock();
        milisec = countTime - startTime;
        sec = (milisec/(CLOCKS_PER_SEC));
        if(timeLeft!= downTime - sec) {
            timeLeft = downTime - sec;
            ggprint8b(&r, 20, c, "Remaining time: %d\n", timeLeft);
        }

       // continue;
   // }
    }
   if(timeLeft = 0) 
       ggprint8b(&r, 20, c, "TIME'S OUT!");

    return;
}
*/


