#version 330

in vec2 texCoord_v;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D depthTex;
uniform mat4 depthviewMatrix;
uniform mat4 depthprojMatrix;
uniform mat4 biasMatrix;
out vec4 color_out;
uniform float screenW;
uniform float screenH;
uniform float Near;
uniform float Far;

float LinearizeDepth(vec4 pos)
{
  float n = Near; // camera z near
  float f = Far; // camera z far
  float z = pos.z;
  return (2.0 * n) / (f + n - z * (f - n));	
}


void main()
{	
	mat4 depthMVP = depthprojMatrix*depthviewMatrix;
	

	vec2 coord = texCoord_v;//vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	
	//vec3 pos = texture2D(diffuseTex,coord).xyz;
	vec3 normal = texture2D(normalTex,coord).xyz;
	vec3 pos = normal;
	vec3 test = texture2D(depthTex, coord).xyz;
	vec4 Shadowcoord = depthMVP*vec4(pos,1.);
	// Recupération de la couleur du pixel courant
	

	float visibility = 1.0;
	if ( texture(depthTex, Shadowcoord.xy).z  <  Shadowcoord.z){
	    visibility = 0.2;
	}
	color_out = vec4(pos, 1.0);//visibility);
}