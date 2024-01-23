#version 330

uniform vec4 u_color;
uniform float u_time;
//In this demo, the window has the following size:
// 1200 x 700
uniform vec2 u_window_size;
out vec4 fragColor;

<<<<<<< HEAD

main()
{

  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;
  float alpha = 1.0;


  


  fragColor = vec4(red, green, blue, alpha);
}


=======
void main() {

  vec2 center = u_window_size * 0.5;

  float distance_x = abs(gl_FragCoord.x - center.x);
  float distance_y = abs(gl_FragCoord.y - center.y);
  
  float y = float(distance_x == distance_y);

  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;  
  float alpha = 1.0;


  fragColor = vec4(y, y, blue, alpha);

}
>>>>>>> 39856f3bbf7b422bd542eb3a66deec0fa5a34ddb
