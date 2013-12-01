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

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float lightRadius;
uniform float lightIntensity;
uniform float screenW;
uniform float screenH;

bool isLightened(vec3 point) {
	vec3 x = lightPos;
	vec3 dir = lightDir;
	float h = length(lightDir);
	float r = lightRadius/2;
	vec3 xPoint = point-x;

	float cone_dist = dot(xPoint, dir);
	if(cone_dist < 0 || cone_dist > h)
		return false;

	float cone_radius = (cone_dist/h)*r;
	float distRadius = cone_dist*cone_dist + cone_radius*cone_radius;
	return distRadius > length(xPoint)*length(xPoint);
}

void main() {
	vec2 coord = vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	vec3 pos = texture2D(diffuseTex, coord).xyz;
	vec3 N = normalize(texture2D(normalTex,coord).xyz);
	vec3 L = normalize(lightDir);
	vec3 dir = pos-lightPos;
	vec3 D = normalize(dir);

	if(isLightened(pos)) {
		finalData[0] = vec3(0,1,0);
	} else {
		finalData[0] = vec3(1,0,0);
	}	
}