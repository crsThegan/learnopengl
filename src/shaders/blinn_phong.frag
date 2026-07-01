#version 330 core
out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

struct Light {
	vec3 pos;
	vec3 dir;

	float cutoff;
	float outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Light light;

uniform Material material;

void main() {
	vec3 texDiff = vec3(texture(material.diffuse, texCoord));
	vec3 texSpec = vec3(texture(material.specular, texCoord));

	vec3 lightDir = normalize(light.pos - fragPos);
	//vec3 lightDir = normalize(-light.dir);

	float theta = dot(lightDir, normalize(-light.dir));
	if (theta < light.outerCutoff) {
		fragColor = vec4(light.ambient * texDiff, 1.0);
		return;
	}

	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	vec3 ambient = texDiff * light.ambient;

	vec3 norm = normalize(normal);

	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * texDiff * light.diffuse;

	vec3 viewDir = normalize(-fragPos);
	vec3 halfway = normalize(viewDir + lightDir);

	float spec = pow(max(dot(halfway, norm), 0.0), material.shininess);
	vec3 specular = texSpec * spec
		* light.specular;

	float dist = length(light.pos - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist
			+ light.quadratic * pow(dist, 2));

	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	vec3 res = ambient + diffuse + specular;
	fragColor = vec4(res, 1.0);
}
