#version 330
in vec4 outColor;
out vec4 finalColor;
in vec2 uvCoord;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform vec3 lightPos;

void main() {
	/*vec3 normal = normalize(2.0 * texture2D (normalTexture, uvCoord.st).rgb - 1.0);

	float lamberFactor= max (dot (lightPos, normal), 0.0) ;
	vec4 diffuseMaterial = 0.0;
	vec4 diffuseLight  = 0.0;
	
	// compute specular lighting
	vec4 specularMaterial ;
	vec4 specularLight ;
	float shininess ;
  
	// compute ambient
	vec4 ambientLight = gl_LightSource[0].ambient;	
	
	if (lamberFactor > 0.0)
	{
		diffuseMaterial = texture2D (diffuseTexture, gl_TexCoord[0].st);
		diffuseLight  = gl_LightSource[0].diffuse;
		
		// In doom3, specular value comes from a texture 
		specularMaterial =  vec4(1.0)  ;
		specularLight = gl_LightSource[0].specular;
		shininess = pow (max (dot (halfVec, normal), 0.0), 2.0)  ;
		 
		gl_FragColor =	diffuseMaterial * diffuseLight * lamberFactor ;
		gl_FragColor +=	specularMaterial * specularLight * shininess ;				
	
	}
	
	gl_FragColor +=	ambientLight;*/
}