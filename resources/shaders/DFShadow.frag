#version 330

out vec3 finalData;
in vec2 outUV;
in vec4 outColor;
in vec3 outNormal;
in vec3 outPosition;
in mat4 Shadowcoord;
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

vec3 depth() {
	float tmp = LinearizeDepth();//gl_FragCoord.z;//1 - texture2D(depthTex, outUV)/Far;
	return vec3(tmp,tmp,tmp);
}
void main() {
	float visibility = 1.0;
	if ( texture( depthTex, ShadowCoord.xy ).z  <  ShadowCoord.z){
	    visibility = 0.5;
	}
	


	finalData = depth()*pow(cosAlpha,5);
}