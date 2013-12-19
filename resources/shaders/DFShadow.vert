#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
uniform mat4 depthviewMatrix;
uniform mat4 depthprojMatrix;
uniform mat4 depthmodelMatrix;
uniform mat4 biasMatrix;
uniform vec3 eyeDir;
out vec4 Shadowcoord;
out vec4 outPosition;
out vec4 outNormal;

void main() {
	mat4 depthMVP = depthprojMatrix*depthviewMatrix*depthmodelMatrix;
	gl_Position = depthMVP*vec4(position, 1.f);
	outPosition = depthMVP*vec4(position, 1.f);
	outNormal = depthmodelMatrix*vec4(normal, 1.f);
	
}
