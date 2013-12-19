#version 330

out vec4 fragData[3];

void main() {
	fragData[0] = vec4(0,0,0,1);
	fragData[1] = vec4(0,0,0,1);
	fragData[2] = vec4(0,0,0,1);
	gl_FragDepth = 1.0f;
}