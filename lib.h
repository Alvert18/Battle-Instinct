//Main header libraries
//
//

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

//defined types
typedef double Flt;
typedef double Vec[3];
typedef Flt     Matrix[4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)     ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                      (c)[1]=(a)[1]-(b)[1]; \
                      (c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define ALPHA 1


class Image { 
public: 
        int width, height; 
        unsigned char *data; 
        ~Image() { delete [] data; } 
        Image(const char *fname) { 
                if (fname[0] == '\0') 
                        return; 
                //printf("fname **%s**\n", fname); 
                char name[40]; 
                strcpy(name, fname); 
                int slen = strlen(name); 
                name[slen-4] = '\0'; 
                //printf("name **%s**\n", name); 
                char ppmname[80]; 
                sprintf(ppmname,"%s.ppm", name); 
                //printf("ppmname **%s**\n", ppmname); 
                char ts[100]; 
                //system("convert eball.jpg eball.ppm"); 
                sprintf(ts, "convert %s %s", fname, ppmname); 
                system(ts); 
                //sprintf(ts, "%s", name); 
                FILE *fpi = fopen(ppmname, "r"); 
                if (fpi) { 
                        char line[200]; 
                        fgets(line, 200, fpi); 
                        fgets(line, 200, fpi); 
                        while (line[0] == '#') 
                                fgets(line, 200, fpi); 
                        sscanf(line, "%i %i", &width, &height); 
                        fgets(line, 200, fpi); 
                        //get pixel data 
                        int n = width * height * 3; 
                        data = new unsigned char[n]; 
                        for (int i=0; i<n; i++) 
                                data[i] = fgetc(fpi); 
                        fclose(fpi); 
                } else { 
                        printf("ERROR opening image: %s\n",ppmname); 
                        exit(0); 
                } 
                unlink(ppmname); 
        } 
}; 
Image img[5] = { 
    "./images/Kang-Walk.gif", 
    "./images/dog.jpg", 
    "./images/bunny.png",
   "./images/MainMenu.png",
   "./images/Tutorial.jfif", 
}; 
//--------------------------------------------------------------------------------------------


class Global {
public:
        int done;
        int xres, yres;
        int walk;
        bool credits = false;
        int walkFrame;
        double delay;
        //Booleans
//      bool inMainMenu = true;
//      bool inGame = false;
        GLuint walkTexture;
        GLuint sergioTexture;
        GLuint guadalupeTexture;
        GLuint MainMenuTexture;
	GLuint TutorialTexture;
        Vec box[20];
        Global() {
                done=0;
                xres=800;
                yres=600;
                walk=0;
                walkFrame=0;
                delay = 0.1;
                for (int i=0; i<20; i++) {
                        box[i][0] = rnd() * xres;
                        box[i][1] = rnd() * (yres-220) + 220.0;
                        box[i][2] = 0.0;
                }
        }
} g;
//--------------------------------------------------------------------------------------------

class X11_wrapper {
private:
        Display *dpy;
        Window win;
public:
        X11_wrapper() {
                GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
                //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
                XSetWindowAttributes swa;
                setupScreenRes(g.xres, g.yres);
                dpy = XOpenDisplay(NULL);
                if (dpy == NULL) {
                        printf("\n\tcannot connect to X server\n\n");
                        exit(EXIT_FAILURE);
                }
                Window root = DefaultRootWindow(dpy);
                XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
                if (vi == NULL) {
                        printf("\n\tno appropriate visual found\n\n");
                        exit(EXIT_FAILURE);
                }
                Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
                swa.colormap = cmap;
                swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                                                        StructureNotifyMask | SubstructureNotifyMask;
                win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,
                                                                vi->depth, InputOutput, vi->visual,
                                                                CWColormap | CWEventMask, &swa);
                GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
                glXMakeCurrent(dpy, win, glc);
                setTitle();
        }
        ~X11_wrapper() {
                XDestroyWindow(dpy, win);
                XCloseDisplay(dpy);
        }
        void setTitle() {
                //Set the window title bar.
                XMapWindow(dpy, win);
                XStoreName(dpy, win, "Walk Cycle");
        }
        void setupScreenRes(const int w, const int h) {
                g.xres = w;
                g.yres = h;
        }
        void reshapeWindow(int width, int height) {
                //window has been resized.
                setupScreenRes(width, height);
                glViewport(0, 0, (GLint)width, (GLint)height);
                glMatrixMode(GL_PROJECTION); glLoadIdentity();
                glMatrixMode(GL_MODELVIEW); glLoadIdentity();
                glOrtho(0, g.xres, 0, g.yres, -1, 1);
                setTitle();
        }
        void checkResize(XEvent *e) {
                //The ConfigureNotify is sent by the
                //server if the window is resized.
                if (e->type != ConfigureNotify)
                        return;
                XConfigureEvent xce = e->xconfigure;
                if (xce.width != g.xres || xce.height != g.yres) {
                        //Window size did change.
                        reshapeWindow(xce.width, xce.height);
                }
        }
        bool getXPending() {
                return XPending(dpy);
        }
        XEvent getXNextEvent() {
                XEvent e;
                XNextEvent(dpy, &e);
                return e;
        }
        void swapBuffers() {
                glXSwapBuffers(dpy, win);
        }

} x11;

