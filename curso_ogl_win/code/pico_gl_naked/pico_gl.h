
#ifndef _PICOGL_H_
#define _PICOGL_H_

void picoglInit         (int w, int h);
void picoglQuit         ();
void picoglClearColor   (float r, float g, float b, float a);
void picoglClear        ();

void picoglSwapBuffers  ();


// Hackish bridge; only valid after Init call
void* picoglGetFramebuffer ();

#endif 


