#version 330

out vec3 finalData[2];
in vec2 outUV;
in vec4 outColor;
in vec3 outNormal;
in vec3 outPosition;
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

bool isLightened(vec3 light, vec3 point) {
	return distance(light, point) < lightRadius;
}

float attenuation(vec3 from, vec3 to) {
	float l = distance(from, to);
	float tmp = (lightRadius-l)/lightRadius;
	return tmp;
}

float scal(vec3 N, vec3 dir) {
	float tmp = dot(N, dir);
	if(tmp > 0)
		return tmp;
	else 
		return 0.f;
}

void main() {
	vec2 coord = vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	vec3 pos = texture2D(diffuseTex,coord).xyz;
	vec3 N = normalize(texture2D(normalTex,coord).xyz);
	vec3 dir = normalize(lightPos-pos);
	float scalaire = scal(N,dir);
	if(isLightened(lightPos, pos)) {
		finalData[0] = lightColor*lightIntensity*scalaire*attenuation(lightPos, pos);
	} else {
		finalData[0] = vec3(0,0,0);
	}
}