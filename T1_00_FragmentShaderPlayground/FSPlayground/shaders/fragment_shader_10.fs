#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;
#define PI 3.141592


void main() {

    float red = clamp(sin(PI * 20.0 * (gl_FragCoord.x/u_window_size.x)), 0.0, 1.0);
    float green = 0.0;
    float blue = 0.0;
    float alpha = 1.0;

    fragColor = vec4(red, green, blue, alpha);
}
