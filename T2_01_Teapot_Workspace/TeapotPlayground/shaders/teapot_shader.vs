#version 330

//By default, in this demo the objects are in the following position:
// [0]:  -2.0,  -2.5,   0.0
// [1]:   0.0,  -2.5,   0.0
// [2]:   2.0,  -2.5,   0.0
// [3]:  -2.0,  -0.5,   0.0
// [4]:   0.0,  -0.5,   0.0
// [5]:   2.0,  -0.5,   0.0
// [6]:  -2.0,   1.5,   0.0
// [7]:   0.0,   1.5,   0.0
// [8]:   2.0,   1.5,   0.0

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;
uniform vec3 u_camera_position;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

out vec3 normal;
out vec3 pos;

void main() {
  gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);
  pos = (u_m_matrix * vec4(a_position, 1.0)).xyz;
  normal = (u_m_matrix *vec4(a_normal, 0.0)).xyz;
}
