#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;


main()
{

  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;
  float alpha = 1.0;


  


  fragColor = vec4(red, green, blue, alpha);
}


