

// PicoGL include
#include "pico_gl_internal.h"
#include "raster.h"
#include "pico_gl.h"


int main (int argc, char** argv)
{
  picoglInit   (800, 600);

  picoglClearColor (0.3f, 0.5f, 1.0f, 1.0f);
  
  while (1) {

    picoglClear  ();
        
    PicoContext ctx = {
      .culling = kCullBack,
      .blend = kNoBlend,
      .color = 0xff0000ff,
    };
    
    Vec2 tri [3] = {
      {-0.75f, 0.66f},
      {-0.5f,  0.0f},
      {0.25f,  -0.66f},
    };
    
    
    DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), &ctx, tri);

    picoglSwapBuffers ();
  }
  
  picoglQuit   ();
  
  return 1;
}
