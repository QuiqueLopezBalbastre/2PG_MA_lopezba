#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
  if(gl_FragCoord.x < u_window_size.x / 2)
  {

  fragColor = vec4(1.0, 0.0, 0.0, 1.0);
  }
  else
  {
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
  }
}
