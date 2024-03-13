
#version 330 core
out vec4 FragColor;

in vec3 Normal; 
in vec3 FragPos;
in vec2 UVs;

uniform vec4 RawColor;
uniform vec3 PointLightPos;
uniform sampler2D Texture1;
 
 // Puntual
 
void main()
{
  vec3 L = normalize(PointLightPos - FragPos);
  vec3 N = normalize(Normal);
  float i = max(dot(L, N),0.0f);
  //FragColor = RawColor * i;
   //               R     G  B   A
  //FragColor = vec4(0.0, UVs, 0.0);
  FragColor = texture(Texture1, UVs) * i; 
}

/*
// Direccional

void main()
{
  vec3 N = normalize(Normal);
  float i = dot(N, vec3(0.0f, 0.0f, 1.0f));
  FragColor = RawColor * i;
}
*/
