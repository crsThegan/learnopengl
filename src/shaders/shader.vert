#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = proj * view * model * vec4(aPos, 1.0);

	vec3 normal_world = mat3(transpose(inverse(model))) * aNormal;
	normal = vec3(view * vec4(normal_world, 0.0));

	fragPos = vec3(view * model * vec4(aPos, 1.0));
	texCoord = aTexCoord;
}
