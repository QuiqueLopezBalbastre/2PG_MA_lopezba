
#version 330 core
out vec4 FragColor;

uniform vec4 RawColor;

in vec3 position;
in vec3 normal;

void main()
{
	vec3 point_light_pos = vec3(0.0, 2.0,2.0);
	vec3 light_pos = normalize(point_light_pos - position);
	float light = dot(normalize(normal), light_pos);
	FragColor = RawColor * vec4(light, light, light, 1.0) ; 
}

