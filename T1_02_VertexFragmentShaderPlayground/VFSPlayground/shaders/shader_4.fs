#version 330

uniform sampler2D u_texture;
out vec4 fragColor;

in vec2 uv;

void main() {
  vec4 q_texture = texture(u_texture, uv);
  fragColor = q_texture;
}
