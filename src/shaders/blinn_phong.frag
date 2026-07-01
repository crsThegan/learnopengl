#version 330 core
out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

struct Light {
	vec3 pos;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;
uniform Material material;

void main() {
	vec3 ambient = material.ambient * light.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.pos - fragPos);

	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	vec3 viewDir = normalize(-fragPos);
	vec3 halfway = normalize(viewDir + lightDir);

	float spec = pow(max(dot(halfway, norm), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * light.specular;

	vec3 res = ambient + diffuse + specular;
	fragColor = vec4(res, 1.0);
}
