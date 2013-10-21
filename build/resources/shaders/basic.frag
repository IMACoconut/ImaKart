#version 330
in vec3 outColor;
out vec3 finalColor;
void main() {
	finalColor = vec4(outColor.r*.2, outColor.g*.76, outColor.b*1, 1.f);
}