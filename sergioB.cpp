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
	


