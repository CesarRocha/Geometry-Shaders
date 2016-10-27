#version 330 core


uniform sampler2D gTexDiffuse;
uniform sampler2D gTexNormal;
uniform float gTime;

in vec3 passPosition;
in vec2 passUV0;
in vec4 passColor;

out vec4 outColor;

const float cPI = 3.1456;

void main (void)
{
	vec2 flipUV0 = passUV0;
	flipUV0.y *= -1.0;

	vec4 diffuseTexel = texture(gTexDiffuse, flipUV0);
	vec4 normalTexel  = texture( gTexNormal, passUV0 );

	vec3 finalColor = vec3(0.0);

	float final_alpha = (diffuseTexel.a * passColor.a); 
	
	finalColor = diffuseTexel.rgb;

	outColor = vec4( finalColor, final_alpha );
}