#version 330
in vec4 outColor;
out vec4 finalColor;
void main() {
	finalColor = vec4(outColor.r,outColor.g,outColor.b,outColor.a);
}