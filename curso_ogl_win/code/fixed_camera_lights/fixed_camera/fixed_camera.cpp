
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// GLAD es una libreria "loader-generator"; OpenGL requiere este tipo de libreria (de la que existen 
// varias implementaciones dependiendo de la plataforma)
#include "deps/glad.h"

//-- SOKOL 
// Sokol es una libreria simple portable para abrir ventanas
#define SOKOL_GLCORE33 1
#define SOKOL_APP_IMPL 1
#define SOKOL_TIME_IMPL 1

#include "deps/sokol_app.h"
#include "deps/sokol_time.h"
// --

static int gWindowWidth = 800;
static int gWindowHeight = 600;

// ------------------------------------------------------------------------------------

static unsigned char* Slurp (const char* filename)
{
  FILE* in_file = 0;
  int err = fopen_s(&in_file, filename, "rb");
  assert(in_file);
  struct stat sb;
  assert(stat(filename, &sb) != -1);
  unsigned char* file_contents = (unsigned char*)malloc(sb.st_size + 1);
  if (file_contents) {
    fread(file_contents, sb.st_size, 1, in_file);
    file_contents[sb.st_size] = 0;
    fclose(in_file);
  }
  return file_contents;
}

// Shaders
// ------------------------------------------------------------------------------------

static char infoLog[512];

// Imprime los posibles errores de compilacion o linkado
static void CheckGPUErrors(unsigned int code, const char* str, bool link)
{
  int success = 0;
  if (link) {
    glGetProgramiv(code, GL_LINK_STATUS, &success);
    if (!success)
      glGetProgramInfoLog(code, 512, NULL, infoLog);
  }
  else {
    glGetShaderiv(code, GL_COMPILE_STATUS, &success);
    if (!success)
      glGetShaderInfoLog(code, 512, NULL, infoLog);
  }
  if (!success) {
    std::cout << str << infoLog << std::endl;
  }
}


static void ShadersInit(unsigned int& shader_program,
  const char* vertex_src,
  const char* shader_src)
{
  // Vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_src, NULL);
  glCompileShader(vertexShader);
  CheckGPUErrors(vertexShader, "VERTEX COMPILATION_FAILED\n", false);

  // Fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &shader_src, NULL);
  glCompileShader(fragmentShader);
  CheckGPUErrors(fragmentShader, "FRAGMENT COMPILATION_FAILED\n", false);

  // Link shaders
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertexShader);
  glAttachShader(shader_program, fragmentShader);
  glLinkProgram(shader_program);
  CheckGPUErrors(shader_program, "SHADER PROGRAM LINKING_FAILED\n", true);

  // Los shaders compilados pueden ser liberados una vez linkado el programa
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// ------------------------------------------------------------------------------------
// Subir una malla a memoria grafica
// VAO = Vertex arrays object <- esto es la malla!
// VBO = Vertex buffer object <- alloc en vram para vertices
// EBO = Element buffer object (indices) <- alloc en vram para indices
// El objeto "array" es el que nos interesa; Los "buffer" solo son una reservas de memoria (grafica)
// y por lo tanto los necesitaremos para la liberacion de recursos, pero no se volvera a usar

struct MeshVtx
{
    glm::vec3 aPos;
    glm::vec3 aNorm;
};

static void UploadMesh(MeshVtx* vertices, int vertices_size, 
                       unsigned int* indices, int indices_size,
                       unsigned int& VBO, unsigned int& VAO, unsigned int& EBO)
{

  // Generamos 3 instancias de objetos OGL: array y buffers (sin inicializar)
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // Enfocamos ambos objetos, VAO y VBO 
  // Esto es necesario, sino podriamos tocar atributos de VBOs y VAOs usados anteriormente
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Configuramos el buffer (tipo y cantidad de memoria). EN ESTE MOMENTO SE COPIAN LOS VERTICES
  // STATIC_DRAW significa que los datos no se modificaran en el futuro
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  // Idem  para los indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
  // Configuramos el array describiendo los atributos de la estructura (posicion, normal, uv, etc)
  // Es un array de vertices de 3 floats, con una separacion entre ellos de 12 bytes
  // El indice de attributo 0 se refiere normalmente a vertices (X,Y,X),
  // el 1 a normales (X,Y,Z) y el 2 a coord. textura (U,V). Pero no esta recomendado
  // usarlos asi, sino con (ej,) glGetAttribLocation(program, "position")
  // Ademas, glVertexAttribPointer relacion el buffer con este array por el ultimo "bind"
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVtx), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVtx), (void*)12);
  glEnableVertexAttribArray(1);

  // Se quita el foco del VAO y el VBO; glVertexAttribPointer ya se ha quedado las referencias
  // Quizar el foco evita que otras llamadas puedan modificar estos objetos accidentalmente 
  // (No se debe quitar el foco del EBO mientras el VAO este en foco, o perdera la referencia)
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


static MeshVtx gMesh[] = {
  {{+1.0f, +1.0f, +1.0f}, {+0.577f, +0.577f, +0.577f }},  // 0
  {{+1.0f, -1.0f, +1.0f}, {+0.577f, -0.577f, +0.577f }},  // 1
  {{-1.0f, -1.0f, +1.0f}, {-0.577f, -0.577f, +0.577f }},  // 2
  {{-1.0f, +1.0f, +1.0f}, {-0.577f, +0.577f, +0.577f }},  // 3

  {{+1.0f, +1.0f, -1.0f}, {+0.577f, +0.577f, -0.577f}},   // 4
  {{+1.0f, -1.0f, -1.0f}, {+0.577f, -0.577f, -0.577f}},   // 5
  {{-1.0f, -1.0f, -1.0f}, {-0.577f, -0.577f, -0.577f}},   // 6
  {{-1.0f, +1.0f, -1.0f}, {-0.577f, +0.577f, -0.577f}},   // 7
};

static unsigned int gIndices[] = {
  2, 1, 0, 0, 3, 2,
  5, 6, 4, 6, 7, 4,
  5, 4, 1, 4, 0, 1,
  6, 2, 7, 2, 3, 7,
  5, 1, 2, 2, 6, 5,
  0, 4, 7, 7, 3, 0
};

static MeshVtx gMeshGroups[] = {
  {{+1.0f, +1.0f, +1.0f}, {+0.0f, +0.0f, +1.0f}}, // 0
  {{+1.0f, -1.0f, +1.0f}, {+0.0f, +0.0f, +1.0f}}, // 1
  {{-1.0f, -1.0f, +1.0f}, {+0.0f, +0.0f, +1.0f}}, // 2
  {{-1.0f, +1.0f, +1.0f}, {+0.0f, +0.0f, +1.0f}}, // 3

  {{+1.0f, +1.0f, -1.0f}, {+0.0f, +0.0f, -1.0f}}, // 4
  {{+1.0f, -1.0f, -1.0f}, {+0.0f, +0.0f, -1.0f}}, // 5
  {{-1.0f, -1.0f, -1.0f}, {+0.0f, +0.0f, -1.0f}}, // 6
  {{-1.0f, +1.0f, -1.0f}, {+0.0f, +0.0f, -1.0f}}, // 7

  {{+1.0f, +1.0f, +1.0f}, {+1.0f, +0.0f, +0.0f}}, // 8  (0)
  {{+1.0f, -1.0f, +1.0f}, {+1.0f, +0.0f, +0.0f}}, // 9  (1)
  {{+1.0f, -1.0f, -1.0f}, {+1.0f, +0.0f, +0.0f}}, // 10 (5)
  {{+1.0f, +1.0f, -1.0f}, {+1.0f, +0.0f, +0.0f}}, // 11 (4)

  {{-1.0f, -1.0f, +1.0f}, {-1.0f, +0.0f, +0.0f}}, // 12 (2)
  {{-1.0f, +1.0f, +1.0f}, {-1.0f, +0.0f, +0.0f}}, // 13 (3)
  {{-1.0f, +1.0f, -1.0f}, {-1.0f, +0.0f, +0.0f}}, // 14 (7)
  {{-1.0f, -1.0f, -1.0f}, {-1.0f, +0.0f, +0.0f}}, // 15 (6)

  {{+1.0f, +1.0f, +1.0f}, {+0.0f, +1.0f, +0.0f}}, // 16 (0)
  {{-1.0f, +1.0f, +1.0f}, {+0.0f, +1.0f, +0.0f}}, // 17 (3)
  {{-1.0f, +1.0f, -1.0f}, {+0.0f, +1.0f, +0.0f}}, // 18 (7)
  {{+1.0f, +1.0f, -1.0f}, {+0.0f, +1.0f, +0.0f}}, // 19 (4)

  {{+1.0f, -1.0f, +1.0f}, {+0.0f, -1.0f, +0.0f}}, // 20 (1)
  {{-1.0f, -1.0f, +1.0f}, {+0.0f, -1.0f, +0.0f}}, // 21 (2)
  {{-1.0f, -1.0f, -1.0f}, {+0.0f, -1.0f, +0.0f}}, // 22 (6)
  {{+1.0f, -1.0f, -1.0f}, {+0.0f, -1.0f, +0.0f}}, // 23 (5)
};

static unsigned int gIndicesGroups[] = {
  2, 1, 0, 0, 3, 2,
  4, 5, 6, 6, 7, 4,
  10, 11, 9, 11, 8, 9,
  15, 12, 14, 12, 13, 14,
  16, 19, 18, 18, 17, 16,
  23, 20, 21, 21, 22, 23,
};

static unsigned int gShaderProgram = 0;
// Mallas: Vertex buffer arrays, vertex object arrays
static unsigned int gVBO0 = 0, gVAO0 = 0, gEBO0 = 0;
static unsigned int gVBO1 = 0, gVAO1 = 0, gEBO1 = 0;
// Locations de las variables "uniform" de los shaders
static int gLocationColor = 0;
static int gModelLoc = -1;
static int gProjLoc = -1;

// -----------------------------------------------------------------------------------------------------------

void onInit()
{
  gladLoadGL();

  stm_setup(); // Init time libreria SOKOL

  char* vertex_shader_source   = (char*)Slurp("vertex.glslv");
  char* fragment_shader_source = (char*)Slurp("fragment.glslf");

  ShadersInit(gShaderProgram, vertex_shader_source, fragment_shader_source);

  UploadMesh(gMesh, sizeof(gMesh), gIndices, sizeof(gIndices), gVBO0, gVAO0, gEBO0);
  UploadMesh(gMeshGroups, sizeof(gMeshGroups), gIndicesGroups, sizeof(gIndicesGroups), gVBO1, gVAO1, gEBO1);

  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);

  // Obtenemos los identificadores (location) de los "uniform" de los shaders 
  gLocationColor = glGetUniformLocation(gShaderProgram, "RawColor");
  gModelLoc = glGetUniformLocation(gShaderProgram, "model");
  gProjLoc = glGetUniformLocation(gShaderProgram, "projection");

  // Chequear que todo fue bien
  assert(glGetError() == GL_NO_ERROR);
}

// -----------------------------------------------------------------------------------------------------------

void onFrame()
{
  gWindowWidth = sapp_width();
  gWindowHeight = sapp_height();
  double time = stm_ms(stm_now());

  // Transformaciones de objeto (la camara se supone fija, mirando a Z)
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 model2 = glm::mat4(1.0f);
  // Ponemos nuestro objeto frente a la camara
  model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -8.0f));
  model = glm::rotate(model, /*5.0f*/0.0001f * (float)time, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, /*5.0f*/0.002f * (float)time, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, /*5.0f*/0.003f * (float)time, glm::vec3(0.0f, 0.0f, 1.0f));

  model2 = glm::translate(model2, glm::vec3(2.0f, 0.0f, -8.0f));
  model2 = glm::rotate(model2, /*5.0f*/0.0001f * (float)time, glm::vec3(0.0f, 1.0f, 0.0f));
  model2 = glm::rotate(model2, /*5.0f*/0.002f * (float)time, glm::vec3(1.0f, 0.0f, 0.0f));
  model2 = glm::rotate(model2, /*5.0f*/0.003f * (float)time, glm::vec3(0.0f, 0.0f, 1.0f));
  // Proyeccion con un FOV de 45 grados
  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(45.0f), ((float)gWindowWidth) / (float)gWindowHeight, 0.1f, 100.0f);

  // Render
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(gShaderProgram);

  glUniform4f(gLocationColor, 0.0f, 0.0f, 1.0f, 1.0f);

  // Enviamos las matrices a los shaders
  glUniformMatrix4fv(gModelLoc, 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(gProjLoc, 1, GL_FALSE, &projection[0][0]);


  // Seleccionamos la malla a pintar
  glBindVertexArray(gVAO0);
  // Draw elements dibuja primitivas indexadas (en nuestros caso, mallas de triangulos)
  glDrawElements(GL_TRIANGLES, sizeof(gIndices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

  // Chequear que todo fue bien
  assert(glGetError() == GL_NO_ERROR);
  // Enviamos las matrices a los shaders
  glUniformMatrix4fv(gModelLoc, 1, GL_FALSE, &model2[0][0]);
  glUniformMatrix4fv(gProjLoc, 1, GL_FALSE, &projection[0][0]);


  // Seleccionamos la malla a pintar
  glBindVertexArray(gVAO1);
  // Draw elements dibuja primitivas indexadas (en nuestros caso, mallas de triangulos)
  glDrawElements(GL_TRIANGLES, sizeof(gIndicesGroups) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

  assert(glGetError() == GL_NO_ERROR);

}

// Liberacion de recursos
// -----------------------------------------------------------------------------------------------------------

void onEnd()
{
  glDeleteVertexArrays(1, &gVAO0);
  glDeleteBuffers(1, &gVBO0);
  glDeleteBuffers(1, &gEBO0);
  glDeleteVertexArrays(1, &gVAO1);
  glDeleteBuffers(1, &gVBO1);
  glDeleteBuffers(1, &gEBO1);
  glDeleteProgram(gShaderProgram);
}

// Inicializaciones: abrir ventana, etc
// La libreria Sokol exige  este nombre de funcion para la inicializacion
// ------------------------------------------------------------------------------------

sapp_desc sokol_main(int argc, char** argv)
{
  sapp_desc app = {};
  app.width = gWindowWidth;
  app.height = gWindowHeight;
  app.frame_cb = onFrame;
  app.init_cb = onInit;
  app.cleanup_cb = onEnd;
  //app.win32_console_create = true;
  app.win32_console_attach = true;
  return app;
}

