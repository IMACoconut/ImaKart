#version 330

// Shader found on http://www.gamedev.net/topic/538429-day--night-cycle-sky-shader-for-you/

uniform sampler2D textureChannel1;
uniform sampler2D textureChannel2;

in vec3 vertexPos;
in vec3 vertexNorm;
uniform vec3 lightPos;
uniform float Near;
uniform float Far;

out vec4 finalData[4];

float saturate(float value)
{
	return clamp(value,0.0,1.0);
}

void main()
{
	vec3 horizon = vec3(0.70, 0.40, 0.20);
	vec3 zenith = vec3(0.00, 0.44, 0.81);
	vec3 night = vec3(0.0156, 0.1019, 0.1843);
	vec3 N = normalize(vertexNorm);
    vec3 V = normalize(vertexPos);
    vec3 L = normalize(lightPos);

    // Compute the proximity of this fragment to the sun.
    float sundot = dot(N, L);

    // Sun and Moon.
    vec3 moon =  0.8f * vec3(pow( max(0.0001, dot(-L, N)), 360.0f )); 
    vec3 light  = 0.8f * vec3(pow( max(0.0001, sundot), 360.0f ));
   	
   	vec3 c1 = night;// - abs(sundot)*horizon;
    vec3 c2 = zenith;// - abs(sundot)*horizon;
    vec3 c3 = horizon;
    float sun2 = (sundot+1)/2;
    vec3 color;
	

   	float atten = 1-abs(L.y);
   	float dist = length(V-L);
   	color = (c1*sun2+ c2*(1-sun2))*(1-atten) + c3*(atten);



    float curve = 0.25f* (2.0f - L.y);
    vec3 sky = color * (1-curve);
    //sky = sky * (1+sundot) + color * -sundot;
    sky *= saturate(L.y+2.0);

	//vec3 sky = c2;

    finalData[0] = vec4(vertexPos,1.f);
    finalData[1] = vec4((sky + moon + light), 1.f);
    finalData[2] = vec4(normalize(vertexNorm),1.f);
    finalData[3] = vec4(Far-1, Far-1, Far-1,1.f);
    //finalData[1] = vec4(N, 1.f);
}