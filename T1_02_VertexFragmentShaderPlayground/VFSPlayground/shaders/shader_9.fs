#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec2 uv;
in vec3 normal;
in vec3 position;

void main() {
  // fragColor = vec4(normal - vec3(0.0,1.0,1.0),1.0);
  fragColor = vec4(normal * vec3(1.0,0.0,0.0),1.0);
}
