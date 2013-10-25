#version 330
in vec4 outColor;
out vec4 finalColor;
in vec2 uvCoord;

uniform sampler2D textureChannel1;

void main() {
	finalColor = texture2D(textureChannel1, uvCoord)*outColor;
}	