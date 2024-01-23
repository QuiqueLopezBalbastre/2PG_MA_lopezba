#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;
#define PI 3.141592

void main() {
    float red = cos(PI * 5.0 * ((gl_FragCoord.y / u_window_size.y) + 1.5 * (gl_FragCoord.x / u_window_size.x)));
    float green = cos(PI * 5.0 * ((gl_FragCoord.y / u_window_size.y) + 1.5 *(gl_FragCoord.x / u_window_size.x)));
    float blue = 0.0;
    float alpha = 0.0;

    fragColor = vec4(red, green, blue, alpha);
}
