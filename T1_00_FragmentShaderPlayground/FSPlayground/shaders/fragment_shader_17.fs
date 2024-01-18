#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {

  vec3 white = vec3(1.0, 1.0, 1.0);

  //pixelating
  float pixel = 8.0;
  float r = 1.0 / pixel;
  vec2 window_size = u_window_size * r;
  vec2 pixel_coord;
  modf(gl_FragCoord.x / pixel, pixel_coord.x);
  modf(gl_FragCoord.y / pixel, pixel_coord.y);

  // PacMan body
  vec2 body_center = window_size * 0.5;
  float pacman_radius = 200.0 * r;
  vec3 pacman_color = vec3(1.0, 1.0, 0.0);

  float distance = length(pixel_coord - body_center);
  float border = step(distance, pacman_radius);

  //Eye 
  vec2 eye_center = vec2(window_size.x * 0.52, window_size.y * 0.6);
  float eye_radius = 20 * r;

  float eye_distance = length(pixel_coord - eye_center);
  float eye_border = step(eye_radius, eye_distance);


  //Mouth 
  float mouth_threshold = 0.88 + (sin((u_time * 0.001) * 0.5 + 0.5) * 0.12);
  vec2 angle = vec2(cos(0.0), sin(0.0));
  vec2 mouth_center = body_center;
  float mouth_dot = dot(angle, normalize(pixel_coord - mouth_center));
  float mouth = step(mouth_dot, mouth_threshold);


  vec3 color = pacman_color * border * eye_border * mouth;
  // color = mix(color, white, mouth_threshold);

  fragColor = vec4(color, 1.0);
}