#version 330

out vec4 finalData;
in vec2 outUV;
in vec4 outColor;
in vec4 outNormal;
in vec4 outPosition;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D depthTex;
uniform float Near;
uniform float Far;

float LinearizeDepth()
{
  float n = Near; // camera z near
  float f = Far; // camera z far
  float z = gl_FragCoord.z;
  return (2.0 * n) / (f + n - z * (f - n));	
}

vec4 depth() {
	float tmp = LinearizeDepth();//gl_FragCoord.z;//1 - texture2D(depthTex, outUV)/Far;
	return vec4(tmp,tmp,tmp,tmp);
}
void main() {

	finalData = vec4(gl_FragCoord.z); 
}