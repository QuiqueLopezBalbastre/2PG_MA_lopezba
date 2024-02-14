

// PicoGL include
#include "pico_gl_internal.h"
#include "raster.h"
#include "pico_gl.h"
#include "math.h"

#define PI 3.141592f

static Vec2 external_ring_points[40];
static Vec2 internal_ring_points[40];
static float segments = 20.0f;
static float radio_interno_anillo_interno = 150.0f / 800.0f;
static float radio_externo_anillo_interno = 240.0f / 800.0f;
static float radio_interno_anillo_externo = 220.0f / 800.0f;
static float radio_externo_anillo_externo = 280.0f / 800.0f;

//static float window_ratio = (2.0f / 800.0f) * (2.0f / 600.0f);
static Vec2 window_ratio = {2.0f/600.0f, 2.0f/ 800.0f};

int main (int argc, char** argv)
{
  picoglInit   (800, 600);

  picoglClearColor (0.3f, 0.5f, 1.0f, 1.0f);
  float angle = 0.0f;

  for(int i = 0; i < segments; i++){
    angle = 2.0f * PI * ((float)i / segments);

    internal_ring_points[i] = {(cosf(angle) * radio_externo_anillo_interno), 
                               (sinf(angle) * radio_externo_anillo_interno)};

    internal_ring_points[i + 20] = {(cosf(angle) * radio_interno_anillo_interno), 
                                    (sinf(angle) * radio_interno_anillo_interno)};
  }

  for(int i = 0; i < segments; i++){
    angle = 2.0f * PI * ((float)i / segments);

    external_ring_points[i] = {(cosf(angle) * radio_externo_anillo_externo), 
                               (sinf(angle) * radio_externo_anillo_externo)};

    external_ring_points[i + 20] = {(cosf(angle) * radio_interno_anillo_externo), 
                                    (sinf(angle) * radio_interno_anillo_externo)};
  }

    PicoContext ctx_intern_circle = {
      .culling = kNoCulling,
      .blend = kNoBlend,
      .color = 0xff00ff00,
    };
/*
*/
    PicoContext ctx_extern_circle = {
      .culling = kCullBack,
      .blend = kNoBlend,
      .color = 0xffff0000,
    };
  
  while (1) {

    picoglClear  ();
    for(int i = 0; i < segments; i++){
      Vec2 tri [3] = {
        {internal_ring_points[0  + i]},
        {internal_ring_points[(1  + i) % 20]},
        {internal_ring_points[20 + i]},
      };
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), &ctx_intern_circle, tri);

      Vec2 tri2[3] = {
        internal_ring_points[(1 + i) % 20],
        internal_ring_points[((1 + i) % 20) + 20],
        internal_ring_points[20 + i]};
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), &ctx_intern_circle, tri2);
               
      Vec2 tri3 [3] = {
        {external_ring_points[0  + i]},
        {external_ring_points[(1  + i) % 20]},
        {external_ring_points[20 + i]},
      };
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), &ctx_extern_circle, tri3);
      
      Vec2 tri4 [3] = {
        {external_ring_points[(1 + i) % 20]},
        {external_ring_points[((1 + i) % 20) + 20]},
        {external_ring_points[20 + i]},
      };
      DrawTriangle ((Framebuffer*)picoglGetFramebuffer(), &ctx_extern_circle, tri4);
      /*
      */
    }
    picoglSwapBuffers ();
  }
  
  picoglQuit();
  
  return 1;
}
