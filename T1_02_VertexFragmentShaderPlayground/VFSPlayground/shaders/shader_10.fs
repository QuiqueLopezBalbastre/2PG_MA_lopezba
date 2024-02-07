#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec2 uv;
in vec3 normal;
in vec3 position;

void main() {
  vec3 light_dir = vec3(1.0,0.0,0.0);
  float d = dot(normal, light_dir);
  fragColor = vec4(light_dir * d,1.0);
}
