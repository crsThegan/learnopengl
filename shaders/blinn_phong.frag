#version 330 core
out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightPos;

void main() {
	float ambientFactor = 0.1;
	vec3 ambient = ambientFactor * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularFactor = 0.5;

	vec3 viewDir = normalize(-fragPos);
	vec3 halfway = normalize(viewDir + lightDir);

	float spec = pow(max(dot(halfway, norm), 0.0), 128);
	vec3 specular = specularFactor * spec * lightColor;

	vec3 res = (ambient + diffuse + specular) * objectColor;
	fragColor = vec4(res, 1.0);
}
