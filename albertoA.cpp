//Alberto Acevedo
//date: 9/25/2018
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"
#include <string>

using namespace std;


void show_credits_Alberto (int x, int y)
{
    Rect r;
    unsigned int c = 0x0027c1ee;
    r.bot = y;
    r.left = x-30;
    r.center = 0;
    ggprint8b(&r, 20, c, "Alberto Acevedo");

}

void show_credits_Alberto_pic (int x, int y,float tx, float ty, GLuint texid) 
{
     
     int wid =40;
     y = y -40;
     glPushMatrix();
     glTranslatef(x+100,y+40,0);
     glColor3f(1.0, 1.0, 1.0);
     glBindTexture(GL_TEXTURE_2D, texid);
     glBegin(GL_QUADS);
        glTexCoord2f(tx, ty+.5); glVertex2i(-wid, -wid);
        glTexCoord2f(tx, ty);    glVertex2i(-wid, wid);
        glTexCoord2f(tx+.125,ty);    glVertex2i(wid, wid);
        glTexCoord2f(tx+.125,ty+.5); glVertex2i(wid, -wid);
     glEnd();
     glPopMatrix();
     glBindTexture(GL_TEXTURE_2D, 0);
     glDisable(GL_ALPHA_TEST);


}
