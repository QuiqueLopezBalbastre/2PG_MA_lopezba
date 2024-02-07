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

out vec3 normal;
out vec3 position;

mat4 InitAsRotate(float angle, vec3 axis) {
  float s = sin(angle);
  float c = cos(angle);
  float oc = 1.0 - c;

  return mat4(oc * axis.x * axis.x  + c,            oc * axis. x * axis. y - axis. z * s, oc * axis. x * axis. z + axis. y * s, 0.0,
              oc * axis. x * axis. y + axis. z * s, oc *  axis.y * axis.y  + c,           oc * axis. y * axis. z - axis. x * s, 0.0,
              oc * axis. x * axis. z - axis. y * s, oc * axis.y * axis.z + axis.x * s,    oc *  axis.z * axis.z + c, 0.0,
              0.0, 0.0, 0.0, 1.0);
}


void main() {
  mat4 rotation = InitAsRotate(u_time * 0.001, vec3(0.0, 1.0, 0.0));
  position = a_position;
  normal = (rotation * u_m_matrix * vec4(a_normal, 0.0)).xyz;
  gl_Position = u_vp_matrix * rotation* u_m_matrix  * vec4(a_position, 1.0);
}
