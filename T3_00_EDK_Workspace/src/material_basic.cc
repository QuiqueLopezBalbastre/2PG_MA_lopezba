/**
 *
 * @brief Basic material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "material_basic.h"
#include <EDK3/dev/gpumanager.h>
#include <ESAT/math.h>


namespace EDK3 {

#define GLSL(x) "#version 330\n"#x
    static const char* kExampleVertexShader = GLSL(
        //The shader itself.
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec3 a_normal;
    layout(location = 2) in vec2 a_uv;
    uniform mat4 u_view_projection;
    uniform mat4 u_model;
    out vec2 uv;
    void main()
    {
        gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
        uv = a_uv;
    }
);

#define GLSL(x) "#version 330\n"#x
    static const char* kExampleFragmentShader = GLSL(
    //The shader itself.
    uniform sampler2D u_albedo_1;
    uniform sampler2D u_albedo_2;
    uniform vec4 u_color;
    uniform int u_use_texture;
    in vec2 uv;
    out vec4 FragColor;
    void main()
    {
        //srand(time_t);
        if (0 == u_use_texture)
        {
            FragColor = u_color;
        }
        else {
            
            FragColor = u_color * texture(u_albedo_1, uv);
        }
        //FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
);

//IMPORTANT!!!
//Type the constructors, destructor and operator= here, just in this point!!!
//If you don't do it, it won't compile!!!

MaterialBasic::MaterialBasic()
{

}
MaterialBasic::~MaterialBasic(){}
MaterialBasic& MaterialBasic::operator=(const MaterialBasic& other) { return *this; }

void MaterialBasic::init() {
  //1: Request at least two shaders and one program to the GPU Manager. ¬/
  //2: Load the source code to the requested shaders. ¬/
  //3: Compile both shaders. ¬/
  //4: Attach shaders to the program. ¬/
  //5: Finally... link the program! ¬/
    EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
    EDK3::ref_ptr<EDK3::dev::Shader> vshader;
    EDK3::ref_ptr<EDK3::dev::Shader> fshader;
    EDK3::scoped_array<char> error_log;


    GPU.newShader(&vshader);
    GPU.newShader(&fshader);
    GPU.newProgram(&program_);

    vshader->loadSource(vshader->EDK3::dev::Shader::Type::kType_Vertex, kExampleVertexShader, strlen(kExampleVertexShader));
    fshader->loadSource(fshader->EDK3::dev::Shader::Type::kType_Fragment, kExampleFragmentShader, strlen(kExampleFragmentShader));
    if (!vshader->compile(&error_log))
    {
        printf("Error in compiling Vertex Shader: %s\n", error_log.get());
    }
    
    if (!fshader->compile(&error_log))
    {
        printf("Error in compiling Fragment Shader:%s\n", error_log.get());
    }
/*

    vshader->compile();
    fshader->compile();
*/
    program_->attach(vshader.get());
    program_->attach(fshader.get());
    if (!program_->link(&error_log))
    {
        printf("Error in linking program: %s\n", error_log.get());
    }
    /*
    program_->link();
    */
}

bool MaterialBasic::enable(const EDK3::MaterialSettings *mat) const {
    //Enable the material...
    //... and use the uniforms located in the material settings!

    const MaterialBasicSettings* ms = dynamic_cast<const MaterialBasicSettings*>(mat);
    MaterialBasicSettings* non_cast_ms = const_cast<MaterialBasicSettings*>(ms);
    if (ms)
    {
        program_->use();
        float color[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
        unsigned int color_loc = program_->get_uniform_position("u_color");
        program_->set_uniform_value(color_loc, Type::T_FLOAT_4, non_cast_ms->color());
        return true;
    }
    else
    {
        const MaterialBasicTextureSettings* ms2 = dynamic_cast<const MaterialBasicTextureSettings*>(mat);
        if (ms2)
        {
            program_->use();
            float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
            unsigned int color_loc = program_->get_uniform_position("u_color");
            program_->set_uniform_value(color_loc, Type::T_FLOAT_4, ms2->color());
            int slot = 0;
            unsigned int albedo_loc = 0;
            if (ms2->texture(0).get()){
                ms2->texture(0)->bind(slot);
                albedo_loc = program_->get_uniform_position("u_albedo_1");
                program_->set_uniform_value(albedo_loc, EDK3::Type::T_INT_1, &slot);
                slot++;
            }
            if (ms2->texture(1).get())
            {
                ms2->texture(1)->bind(slot);
                albedo_loc = program_->get_uniform_position("u_albedo_2");
                program_->set_uniform_value(albedo_loc, EDK3::Type::T_INT_1, &slot);
                slot++;
            }
            int boolean = program_->get_uniform_position("u_use_texture");
            program_->set_uniform_value(boolean, EDK3::Type::T_INT_1, &boolean);
            //printf("use_texture = %d", boolean);
            return true;
        }
    }
    return false;
}

void MaterialBasic::setupCamera(const float projection[16],
                                const float view[16]) const {
  //Set the projection and view matrices as uniforms here!

    ESAT::Mat4 proj_ = ESAT::Mat4FromColumns(projection);
    ESAT::Mat4 view_ = ESAT::Mat4FromColumns(view);
    ESAT::Mat4 m = ESAT::Mat4Multiply(proj_, view_);
    program_->set_uniform_value(program_->get_uniform_position("u_view_projection"), T_MAT_4x4, m.d);

}

void MaterialBasic::setupModel(const float model[16]) const {
  //Set the model matrix as uniform here!
    ESAT::Mat4 m = ESAT::Mat4FromColumns(model);
    program_->set_uniform_value(program_->get_uniform_position("u_model"), T_MAT_4x4, m.d);
}

unsigned int MaterialBasic::num_attributes_required() const {
  //Depending on how attributes the geometry has.
    return 3;
}

EDK3::Attribute MaterialBasic::attribute_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Attribute" enum.
  //Depending on how attributes are stored in the geometry buffer.
    switch (attrib_idx)
    {
    case 0:
        return A_POSITION;
    case 1:
        return A_NORMAL;
    case 2:
        return A_UV;
    }
}

EDK3::Type MaterialBasic::attribute_type_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Type" enum.
  //Depending on how attributes are stored in the geometry buffer.
    switch (attrib_idx)
    {
    case 0:
        return T_FLOAT_3;
    case 1:
        return T_FLOAT_3;
    case 2:
        return T_FLOAT_2;
    }
}

} //EDK3
