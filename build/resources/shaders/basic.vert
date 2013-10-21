#version 330
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;
out vec3 outColor;
void main() {
	gl_Position = vec4(position, 0.f, 1.f);
	outColor = color;
}