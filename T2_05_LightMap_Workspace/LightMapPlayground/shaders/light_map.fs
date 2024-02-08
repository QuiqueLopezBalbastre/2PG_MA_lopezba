#version 330
layout(location = 0) out vec4 fragColor;
uniform vec3 u_camera_position;
uniform float u_time;
in vec2 uv;
in vec3 pos;
in vec3 normal;

//Textures:
uniform sampler2D u_albedo_texture;
uniform sampler2D u_specular_texture;

struct Light {
  vec3 direction;
  vec3 position;
  vec3 light_color;
  vec3 specular_color;
  vec3 spot_direction;
  float spec_strength;
  float attenuation_linear;
  float attenuation_quadratic;
  float attenuation_constant;
  float cutoff;

  int type;
};

void SetLights(out Light light) {

  light.position = vec3(-3.0,0.0,0.0);
  light.direction = normalize(light.position - pos);
  light.light_color = vec3(1.0, 0.0, 0.0);
  light.specular_color = vec3(1.0, 1.0, 1.0);
  light.attenuation_linear = 0.0007;
  light.attenuation_quadratic = 0.00002;
  light.attenuation_constant = 1.0;
}

//Función limpia de PointLight
vec3 PointLight(Light light) {
  float distance = length(light.position - pos);
  float attenuation = 1.0 / (light.attenuation_constant + light.attenuation_linear * distance + light.attenuation_quadratic * distance * distance);

  float d = max(dot(light.direction, normal), 0.0);
  vec3 diffuse = light.light_color * d * attenuation;

  vec3 view_dir = normalize(u_camera_position - pos);
  vec3 reflect_dir = reflect(-light.direction, normal);
  float s = pow(max(dot(view_dir, reflect_dir), 0.0), 32.0);
  vec3 spec_color = light.specular_color * s * attenuation;

  return diffuse + spec_color;
}


void main() {
  Light point;
  SetLights(point);
  vec3 color = PointLight(point);
  //vec4 color = vec4(PointLight(point), 0.0);
  fragColor = texture(u_albedo_texture, uv) * vec4(color,0.0);
}
