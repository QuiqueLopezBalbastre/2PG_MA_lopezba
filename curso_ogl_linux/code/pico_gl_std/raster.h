
#ifndef _RASTER_H_
#define _RASTER_H_

typedef unsigned int ARGBColor8888;


typedef struct
{
  int w, h;
  ARGBColor8888* pixels;
} Framebuffer;


typedef struct
{
  float x, y;
} Vec2;

enum CullingMode
{
  kNoCulling,
  kCullFront,
  kCullBack
};

enum BlendingType
{
  kNoBlend,
  kBlendSrcAlpha,
  kBlendDstAlpha
};

typedef struct
{
  CullingMode   culling;
  BlendingType  blend;
  ARGBColor8888 color;
} PicoContext;


void DrawTriangle (Framebuffer* fb, PicoContext* ctx, Vec2* tri_vtx);

#endif




