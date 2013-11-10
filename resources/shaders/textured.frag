#version 330
in vec4 outColor;
out vec4 finalColor;
in vec2 uvCoord;
in vec3 outNormal;

uniform sampler2D textureChannel1;
uniform vec3 lightPos;
uniform vec3 eyeDir;

void main() {
	float coeff = dot(normalize(lightPos),normalize(outNormal));// * dot(normalize(-eyeDir), normalize(outNormal));

	float t = coeff;
	
// Uncomment for cell-shading
//*
	if(coeff >= 0.5)
		t = 1;
	else if(coeff > 0.4)
		t = 0.4;
	else if(coeff > 0)
		t = 0.2;
	else
		t = 0.1;
//*/
	finalColor = texture2D(textureChannel1, uvCoord)*outColor*t;
}