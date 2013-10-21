#version 330
in vec3 outColor;
out vec3 finalColor;
void main() {
	finalColor = vec4(outColor.rgb, 1.f);
}