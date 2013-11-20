#version 330

out vec3 finalData[2];
in vec2 outUV;
in vec4 outColor;
in vec3 outNormal;
in vec3 outPosition;
uniform sampler2D normalTex;
uniform float Near;
uniform float Far;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float screenW;
uniform float screenH;

void main() {
	vec2 coord = vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	vec3 N = normalize(texture2D(normalTex,coord).xyz);
	vec3 L = normalize(-lightDir);
	float scal = dot(N,L);
	finalData[0] = lightColor*lightIntensity*dot(L,N);
}