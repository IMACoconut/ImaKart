#version 330

out vec4 finalData[4];
in vec2 outUV;
in vec4 outColor;
in vec3 outNormal;
in vec3 outPosition;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D depthTex;
uniform float Near;
uniform float Far;

uniform float isLight;


float LinearizeDepth()
{
  float n = Near; // camera z near
  float f = Far; // camera z far
  float z = gl_FragCoord.z;
  return (2.0 * n) / (f + n - z * (f - n));	
}

float depth() {
	return LinearizeDepth();
}

void main() {
	finalData[0] = vec4(outPosition,isLightened);
	finalData[1] = vec4(texture2D(diffuseTex, outUV).rgb*outColor.rgb,1.f);
	finalData[2] = vec4(normalize(outNormal),1.f);
	finalData[3] = vec4(isLight, isLight, isLight, 1.f);
	gl_FragDepth = depth();
}
