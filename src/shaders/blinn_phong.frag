#version 330 core
out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;

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
	vec3 texDiff = vec3(texture(material.diffuse, texCoord));
	vec3 texSpec = vec3(texture(material.specular, texCoord));

	float woodMask = 1.0 - step(0.01, length(texSpec));
	vec3 emission = vec3(texture(material.emission, texCoord)) * woodMask;

	vec3 ambient = texDiff * light.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.pos - fragPos);

	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * texDiff * light.diffuse;

	vec3 viewDir = normalize(-fragPos);
	vec3 halfway = normalize(viewDir + lightDir);

	float spec = pow(max(dot(halfway, norm), 0.0), material.shininess);
	vec3 specular = texSpec * spec
		* light.specular;

	vec3 res = ambient + diffuse + specular + emission;
	fragColor = vec4(res, 1.0);
}
