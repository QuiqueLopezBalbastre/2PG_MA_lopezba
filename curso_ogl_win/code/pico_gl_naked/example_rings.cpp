
#include <math.h>

// PicoGL include
#include "pico_gl_internal.h"
#include "raster.h"
#include "pico_gl.h"

#define PI 3.141592f

#define WINDOW_WIDTH   (800)
#define WINDOW_HEIGHT  (600)


static void DrawRing (PicoContext* ctx, float r0, float r1, bool reverse, float aoff)
{
  int i;
  const int kSegments = 20;
  for (i=0; i<kSegments; i++) {
    float a0 = (2.0f * PI * (float)i) / (float)kSegments;
    float a1 = (2.0f * PI * (float)(i + 1)) / (float)kSegments;
    a0 += aoff;
    a1 += aoff;
    float scx = 1.0f;
    float scy = ((float)WINDOW_WIDTH) / (float) WINDOW_HEIGHT; 
    Vec2 quad [4] = {
        {cosf(a0) * r1 * scx, sinf(a0) * r1 * scy},
        {cosf(a1) * r1 * scx, sinf(a1) * r1 * scy},
        {cosf(a1) * r0 * scx, sinf(a1) * r0 * scy},
        {cosf(a0) * r0 * scx, sinf(a0) * r0 * scy},
    };

    if (! reverse) {
      Vec2 tri0[3] = {quad [0], quad [1], quad [2]};
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), ctx, tri0);
      Vec2 tri1[3] = {quad [2], quad [3], quad [0]};
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), ctx, tri1);
    }
    else {
      Vec2 tri0[3] = {quad [0], quad [2], quad [1]};
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), ctx, tri0);
      Vec2 tri1[3] = {quad [2], quad [0], quad [3]};
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), ctx, tri1);
    }
  }
}

static float t = 0.0f;

int main (int argc, char** argv)
{
  picoglInit   (WINDOW_WIDTH, WINDOW_HEIGHT);

  picoglClearColor (0.0f, 0.0f, 1.0f, 1.0f);
  
  while (1) {
    picoglClear  ();
    
    PicoContext ctx0 = {
      .culling = kCullBack,
      .blend = kNoBlend,
      .color = 0xff00ff00,
    };

    DrawRing (&ctx0, 0.37f, 0.6f, false, t);

    PicoContext ctx1 = {
      .culling = kCullFront,
      .blend = kBlendSrcAlpha,
      .color = 0x80ff0000,
    };

    DrawRing (&ctx1, 0.56f, 0.7f, true, -t);
    
    picoglSwapBuffers ();

    t += 0.01f;
  }
  
  picoglQuit   ();
  
  return 1;
}
