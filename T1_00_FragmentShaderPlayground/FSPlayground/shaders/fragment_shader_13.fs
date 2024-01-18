#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;
#define PI 3.141692

void main() {

  float stripes_x = 24.0;
  float stripes_y = 14.0;

  float x = gl_FragCoord.x / u_window_size.x;
  float y = gl_FragCoord.y / u_window_size.y;
  
  float stripeX = (round(sin(x * 2.0 * PI * stripes_x) * 0.5 + 0.5) - 1.0) * (-1.0);
  float stripeY = (round(sin(y * 2.0 * PI * stripes_y) * 0.5 + 0.5) - 1.0) * (-1.0);
  
  float alpha = 1.0;


  fragColor = vec4(stripeX * stripeY, stripeX * stripeY, stripeX * stripeY, alpha);

}