//Name: Guadalupe Nunez
//Date: October 02, 2018
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


