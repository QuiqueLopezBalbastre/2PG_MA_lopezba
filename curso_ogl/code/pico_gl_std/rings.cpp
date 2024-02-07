

// PicoGL include
#include "pico_gl.h"
#include "vec2.h"
#include "math.h"

#define PI 3.141592f

static Vec2 external_ring_points[40];
static Vec2 internal_ring_points[40];
static unsigned int index[120];
static unsigned int index2[120];
static float segments = 20.0f;
static float radio_interno_anillo_interno = 150.0f;
static float radio_externo_anillo_interno = 240.0f;
static float radio_interno_anillo_externo = 220.0f;
static float radio_externo_anillo_externo = 280.0f;
static Vec2 window = {800.0f, 600.0f};


static Vec2 window_ratio = {2.0f/window.x, 2.0f/ window.y};

int main (int argc, char** argv)
{
  picoglInit   (window.x, window.y);

  picoglClearColor (0.3f, 0.5f, 1.0f, 1.0f);
  float angle = 0.0f;

  for(int i = 0; i < segments; i++){
    angle = 2.0f * PI * ((float)i / segments);

    internal_ring_points[i] = {(cosf(angle) * radio_externo_anillo_interno * window_ratio.x), 
                               (sinf(angle) * radio_externo_anillo_interno * window_ratio.y)};

    internal_ring_points[i + 20] = {(cosf(angle) * radio_interno_anillo_interno * window_ratio.x), 
                                    (sinf(angle) * radio_interno_anillo_interno * window_ratio.y)};
  }

  for(int i = 0; i < segments; i++){
    angle = 2.0f * PI * ((float)i / segments);

    external_ring_points[i] = {(cosf(angle) * radio_externo_anillo_externo * window_ratio.x), 
                               (sinf(angle) * radio_externo_anillo_externo * window_ratio.y)};

    external_ring_points[i + 20] = {(cosf(angle) * radio_interno_anillo_externo * window_ratio.x), 
                                    (sinf(angle) * radio_interno_anillo_externo * window_ratio.y)};
  }

/*
    PicoContext ctx_intern_circle = {
      .culling = kNoCulling,
      .blend = kNoBlend,
      .color = 0xff00ff00,
    };
    PicoContext ctx_extern_circle = {
      .culling = kCullBack,
      .blend = kNoBlend,
      .color = 0xffff0000,
    };
*/
    for(int i = 0; i < 20; i++){
      index[i * 6] = i;
      index[i * 6 + 1] = (1 + i) % 20;
      index[i * 6 + 2] = 20 + i;
      index[i * 6 + 3] = (1 + i) % 20;
      index[i * 6 + 4] = (1 + i) % 20 + 20;
      index[i * 6 + 5] = 20 + i;
    }
    for(int i = 0; i < 20; i++){
      index2[i * 6] = (1 + i) % 20;
      index2[i * 6 + 1] = i;
      index2[i * 6 + 2] = 20 + i;
      index2[i * 6 + 3] = (1 + i) % 20 + 20;
      index2[i * 6 + 4] = (1 + i) % 20;
      index2[i * 6 + 5] = 20 + i;
    }


  picoglEnable(PGL_CULL_FACE);

  while (1) {

    picoglClear  ();

    picoglDisable(PGL_BLEND);
    picoglCullFace(PGL_BACK);    
    glColor4f(0.0,1.0,0.0,1.0);
    picoglDrawTris((float*)internal_ring_points, index, 120);
    
    picoglEnable(PGL_BLEND);
    picoglBlendFunc(PGL_SRC_ALPHA, PGL_ONE_MINUS_SRC_ALPHA);
    picoglCullFace(PGL_FRONT);  
    glColor4f(1.0,0.0,0.0,0.5);
    picoglDrawTris((float*)external_ring_points, index2, 120);
               
    

    picoglSwapBuffers ();
  }
  
  picoglQuit();
  
  return 1;
}
