

// Pico GL include
#include "picoGL.h"
#include "raster.h"

int main (int argc, char** argv)
{
  picoglInit   (800, 600);

  picoglClearColor (0.3f, 0.5f, 1.0f, 1.0f);
  
  while (1) {

    picoglClear  ();
        
    PicoContext ctx = {
      .culling = kCullFront,
      .blend = kNoBlend,
      .color = 0xff0000ff,
    };
    
    Vec2 tri [3] = {
      {100.0f, 100.0f},
      {200.0f, 300.0f},
      {500.0f, 500.0f},
    };
    
    DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), &ctx, tri);

    picoglSwapBuffers  ();
  }
  
  picoglQuit   ();
  
  return 1;
}
