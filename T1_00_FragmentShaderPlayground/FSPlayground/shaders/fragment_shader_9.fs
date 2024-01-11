#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {
    fragColor = vec4(step(0.5, gl_FragCoord.x / u_window_size.x)  ,
                     step(0.5, gl_FragCoord.y / u_window_size.y),
                     0.0,
                     1.0);
}
