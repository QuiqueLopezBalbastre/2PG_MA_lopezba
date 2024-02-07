#version 330

layout(location = 0) out vec4 fragColor;

uniform vec3 u_camera_position;

in vec3 normal;
in vec3 pos;
uniform float u_time;

struct Light{
  vec3 direction;
  vec3 position;
  vec3 light_color;
  vec3 specular_color;
  vec3 spot_direction;
  float shininess;
  float spec_strength;
  float attenuation_linear;
  float attenuation_quadratic;
  float attenuation_constant;
  float cutoff;

  int type;
};

Light light[30];

void SetLights(){

  light[0].type = 1;
  light[0].position = vec3(sin(u_time * 0.001) * 900,370.0, 89.0 );
  light[0].direction = normalize(light[0].position - pos);
  light[0].light_color = vec3(1.0, 1.0, 0.0);
  light[0].specular_color = vec3(1.0, 1.0, 1.0);
  light[0].spot_direction = normalize(vec3(1.0, 0.0, 0.5));
  light[0].attenuation_linear = 0.0007;
  light[0].attenuation_quadratic = 0.00002;
  light[0].attenuation_constant = 1.0;
  light[0].cutoff = cos(radians(70.0));

  light[1].type = 2;
  light[1].position = vec3(130.0, 70.0, 140.0);
  light[1].direction = normalize(light[1].position - pos);
  light[1].light_color = vec3(1.0, 0.0, 0.0);
  light[1].specular_color = vec3(1.0, 1.0, 1.0);
  light[1].spot_direction = normalize(vec3(0.0, -1.0, 0.0));
  light[1].attenuation_linear = 0.007;
  light[1].attenuation_quadratic = 0.0002;
  light[1].attenuation_constant = 1.0;
  light[1].cutoff = cos(radians(60.0)); //cutoff

  light[2].type = 2;
  light[2].position = vec3(-240.0, 60.0, 140.0);
  light[2].direction = normalize(light[2].position - pos);
  light[2].light_color = vec3(1.0, 0.0, 0.0);
  light[2].specular_color = vec3(1.0, 1.0, 1.0);
  light[2].spot_direction = normalize(vec3(0.0, -1.0, 0.0));
  light[2].attenuation_linear = 0.007;
  light[2].attenuation_quadratic = 0.0002;
  light[2].attenuation_constant = 1.0;
  light[2].cutoff = cos(radians(60.0)); //cutoff

  light[3].type = 1;
  light[3].position = vec3(sin(u_time * 0.001) * -900,300.0, 89.0 );
  light[3].direction = normalize(light[3].position - pos);
  light[3].light_color = vec3(0.0, 1.0, 1.0);
  light[3].specular_color = vec3(1.0, 1.0, 1.0);
  light[3].spot_direction = normalize(vec3(0.0, 1.0, 0.0));
  light[3].attenuation_linear = 0.0007;
  light[3].attenuation_quadratic = 0.00002;
  light[3].attenuation_constant = 1.0;
  light[3].cutoff = cos(radians(60.0));

  light[4].type = 1;
  light[4].position = vec3(sin(u_time * 0.001) * -900,720.0, -500.0 );
  light[4].direction = normalize(light[4].position - pos);
  light[4].light_color = vec3(0.0, 1.0, 0.5);
  light[4].specular_color = vec3(1.0, 1.0, 1.0);
  light[4].spot_direction = normalize(vec3(0.0, -1.0, -1.0));
  light[4].attenuation_linear = 0.000022;
  light[4].attenuation_quadratic = 0.000019;
  light[4].attenuation_constant = 1.0;
  light[4].cutoff = cos(radians(75.0));

  light[5].type = 1;
  light[5].position = vec3(-1250,180.0, -50.0);
  light[5].direction = normalize(light[5].position - pos);
  light[5].light_color = vec3(1.0, 0.2, 0.5);
  light[5].specular_color = vec3(1.0, 1.0, 1.0);
  light[5].spot_direction = normalize(vec3(-1.0, -1.0, 0.0));
  light[5].attenuation_linear = 0.000022;
  light[5].attenuation_quadratic = 0.000019;
  light[5].attenuation_constant = 1.0;
  light[5].cutoff = cos(radians(75.0));

  light[6].type = 1;
  light[6].position = vec3(1050,170.0, -50.0);
  light[6].direction = normalize(light[6].position - pos);
  light[6].light_color = vec3(1.0, 0.2, 0.5);
  light[6].specular_color = vec3(1.0, 1.0, 1.0);
  light[6].spot_direction = normalize(vec3(1.0, -1.0, 0.0));
  light[6].attenuation_linear = 0.000022;
  light[6].attenuation_quadratic = 0.000019;
  light[6].attenuation_constant = 1.0;
  light[6].cutoff = cos(radians(75.0));

  light[7].type = 1;
  light[7].position = vec3(-1200,666.0, sin(u_time * 0.001) * 500.0);
  light[7].direction = normalize(light[7].position - pos);
  light[7].light_color = vec3(0.6, 0.3, 1.0);
  light[7].specular_color = vec3(1.0, 1.0, 1.0);
  light[7].spot_direction = normalize(vec3(-1.0, -1.0, -1.0));
  light[7].attenuation_linear = 0.000022;
  light[7].attenuation_quadratic = 0.000019;
  light[7].attenuation_constant = 1.0;
  light[7].cutoff = cos(radians(75.0));
}

vec3 AmbientLight()
{
  vec3 ambient_color = vec3(1.0,1.0,1.0);
  float ambient_power =0.1;
  return ambient_color * ambient_power;
}


vec3 DirectionalLight(Light used_light)
{
  vec3 light_color = used_light.light_color;
  vec3 light_dir = used_light.direction;

  vec3 specular_color = used_light.specular_color;

  float d =max(dot(light_dir,normal),0.0);
  vec3 diffuse = light_color * d;

  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float s = pow(max(dot(view_dir,reflect_dir),0.0),32.0);
  vec3 spec_color = used_light.specular_color * s;

  return diffuse + spec_color;
}

vec3 PointLight(Light used_light)
{
  vec3 light_color = used_light.light_color;
  vec3 specular_color = used_light.specular_color;
  vec3 light_pos = used_light.position;
  vec3 light_dir = used_light.direction;
  
  float constant = used_light.attenuation_constant;
  float linear = used_light.attenuation_linear;
  float quadratic = used_light.attenuation_quadratic;

  float distance = length(light_pos - pos);
  float attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

  float d = max(dot(light_dir,normal),0.0);
  vec3 diffuse = light_color * d * attenuation;

  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float s = pow(max(dot(view_dir,reflect_dir),0.0),32.0);
  vec3 spec_color = specular_color * s * attenuation;

  return diffuse + spec_color;
}

vec3 SpotLight(Light used_light)
{
   vec3 light_color = used_light.light_color;
  vec3 specular_color = used_light.specular_color;
  vec3 light_pos = used_light.position;
  vec3 light_dir = used_light.direction;
  
  float constant = used_light.attenuation_constant;
  float linear = used_light.attenuation_linear;
  float quadratic = used_light.attenuation_quadratic;

  float distance = length(light_pos - pos);
  float attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);


  // Definir la dirección del foco
  vec3 spot_direction = used_light.spot_direction;
  // Calcular el ángulo entre la dirección de la luz y la dirección del foco
  float spot_angle = dot(-light_dir, spot_direction);
  
  // Definir el ángulo máximo del cono del foco (por ejemplo, 30 grados)
  float spot_cutoff = used_light.cutoff;

  // Si el ángulo entre la dirección de la luz y la dirección del foco es menor que el ángulo máximo del cono,
  // entonces la luz está dentro del cono del foco
  float spot_factor = smoothstep(spot_cutoff, 1.0, spot_angle);

  // Aplicar la atenuación y el factor del cono del foco
  attenuation *= spot_factor;

  float d = max(dot(light_dir, normal), 0.0);
  vec3 diffuse = light_color * d * attenuation;

  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float s = pow(max(dot(view_dir, reflect_dir), 0.0), 32.0);
  vec3 spec_color = specular_color * s * attenuation;

  return diffuse + spec_color;
}

void main() {
  SetLights();
  
  vec3 color = SpotLight(light[1]);
   color += PointLight(light[0]);
   color += PointLight(light[2]);
   color += SpotLight(light[3]);
  color += SpotLight(light[4]);
  color += SpotLight(light[5]);
  color += SpotLight(light[6]);
   color += SpotLight(light[7]);
  fragColor = vec4(color, 1.0);

}
