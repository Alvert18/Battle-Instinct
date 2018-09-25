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


