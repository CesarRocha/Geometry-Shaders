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
in vec3 passNormal;
in vec3 passTangent;
in vec3 passBiTangent;
in float passDistToCamera;

//Result
out vec4 outColor;


////------------------------------------------------------------------------
vec3 ComputeDiffuse( vec3 surfaceToLight,  vec3 light_color, float power, vec3 n )
{
	   // DIFFUSE
	   float dist2 = dot( surfaceToLight, surfaceToLight );
	   power = power / dist2;
	   float idist = inversesqrt(dist2);
	   surfaceToLight = surfaceToLight * idist;
	   float ndotl = dot( n, surfaceToLight );
	   float intensity = clamp( ndotl * power, 0.0, 1.0 );
	   vec3 diffuse = intensity * light_color;
	   return diffuse;
}
////------------------------------------------------------------------------
vec3 ComputeSpecular(vec3 surfaceToLight, vec3 surfaceToCamera, vec3 light_color,vec3 normal, float shininess)
{
		//SPECULAR
		vec3 Lm = normalize(surfaceToLight);
		float temp = 2.0f*dot(Lm,normal);
		vec3 Rm = normalize(temp * normal - Lm);
		temp = dot(Rm, normalize(surfaceToCamera));
		temp = pow(temp, shininess);


		vec3 final_color = clamp(temp * light_color,0,1);
		return final_color;
		//return  vec3(2 * normal * (dot(normal, surfaceToLight), - surfaceToLight)); //This is cool!

}

vec3 ComputeSpecularEnhanced(const vec3 surfaceToLight, const vec3 surfaceToCamera, const Light light, const vec3 normal)
{
		//SPECULAR_ENCHANCED
		vec3  Lvector = light.gLightPosition - passPosition;
		float dist = length(light.gLightPosition - passPosition);
		Lvector = light.gLightWeight * (Lvector / dist) - (1-light.gLightWeight) * light.gLightDirection;
		float Sa = dot( Lvector, light.gLightDirection);
		float Sc = step(light.gLightAngle, Sa);
		float Sf = Sc * max( pow(Sa, light.gLightSpotPower), light.gLightMinSf);
		float power = light.gLightColor.w;
		vec3  Lcolor = light.gLightColor.xyz;
		float Li = clamp(power/ dist * Sf, light.gLightMinIntensity, light.gLightMaxIntensity);
		
		
		vec3 Lm = normalize(surfaceToLight);
		float temp = 2.0f*dot(Lm,normal);
		vec3 Rvector = normalize(temp * normal - Lm);
		temp = dot(Rvector, normalize(surfaceToCamera));
		temp = pow(temp, gShininess);
		
		
		vec3 final_light = clamp(temp * light.gLightColor.xyz,0,1);

		return final_light;

}

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
		float Li = clamp(power/ dist * Sf, light.gLightMinIntensity, light.gLightMaxIntensity);
		
		outLight.LightIntensity = Li * Lcolor;
		outLight.LightVector = Lvector;
		return outLight;
}

vec3 ComputeToonShading(vec3 normal)
{
		vec3 color;
		vec3 EyeVert = normalize(gCameraPosition - passPosition);
		float intensity = max(dot(normal,EyeVert), 0.0);
		if (intensity > 0.95)
			color = vec4(1.0,0.5,0.5,1.0).xyz;
		else if (intensity > 0.5)
			color = vec4(0.6,0.3,0.3,1.0).xyz;
		  else if (intensity > 0.25)
			color = vec4(0.4,0.2,0.2,1.0).xyz;
		 else
			color = vec4(0.2,0.1,0.1,1.0).xyz;
		return color;
}

vec4 WorldUnitVectorToColor( vec3 n ) 
{
	vec3 c = (n + vec3(1.0f)) * .5f;
	return vec4(c, 1.0f);
}

vec3 BandVec3( vec3 v, float num_bands ) 
{
    vec3 c = v * vec3(num_bands + 1.0f);
	c = min( floor(c), vec3(num_bands) );
	c = c / vec3(num_bands);
	return c;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void main( void )
{
	vec3 surfaceToCamera = gCameraPosition - passPosition;
	vec3 eyeVector = normalize(surfaceToCamera);

	vec3 final_color = vec3(0.0f);
	vec2 flipped_texcoord = vec2(passUV0.x, 1.0 - passUV0.y); //flips the texture. Was upside down.	
	vec3 normal		= texture( gTexNormal,   flipped_texcoord ).xyz;
	vec3 diffuse	= texture( gTexDiffuse,  flipped_texcoord ).xyz;
	vec3 specular	= texture( gTexSpecular, flipped_texcoord ).xyz;

	normal = normal * vec3(2.0f, 2.0f, 1.0f) - vec3(1.0f, 1.0f, 0.0f);
	mat3 TBN = mat3(passTangent,passBiTangent,passNormal);
	normal = TBN * normal;
	normal = normalize(normal);

	//Ambient
	vec3 ambient = (gMaterialAmbientLight * gMaterialAmbientLight.a).xyz;
	final_color = (ambient * diffuse);

	////Single Light Test Code
	//Light light = lights[0];
	//vec3  Lvector = light.gLightPosition - passPosition;
	//float dist = length(Lvector);
	//
	//// light.gLightDirection = vec3(0.0f, 0.0f, -1.0f);
	//Lvector = light.gLightWeight * (Lvector / dist) - (1-light.gLightWeight) * light.gLightDirection;
	//
	//float Sa = dot( -Lvector, light.gLightDirection);
	//float Sc = step(light.gLightAngle, Sa);
	//float Sf = Sc * max( pow(Sa, light.gLightSpotPower), light.gLightMinSf);
	//float power = light.gLightColor.w;
	//vec3  Lcolor = light.gLightColor.xyz;
	//float Li = clamp(power/ dist * Sf, light.gLightMinIntensity, light.gLightMaxIntensity);
	//outColor = vec4(vec3(Li), 1.0f);
	//return;

	vec3 diffuse_power = vec3(0.0f);
	vec3 spec_power = vec3(0.0f);
	for( int i = 0; i < numberOfLights; i++)
	{
		vec3 surfaceToLight  = lights[i].gLightPosition  - passPosition;

		LightOutput outLight = ComputeALight( lights[i], normal );

		diffuse_power += outLight.LightIntensity * dot(normal, outLight.LightVector);

		vec3 h = outLight.LightVector + eyeVector;
		h = normalize(h);

		//vec3 color_from_spec = ComputeSpecularEnhanced(surfaceToLight, surfaceToCamera, lights[i], normal);
		//final_color += (color_from_spec * specular);

		//spec_power += outLight.LightIntensity * pow( dot(h, normal), gShininess );
		spec_power += ComputeSpecularEnhanced(surfaceToLight, surfaceToCamera, lights[i], normal);
	}

	// cool thing Cesar told me to leave in
	//outColor = vec4( spec_power, 1.0f );
	//return;

	// Banding
	//diffuse_power = BandVec3( diffuse_power, 5.0f );
	//spec_power    = BandVec3( spec_power, 5.0f );


	//Clamp and add  
	diffuse_power = clamp( diffuse_power, vec3(0.0f), vec3(1.0f) );
	//spec_power    = clamp( diffuse_power, vec3(0.0f), vec3(1.0f) );
	final_color += (diffuse_power * diffuse) + (spec_power * specular);
	 
	//Toon Shading
	//vec3 toon_shading = ComputeToonShading(normal);
	//final_color = toon_shading;
	
	//Fog
	float fogFactor = (gFogEnd - passDistToCamera)/(gFogEnd - gFogStart);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	final_color = mix(gFogColor, final_color, fogFactor); 

	//Outputting color
	final_color = clamp(final_color, 0.0f, 1.0f);

	//final_color = BandVec3( final_color, 2.0f );

	outColor = vec4( final_color, 1.0f );
	//outColor = vec4((passNormal+vec3(1.0)) * .5, 1);
	//outColor = vec4((passTangent+vec3(1.0)) * .5, 1);
	//outColor = vec4((passBiTangnet+vec3(1.0)) * .5, 1);
}
