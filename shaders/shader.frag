#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texFace;
uniform sampler2D texContainer;

uniform float mixFactor;

void main() {
	vec2 magCoords = TexCoord * 2.0;
	FragColor = mix(texture(texFace, magCoords), texture(texContainer, TexCoord), mixFactor);
}
