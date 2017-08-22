#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

GC                      gc;
 
int main(int argc, char *argv[]) 
{
  unsigned long black, white;
  dpy = XOpenDisplay(NULL);
  
  if(dpy == NULL) {
    printf("\n\tcannot connect to X server\n\n");
    exit(0);
  }
         
  root = DefaultRootWindow(dpy);
  black = BlackPixel(dpy, DefaultScreen(dpy));
  white = WhitePixel(dpy, DefaultScreen(dpy));
 
  vi = glXChooseVisual(dpy, 0, att);
 
  if(vi == NULL) {
    printf("\n\tno appropriate visual found\n\n");
    exit(0);
  } 
  else {
    printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
  }
 
 
  cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
  swa.colormap = cmap;
  swa.event_mask = ExposureMask | KeyPressMask;
  swa.override_redirect = True;
  swa.background_pixel = white;
  XGetWindowAttributes(dpy, root, &gwa);
  win = XCreateWindow(dpy, root, 0, 0, gwa.width, gwa.height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel|CWColormap|CWEventMask|CWOverrideRedirect, &swa);

  ///////////////////////////////////////////////////////// 
  gc = XCreateGC(dpy, win, 0, NULL);
  XSetBackground(dpy, gc, white);
  XSetBackground(dpy, gc, black);
  XClearWindow(dpy, win);
  ///////////////////////////////////////////////////////// 

  XMapWindow(dpy, win);
  
  glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
  glXMakeCurrent(dpy, win, glc);
  glEnable(GL_DEPTH_TEST); 
  
  while(1) 
  {
    XNextEvent(dpy, &xev);
    if(xev.type == Expose) {

    }
    else if(xev.type == KeyPress) {
      glXMakeCurrent(dpy, None, NULL);
      glXDestroyContext(dpy, glc);
      XDestroyWindow(dpy, win);
      XCloseDisplay(dpy);
      exit(0);
    }
  } /* this closes while(1) { */
} 
