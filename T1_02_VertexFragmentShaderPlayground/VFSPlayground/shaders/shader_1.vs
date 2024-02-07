#version 330

//Cube size:
//1.0 x 1.0 x 1.0
//By default, in this demo the camera is in the following position:
//3.0, 2.0, 3.0
//By default, in this demo the object is in the following position:
//0.0, 0.0, 0.0
//By default, in this demo the window has the following size:
//1000.0, 600.0

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;




void main() {
  // a_position += a_position;
  gl_Position = u_m_matrix * vec4(a_position, 1.0);
}
