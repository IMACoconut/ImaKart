#version 330

in vec2 texCoord_v;
uniform sampler2D diffuseTex;
out vec4 color_out;

void main()
{
	// Recupération de la couleur du pixel courant
	color_out = texture(diffuseTex, texCoord_v.xy);;
}