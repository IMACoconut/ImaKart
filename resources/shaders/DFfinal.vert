#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;
out vec2 texCoord_v;

void main()
{
	texCoord_v = uv;
	gl_Position =  vec4(position, 1.0);
}
