#version 330

out vec3 finalColor;
out vec2 outUV;
out vec4 outColor;
out vec3 outNormal;
out vec3 outPosition;

void main() {
	finalColor = vec4(normalize(outPosition), 1.f);
}