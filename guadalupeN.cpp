//Name: Guadalupe Nunez
//Date: October 02, 2018
//
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
#include "log.h"
#include "fonts.h"

using namespace std;

void showLupeName(int x, int y)
{
	Rect r;
    unsigned int c = 0x0027c1ee;
    r.bot = y-50;
    r.left = x-30;
    r.center = 0;
    ggprint8b(&r, 20, c, "Guadalupe Nunez");

}

