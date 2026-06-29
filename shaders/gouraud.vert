#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightPos;

void main() {
	gl_Position = proj * view * model * vec4(aPos, 1.0);

	vec3 normal_world = mat3(transpose(inverse(model))) * aNormal;
	vec3 normal = vec3(view * vec4(normal_world, 0.0));

	vec3 vertPos = vec3(view * model * vec4(aPos, 1.0));

	// Lighting

	float ambientFactor = 0.1;
	vec3 ambient = ambientFactor * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - vertPos);

	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularFactor = 0.5;

	vec3 viewDir = normalize(-vertPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularFactor * spec * lightColor;

	color = (ambient + diffuse + specular) * objectColor;
}
