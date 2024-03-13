
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 projection;

out vec3 normal;
out vec3 position;

void main()
{
	gl_Position = projection * model * vec4(aPos, 1.0f);
	normal = mat3(model) * aNorm;
	position = vec3(mat3(model) * aPos);
}


