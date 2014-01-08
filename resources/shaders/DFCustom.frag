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

float CalcShadowFactor(vec4 LightSpacePos)
{
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
    float Depth = texture(depthTex, UVCoords).x;
    if (Depth < (z + 0.00001))
        return 0.2;
    else
        return 1.0;
}

void main()
{	
	mat4 depthMVP = depthprojMatrix*depthviewMatrix;
	

	vec2 coord = texCoord_v;//vec2(gl_FragCoord.x/screenW, gl_FragCoord.y/screenH);
	
	vec3 pos = texture2D(diffuseTex,coord).xyz;
	vec3 normal = texture2D(normalTex,coord).xyz;
	vec4 Shadowcoord = depthMVP*vec4(pos,1.);
  Shadowcoord.z += 0.5;
	// Recupération de la couleur du pixel courant
	

	float visibility =CalcShadowFactor(Shadowcoord);// texture(depthTex, Shadowcoord.xy).x < Shadowcoord.z ? 0.2 : 1;
	color_out = vec4(visibility);
}