#version 330
layout(location = 0) out vec4 fragColor;
uniform vec3 u_camera_position;
in vec2 uv;

//Textures:
uniform sampler2D u_albedo_texture;
uniform sampler2D u_specular_texture;

void main() {
  fragColor = texture(u_albedo_texture, uv);
}
