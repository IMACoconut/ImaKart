#version 330

in vec2 texCoord_v;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D depthTex;
out vec4 color_out;

void main()
{
	float visibility = texture( depthTex, texture2D(depthTex, texCoord_v).xyz );
	// Recupération de la couleur du pixel courant
	color_out = texture2D(diffuseTex, texCoord_v)*texture2D(normalTex, texCoord_v);
}