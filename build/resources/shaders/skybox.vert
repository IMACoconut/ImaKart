#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 color;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;

out vec3 vertexPos;
void main() {
	gl_Position = projMatrix*viewMatrix*vec4(position*10000, 1.f);
	vertexPos = normal;
}