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

mat4 InitAsScale(float sx, float sy, float sz) {
  return mat4(sx, 0.0, 0.0, 0.0,
              0.0, sy, 0.0, 0.0,
              0.0, 0.0, sz, 0.0,
              0.0, 0.0, 0.0, 1.0);
}


mat4 InitAsRotate(float angle, vec3 axis) {
  float s = sinf(angle);
  float c = cosf(angle);
  float oc = 1.0 - c;

  return mat4(oc - pow(axis.x, 2) + c,              oc ∗ axis. x ∗ axis. y − axis. z ∗ s, oc ∗ axis. x ∗ axis. z + axis. y ∗ s, 0.0,
              oc ∗ axis. x ∗ axis. y + axis. z * s, oc ∗ pow(axis.y, 2) + c,              oc ∗ axis. y ∗ axis. z − axis. x ∗ s, 0.0,
              oc ∗ axis. x ∗ axis. z − axis. y ∗ s, 0.0,                                  oc ∗ pow(axis.z, 2) + c,              0.0,
              0.0,                                  0.0,                                  0.0,                                  1.0);
}

mat4 InitAsView(vec3 camera_position, vec3 target_point)
{
  vec3 up = vec3(0.0, 1.0, 0.0);
  vec3 forward = normalize(target_point - camera_position);
  vec3 left = normalize(cross(forward, up));
  vec3 updated_up = normalize(cross(left, forward));


  float dot_left_pos = dot(left, camera_position);
  float dot_up_pos = dot(updated_up, camera_position);
  float dot_fwd_pos = dot(forward, camera_position);

  return mat4(left.x, updated_up.x, -forward.x, 0.0,
              left.y, updated_up.y, -forward.y, 0.0,
              left.z, updated_up.z, -forward.z, 0.0);
}

mat4 InitAsPerspective(float fov, float aspect, float znear, float zfar)
{
  float r = tan(fov * 0.5);
  return mat4
  (
    1.0 / (aspect * r), 0.0,                                         0.0, 0.0,
    0.0,                1.0 / r,                                     0.0, 0.0,
    0.0,                0.0, -(2.0 * zfar * znear) / (zfar * znear), 0.0, 0.0,
    0.0,                0.0, -(2.0 * zfar * znear) / (zfar * znear), 0.0, 0.0
  )
}


void main(){
  mat4 translate = InitAsTranslate(0.0, 0.0, 0.0);
  mat4 scale = InitAsScale(1.0, 1.0, 1.0);
  mat4 rotate = InitAsRotate(0.0, vec3(0.0, 1.0, 0.0));
  mat4 view = InitAsView(u_camera_position, vec3(0.0, 0.0, 0.0));
  mat4 perspective = InitAsPerspective(1.57, u_window_size.x / u_window_size.y, 0.01, 100.0);
  gl_Position = perspective * view * translate * rotate * scale * vec4(a_position, 1.0);
  uv = a_uv;
}
