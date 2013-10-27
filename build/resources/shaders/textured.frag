#version 330
in vec4 outColor;
out vec4 finalColor;
in vec2 uvCoord;
in vec3 outNormal;

uniform sampler2D textureChannel1;
uniform vec3 lightPos;

void main() {
	float coeff = dot(outNormal,lightPos);
	finalColor = /*texture2D(textureChannel1, uvCoord)*/outColor*coeff;
}