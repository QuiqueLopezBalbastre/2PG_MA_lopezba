#version 330

layout(location = 0) out vec4 fragColor;

uniform vec3 u_camera_position;

in vec3 normal;
in vec3 pos;

vec3 AmbientLight()
{
  vec3 ambient_color = vec3(1.0,1.0,1.0);
  float ambient_power =0.1;
  return ambient_color * ambient_power;
}

vec3 DirectionalLight()
{
  vec3 light_color = vec3(0.0,1.0,0.5);
  vec3 light_dir = vec3(1.0,0.0,0.0);

  vec3 specular_color = vec3(1.0,1.0,1.0);

  float d = max(dot(light_dir,normal),0.0);
  vec3 diffuse = light_color * d;

  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float s = pow(max(dot(view_dir,reflect_dir),0.0),32.0);
  vec3 spec_color = specular_color * s;

  return diffuse + spec_color;
}

vec3 PointLight()
{
  vec3 light_color = vec3(0.0,1.0,0.5);
  vec3 specular_color = vec3(1.0,1.0,1.0);
  vec3 light_pos = vec3(-1.0,0.0,0.0);
  vec3 light_dir = normalize(light_pos - pos);
  

  float d =max(dot(light_dir,normal),0.0);
  vec3 diffuse = light_color * d;

  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float s = pow(max(dot(view_dir,reflect_dir),0.0),32.0);
  vec3 spec_color = specular_color * s;

  return diffuse + spec_color;
}

void main() {


  //vec3 color = DirectionalLight();
 //color += AmbientLight();
 vec3 color = PointLight();
  fragColor = vec4(color, 1.0);

}
