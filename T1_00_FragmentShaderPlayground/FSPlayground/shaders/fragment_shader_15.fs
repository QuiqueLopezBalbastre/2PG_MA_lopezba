#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

void main() {

  vec2 center = u_window_size * 0.5;
  float big_radius = 180.0;
  float petit_radius = 100.0;

  float distance = length(gl_FragCoord.xy - center);
  float outer = step(distance, big_radius);
  float inner = step(petit_radius, distance);

  vec3 background_color = vec3(0.878, 0.894, 0.803);
  vec3 outer_color = vec3(0.89, 0.55, 0.27);
  vec3 inner_color = vec3(0.45, 0.79, 0.82);

  float alpha = clamp((distance - petit_radius) / (big_radius - petit_radius), 0.0, 1.0);
  vec3 color = mix(inner_color, outer_color, alpha) * outer * inner;
  color = mix(background_color, color, outer * inner);

  fragColor = vec4(color, 1.0);

}