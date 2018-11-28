//Sergio Benavides
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

extern int selected;

void show_credits_Sergio (int x, int y)
{
    Rect r;
    unsigned int c = 0x0027c1ee;
    r.bot = y;
    r.left = x-30;
    r.center = 0;
    ggprint8b(&r, 20, c, "Sergio Benavides");

}

void showSergioPicture(int x, int y, GLuint texid)
{
    int wid=40;
    static float fx = 0.0f;
    static float angle = 0.0f;
    static float angle2 = 0.0f;

    angle += 0.2;
    fx = sin(angle);
    glPushMatrix();
    glTranslatef(x + (int)(fx*20.0), y, 0);
    glBindTexture(GL_TEXTURE_2D, texid);
  /*  glBegin(GL_QUADS);
    	glTexCoord2f(tx, ty+.5); glVertex2i(-wid, -wid);
        glTexCoord2f(tx, ty); glVertex2i(-wid, wid);
        glTexCoord2f(tx+.125, ty); glVertex2i(wid, wid);
        glTexCoord2f(tx+.125, ty+.5); glVertex2i(wid, -wid);
    glEnd();
    */
     glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
                glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
                glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
                glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
          glEnd();

    
    glPopMatrix();
      return;
}
bool inMainMenu = true;
bool inGame = false;

void showMainMenu(int x, int y, GLuint MainMenuTexture) 
{

    int px, py;

    float w = x;
    float h = y;
    glPushMatrix();
    glTranslatef(600, 800, 0);
    glBindTexture(GL_TEXTURE_2D, MainMenuTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i( -w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( -w, -h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( w,  -h);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(w, h);
    glEnd();
    glPopMatrix();
    Rect r;

    //unsigned int c = 0x0027c1ee;
    unsigned int c = 0x00ffffff;
    r.bot = y - 400;
    r.left = x/2 - 45;
    r.center = 0;
    ggprint12(&r, 20, c, "Start");
    ggprint12(&r, 20, c, "Tutorial");

    Rect r2;
    r2.bot = y - 400;
    r2.left = x/2 - 45;
    r2.center = 0;

    if (selected == 1) {
	px = x/2 - 73;
	py = y - 390;
	ggprint12(&r2, 20, 0xFF0000, "Start");
    } else if (selected == 2) {
	px = x/2 - 73;
        py = y - 407;	
	ggprint12(&r2, 20, 0xFF0000, " ");
	ggprint12(&r2, 20, 0xFF0000, "Tutorial");
    }

}

