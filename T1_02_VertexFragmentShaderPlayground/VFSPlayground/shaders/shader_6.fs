#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec2 uv;
in vec3 normal;

void main() {
  fragColor = vec4(normal + 0.5, 1.0);
}
