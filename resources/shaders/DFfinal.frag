#version 330

in vec2 texCoord_v;
in vec4 Shadowcoord;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
out vec4 color_out;

void main()
{
	
	// Recupération de la couleur du pixel courant
	color_out = texture2D(diffuseTex, texCoord_v)*texture2D(normalTex, texCoord_v);
}