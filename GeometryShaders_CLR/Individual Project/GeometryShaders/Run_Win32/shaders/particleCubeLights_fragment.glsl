#version 330 core

//Textures
uniform sampler2D	gTexDiffuse; 
uniform sampler2D	gTexNormal;
uniform sampler2D	gTexSpecular;
uniform sampler2D	gTexEmissive;
uniform sampler2D	gTexEmissive2;	
uniform sampler2D	gTexDepth;	

//Material
uniform vec4  gMaterialAmbientLight; 
uniform float gShininess;

//Light
const int numberOfLights = 16;
uniform int gLightCount = 16;
uniform struct Light
{
vec3  gLightPosition;
vec4  gLightColor;
vec3  gLightDirection;

float	gLightAmbient;
float	gLightWeight;
float	gLightAngle;
float	gLightSpotPower;
float	gLightMinSf;
float	gLightMinIntensity;
float	gLightMaxIntensity;
}lights[numberOfLights];


//Fog
uniform float gFogStart;
uniform float gFogEnd;
uniform vec3  gFogColor;

//Camera
uniform vec3 gCameraPosition;

//Verts
in vec3 passPosition;
in vec2 passUV0;

//Result
out vec4 outColor;

struct LightOutput
{
	vec3 LightIntensity;
	vec3 LightVector;
};

LightOutput ComputeALight(const Light light, const vec3 normal)
{
		LightOutput outLight;
		
		vec3  Lvector = light.gLightPosition - passPosition;
		float dist = length(Lvector);

		Lvector = light.gLightWeight * (Lvector / dist) - (1-light.gLightWeight) * light.gLightDirection;

		float Sa = dot( -Lvector, light.gLightDirection);
		float Sc = step(light.gLightAngle, Sa);
		float Sf = Sc * max( Sa, light.gLightMinSf);
		float power = light.gLightColor.w;
		vec3  Lcolor = light.gLightColor.xyz;
		float Li = 1.0;// clamp(power/ dist * Sf, light.gLightMinIntensity, light.gLightMaxIntensity);
		
		outLight.LightIntensity = Li * Lcolor;
		outLight.LightVector = Lvector;
		return outLight;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void main( void )
{
   vec3 diffuse = texture( gTexDiffuse, passUV0 ).xyz;
   vec3 normal = texture( gTexNormal, passUV0 ).xyz;
   normal = normalize(normal);


//Ambient
	vec3 ambient = (gMaterialAmbientLight * gMaterialAmbientLight.a).xyz;
   vec3 final_color = vec3(0.0f);
	final_color = (ambient * diffuse);
	
//Begin computing lights
	vec3 total_diffuse = vec3(0.0f);
	for( int i = 0; i < numberOfLights; i++)
	{
		LightOutput outLight = ComputeALight( lights[i], normal );

		total_diffuse += outLight.LightIntensity * clamp( dot(normal, outLight.LightVector), 0.0, 1.0);
	}

	total_diffuse = clamp( total_diffuse, vec3(0.0f), vec3(1.0f) );
	final_color += (total_diffuse * diffuse.rgb);
    outColor = vec4( final_color, 1.0f );
}