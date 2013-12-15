#version 330
layout(location = 0) in vec3 position;
uniform mat4 depthviewMatrix;
uniform mat4 depthprojMatrix;
uniform mat4 depthmodelMatrix;
uniform mat4 biasMatrix;
uniform vec3 eyeDir;
out vec4 Shadowcoord;

void main() {
	mat4 depthMVP = depthprojMatrix*depthviewMatrix*depthmodelMatrix;
	gl_Position = depthMVP*vec4(position, 1.f);
	Shadowcoord = biasMatrix*depthMVP*vec4(position, 1.f);
}
