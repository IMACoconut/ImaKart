#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 color;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;
out vec2 uvCoord;
out vec4 outColor;
out vec3 outNormal;

void main() {
	gl_Position = projMatrix*viewMatrix*modelMatrix*vec4(position, 1.f);
	outNormal = normal;
	outColor = color;
	uvCoord = uv;
}