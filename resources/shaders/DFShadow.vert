#version 330
layout(location = 0) in vec3 position;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;
uniform mat4 biasMatrix;
uniform vec3 eyeDir;
out vec4 Shadowcoord;

void main() {
	mat4 MVP = projMatrix*viewMatrix*modelMatrix;
	gl_Position = MVP*vec4(position, 1.f);
	Shadowcoord = biasMatrix*MVP*vec4(position, 1.f);
}
