#version 330
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