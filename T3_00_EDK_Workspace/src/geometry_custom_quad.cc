/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_quad.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"


namespace EDK3 {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!

  QuadCustom::QuadCustom()
  {
    is_initialized_ = false;
  }
  QuadCustom::~QuadCustom(){}
  QuadCustom& QuadCustom::operator=(const QuadCustom&)
  {
    return *this;
  }

void QuadCustom::init(const float quad_size) {
  //TODO demand graphic resources to the GPUManager.

  EDK3::dev::GPUManager::Instance()->newBuffer(&elements_buffer);
  EDK3::dev::GPUManager::Instance()->newBuffer(&order_buffer);
  /*
   The quad face is like this:
         0---------1
         |\        |
         | \       |
         |  \      |
         |   \     |
         |    \    |
         |     \   |
         |      \  |
         |       \ |
         |        \|
         2---------3
    That's the order of its face.
   */

  //****** Positions:
  //TODO
  float size = quad_size * 0.5f;
  ESAT::Vec3 positions[4] = { {-size, size, 0.0f},
                             {size, size, 0.0f},
                             { -size,-size, 0.0f},
                             { size, -size, 0.0f} };

  //****** Normals:
  //TODO
  ESAT::Vec3 normals[4] = {
    (0.0f,0.0f,1.0f),
    (0.0f,0.0f,1.0f),
    (0.0f,0.0f,1.0f),
    (0.0f,0.0f,1.0f),
  };

  //****** UVs:
  //TODO
  ESAT::Vec2 uvs[4] = {
    {0.0f, 1.0f},
    {1.0f, 1.0f},
    {0.0f, 0.0f},
    {1.0f, 0.0f},
  };

  //****** Colors:
  //TODO
  

  //****** Upload data:
  //TODO initialize and upload data to the "elements_buffer".
  //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
  //48 attributes has a face.

  constexpr int kNData = 8 * 4;
  float data[kNData];
  int j = 0;
  for (int i = 0; i < 4; i++)
  {
    data[j++] = positions[i].x;
    data[j++] = positions[i].y;
    data[j++] = positions[i].z;

    data[j++] = normals[i].x;
    data[j++] = normals[i].y;
    data[j++] = normals[i].z;

    data[j++] = uvs[i].x;
    data[j++] = uvs[i].y;
  }

  elements_buffer->init(sizeof(data));
  elements_buffer->uploadData(data, sizeof(data), 0);
  //****** Upload order:
  //TODO initialize and upload data to the "order_buffer".
  //Remember to order triangles in counter clockwise direction!!
  //6 vertices per face * 1 faces * sizeof(short int)
  unsigned int order[] = { 0, 2, 3, 0, 3, 1 };
  order_buffer->init(sizeof(order));
  order_buffer->uploadData(order, sizeof(order), 0);
}

bool QuadCustom::bindAttribute(const Attribute a,
                               unsigned int where_to_bind_attribute) const {
  //TODO
  //EDK3::dev::GPUManager::Instance()->enableVertexAttribute
  switch (a)
  {
  case Attribute::A_POSITION:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
      elements_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_3, 0,
      sizeof(float) * 0.0f, sizeof(float) * 8.0f);
    break;
  case Attribute::A_NORMAL:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
      elements_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_3, 0, 
      sizeof(float) * 3.0f, sizeof(float) * 8.0f);
    break;
  case Attribute::A_UV:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
      elements_buffer.get(), where_to_bind_attribute, EDK3::T_FLOAT_2, 0, 
      sizeof(float) * 6.0f, sizeof(float) * 8.0f);

    break;
  default:
    return false;
    break;
  }
  return true;
}

void QuadCustom::render() const {
  //TODO
  EDK3::dev::GPUManager::Instance()->drawElements(
    EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, 6, order_buffer.get(), EDK3::Type::T_UINT,
    0);
}

} //EDK3
