
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 Normal; 
out vec3 FragPos;
out vec2 UVs;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  // Output obligatorio del vertex shader (en coordenadas homogeneas 3d)
  gl_Position = projection * model * vec4(aPos, 1.0f);
  // Llevamos la normal a mundo; esto es correcto porque la matriz es otorgonal
  Normal = mat3(model) * aNormal;
  // La formula canonica (que acepta matrices no ortogonales) es esta:
  //Normal = mat3(inverse (transpose(model))) * aNormal;   // ...pero es mucho mas cara
  // Posicion 3d en coordenadas de mundo, para el calculo de difusa del fragment shader
  FragPos = vec3(model * vec4(aPos,1.0));
  UVs = aUV;
}


