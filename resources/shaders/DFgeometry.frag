#version 330

out vec3 finalData[4];
in vec2 outUV;
in vec4 outColor;
in vec3 outNormal;
in vec3 outPosition;
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
	finalData[0] = outPosition;
	finalData[1] = texture2D(diffuseTex, outUV).rgb;
	finalData[2] = vec3(normalize(outNormal));
	finalData[3] = depth();//texture2D(depthTex, outUV);//vec3(depth, depth, depth);
}