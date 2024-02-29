/**
 *
 * @brief Basic material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "material_basic.h"


namespace EDK3 {

static const char kExampleVertexShader1[] =
  "#version 330\n"
  "uniform...";

#define GLSL(x) "#version 330\n"#x
static const char* kExampleVertexShader2 = GLSL(
  //The shader itself.
);

//IMPORTANT!!!
//Type the constructors, destructor and operator= here, just in this point!!!
//If you don't do it, it won't compile!!!

void MaterialBasic::init() {
  //1: Request at least two shaders and one program to the GPU Manager.
  //2: Load the source code to the requested shaders.
  //3: Compile both shaders.
  //4: Attach shaders to the program.
  //5: Finally... link the program!
}

bool MaterialBasic::enable(const EDK3::MaterialSettings *mat) const {
  //Enable the material...
  //... and use the uniforms located in the material settings!
  return false;
}

void MaterialBasic::setupCamera(const float projection[16],
                                const float view[16]) const {
  //Set the projection and view matrices as uniforms here!
}

void MaterialBasic::setupModel(const float model[16]) const {
  //Set the model matrix as uniform here!
}

unsigned int MaterialBasic::num_attributes_required() const {
  //Depending on how attributes the geometry has.
}

EDK3::Attribute MaterialBasic::attribute_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Attribute" enum.
  //Depending on how attributes are stored in the geometry buffer.
}

EDK3::Type MaterialBasic::attribute_type_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Type" enum.
  //Depending on how attributes are stored in the geometry buffer.
}

} //EDK3
