#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {

  float stripewidth = 0.01;

  float red = mod(((gl_FragCoord.x / u_window_size.x) * (gl_FragCoord.y/ u_window_size.y)), stripewidth * 2);
  red = step(red, stripewidth);

  float green = mod((gl_FragCoord.x / u_window_size.x) * (gl_FragCoord.y/ u_window_size.y), stripewidth * 2) ;
  green = step(green, stripewidth);
  
  float blue = mod((gl_FragCoord.x / u_window_size.x) * (gl_FragCoord.y/ u_window_size.y), stripewidth * 2) ;
  blue = step(blue, stripewidth);
  
  float alpha = 1.0;


  fragColor = vec4(red, green, blue, alpha);

}