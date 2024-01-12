#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;
#define PI 3.141592

void main() {
    float red = cos(PI * 20.0 * (gl_FragCoord.x/u_window_size.x));
    float green = cos(PI * 20.0 * (gl_FragCoord.y / u_window_size.y));
    float blue = 0.0;
    float alpha = 0.0;

    fragColor = vec4(red, green, blue, alpha);
}
/*
void main() {
  float stripeWidth = 0.1;
  
  float stripe = mod(gl_FragCoord.x / u_window_size.x, stripeWidth * 2);
  float r = step(stripeWidth, stripe);

  fragColor = vec4(r, 0.0, 0.0, 1.0);
}
*/