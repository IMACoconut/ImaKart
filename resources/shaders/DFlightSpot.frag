#version 330

out vec4 finalData;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;

uniform float Near;
uniform float Far;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float lightRadius;
uniform float lightIntensity;
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

float isLightened(vec3 point) {
	vec3 x = lightPos;
	vec3 dir = normalize(lightDir);
	float h = length(lightDir);
	float r = lightRadius;
	vec3 xPoint = point-x;
	float xPointLen = length(xPoint);

	float cone_dist = dot(xPoint, dir);
	if(cone_dist < 0 || cone_dist > h)
		return 0.f;

	float cone_radius = (cone_dist/h)*r;
	float distRadius = cone_dist*cone_dist + cone_radius*cone_radius;
	float tmp = (distRadius - xPointLen*xPointLen);
	if(tmp < 0)
		return 0.f;
	return sqrt(tmp)/r;
}

void main() {
	vec2 coord = vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	vec3 pos = texture2D(diffuseTex, coord).xyz;

	vec3 N = normalize(texture2D(normalTex,coord).rgb);

	vec3 L = normalize(-lightDir);
	vec3 dir = pos-lightPos;
	vec3 D = normalize(dir);

	finalData = vec4(lightColor*lightIntensity*max(dot(L,N),0)*celShad(isLightened(pos)), 1.f);
}
