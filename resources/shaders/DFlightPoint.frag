#version 330

out vec4 finalData;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform float Near;
uniform float Far;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float lightRadius;
uniform float screenW;
uniform float screenH;

float celShad(float val) {
	if(val >= 0.7)
		return 1.f;
	if(val >= 0.5)
		return 0.5f;
	if(val >= 0.2)
		return 0.2f;
	return 0.f;
}

float DirectIllumination(vec3 P, vec3 L, float R)
{
	float d = length(P-L);
	return 1/(pow(d/R +1, 2));
}

bool isLightened(vec3 light, vec3 point) {
	return distance(light, point) < lightRadius;
}

float attenuation(vec3 from, vec3 to, float radius) {
	float l = distance(from, to);

	if(l > radius)
		return 0.f;

	return max(((radius-l)*(radius-l))/(radius*radius),0.f);
}

float scal(vec3 N, vec3 dir) {
	return max(dot(N, dir),0);
}

void main() {
	vec2 coord = vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	vec3 pos = texture2D(diffuseTex,coord).rgb;
	vec3 N = normalize(texture2D(normalTex,coord).rgb);
	vec3 dir = normalize(lightPos-pos);
	float scalaire = max(scal(N,dir),0);
	finalData = vec4(lightColor*lightIntensity*scalaire*celShad(attenuation(pos, lightPos, lightRadius)),1.f);
}