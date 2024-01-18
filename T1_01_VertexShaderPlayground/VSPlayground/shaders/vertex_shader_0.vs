#version 330

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;
out vec2 uv;
uniform vec2 u_window_size;
uniform vec3 u_camera_position;
uniform float u_time;

//By default, in this demo the camera is in the following position:
//0.0, 2.0, 3.0
//By default, in this demo the object is in the following position:
//0.0, 0.0, 0.0
//By default, in this demo the window has the following size:
//1000.0, 600.0

//Example of function which returns a translation matrix:
mat4 InitAsTranslate(float tx, float ty, float tz) {
  return mat4(1.0, 0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0,
              0.0, 0.0, 1.0, 0.0,
              tx,  ty,  tz,  1.0);
}


void main(){
  mat4 translate = InitAsTranslate(0.0, 0.0, 0.0);
  gl_Position = translate * vec4(a_position, 1.0);
  uv = a_uv;
}
