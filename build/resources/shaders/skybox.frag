#version 330

// Shader found on http://www.gamedev.net/topic/538429-day--night-cycle-sky-shader-for-you/

uniform sampler2D textureChannel1;
uniform sampler2D textureChannel2;

in vec3 vertexPos;
uniform vec3 lightPos;
out vec3 fFragColor;

float saturate(float value)
{
	return clamp(value,0.0,1.0);
}

void main()
{
	vec3 horizon = vec3(0.70, 0.40, 0.20);
	vec3 zenith = vec3(0.00, 0.34, 0.71);
    vec3 V = normalize(vertexPos);
    vec3 L = normalize(lightPos);

    // Compute the proximity of this fragment to the sun.
    float sundot = dot(V, L);

    // Sun and Moon.
    vec3 light = 0.8f * pow( max(0.0001, sundot), 360.0f );
    vec3 moon  = 0.3f * pow( max(0.0, dot(-L, V)), 60.0f );

    float curve = 0.25f * (2.0f - L.y);
    vec3 sky = zenith * (1-curve) + horizon * curve;
    sky = sky * (1+sundot) + zenith * -sundot;
    sky *= saturate(L.y+2.0);

    fFragColor = sky + light + moon;
}