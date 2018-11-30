/*
 * Alberto Acevedo
 * date: 9/25/2018
 * Individual file for:
 * - Showing credits
 * - Showing picture in credits
 */
#include <math.h>
#include <GL/glx.h>
#include "fonts.h"
#include "img.h"
#include "lib.h"
using namespace std;



Image fighter_stance = "./images/Kang-Walk.gif";

class Fighter {
    public:
	GLuint stance;
	int width;
	int height;
	Vec pos;
	Vec vel;
	Vec lastpos;
	Fighter() {}
}fighter;


//Write name on the credit screen
void show_credits_Alberto (int x, int y)
{
    Rect r;
    unsigned int c = 0x0027c1ee;
    r.bot = y;
    r.left = x-30;
    r.center = 0;
    ggprint8b(&r, 20, c, "Alberto Acevedo");

}

//Post picture on the credit screen
void showAlbertoPicture (int x, int y,float tx, float ty, GLuint texid) 
{
    int wid = 40;
    static float fx = 0.0f;
    static float angle = 0.0f;

    angle += 0.01;
    fx = sin(angle);
    y = y -40;

    glPushMatrix();
    glTranslatef(x + (int)(fx*30.0),y,0);
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2f(tx, ty+.5);     glVertex2i(-wid, -wid);
    glTexCoord2f(tx, ty);        glVertex2i(-wid, wid);
    glTexCoord2f(tx+.125,ty);    glVertex2i(wid, wid);
    glTexCoord2f(tx+.125,ty+.5); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void init_fighters() {

    //Initialization
    int width = fighter_stance.width;
    int height = fighter_stance.height;
    //Texture elements
    glGenTextures(1, &fighter.stance);

    //stance
    glBindTexture(GL_TEXTURE_2D, fighter.stance);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
	    GL_RGB, GL_UNSIGNED_BYTE, fighter_stance.data);
    unsigned char *StanceData = buildAlphaData(&fighter_stance);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, StanceData);
}


void render_fighters(int walkFrame, int cy, int cx, Vec pos ) {

    
    float h = 200.0;
    float w = h * 0.5;
    glPushMatrix();
    glTranslatef(pos[0],0,pos[2]);
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, fighter.stance);
    //
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = walkFrame % 7;
    int iy = 0;
    if (walkFrame >= 7)
	iy = 1;
    int tx = (float)ix / 7.0;
    int ty = (float)iy / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+1); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,      ty);    glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx+.1, ty);    glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx+.1, ty+1); glVertex2i(cx+w, cy-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);


}
