//X11 header file/ declaration
//

#include "global.h"
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

