#version 330 core

//Textures
uniform sampler2D	gTexDiffuse; 
uniform sampler2D	gTexNormal;
uniform sampler2D	gTexSpecular;
uniform sampler2D	gTexEmissive;
uniform sampler2D	gTexEmissive2;	
uniform sampler2D	gTexDepth;	
uniform sampler2D	gTexSGE;	

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
float glightIntensity;
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
in vec4 passColor;

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

		//Use 1.0 for full intensity unaffected by distance;
		float power = 1.0;
		power = light.gLightColor.w;


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

		//CHANGE
		float power = light.glightIntensity;

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

vec4 EncodeDirectionAsRgba( vec3 direction ) 
{
	vec3 color = (direction + vec3(1.0)) * .5;
	return vec4( color, 1.0);
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
//Setup eyeVector
	vec3 surfaceToCamera = gCameraPosition - passPosition;
	vec3 eyeVector = normalize(surfaceToCamera);

//Initialize final color to return
	vec3 final_color = vec3(0.0f);

//Setup textures
	//vec2 flipped_texcoord = vec2(passUV0.x, 1.0 - passUV0.y); //flips the texture. Was upside down.	
	vec3 normalTexel	= texture( gTexNormal,   passUV0 ).rgb;
	vec4 diffuseTexel	= texture( gTexDiffuse,  passUV0 );
	//vec3 specular	= texture( gTexSpecular, passUV0 ).xyz;
	vec3 sge			= texture( gTexSGE,		 passUV0 ).rgb;

//Setup Specular/Gloss/Emissive values based on SGEMap
	float specular = sge.r;
	float gloss	   = sge.g;
	float emissive = sge.b;

//Setup normals
	vec3 normalInTangentSpace = normalTexel * vec3(2.0f, 2.0f, 2.0f) - vec3(1.0f, 1.0f, 1.0f);
	vec3 normalizedTangent = normalize( passTangent );
	vec3 normalizedBitangent = normalize( passBiTangent );
	mat3 TBN = mat3(normalizedTangent, normalizedBitangent, passNormal);
	vec3 normalInWorldSpace = TBN * normalInTangentSpace;
	normalInWorldSpace = normalize(normalInWorldSpace);

//Apply Ambient Light to Diffuse
	vec3 ambient = (gMaterialAmbientLight * gMaterialAmbientLight.a).rgb;
	final_color = (ambient * diffuseTexel.rgb * passColor.rgb);

	float final_alpha = (diffuseTexel.a * passColor.a);

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

//Initialize specilar and diffusive powers
	vec3 total_diffuse = vec3(0.0f);
	vec3 total_specular = vec3(0.0f);

//Begin computing lights
	for( int i = 0; i < numberOfLights; i++)
	{
		vec3 surfaceToLight  = lights[i].gLightPosition  - passPosition;

		LightOutput outLight = ComputeALight( lights[i], normalInWorldSpace );

		total_diffuse += outLight.LightIntensity * clamp( dot(normalInWorldSpace, outLight.LightVector), 0.0, 1.0);

		vec3 h = outLight.LightVector + eyeVector;
		h = normalize(h);

		//vec3 color_from_spec = ComputeSpecularEnhanced(surfaceToLight, surfaceToCamera, lights[i], normalInWorldSpace);
		//final_color += (color_from_spec * specular);

		//total_specular += outLight.LightIntensity * pow( dot(h, normalInWorldSpace), gShininess );
		total_specular += ComputeSpecularEnhanced(surfaceToLight, surfaceToCamera, lights[i], normalInWorldSpace);
	}

	//outColor = vec4(passColor.rgba);
	//return;


//cool thing to leave in
	//outColor = vec4( total_specular, 1.0f );
	//return;


//Banding
	//total_diffuse = BandVec3( total_diffuse, 5.0f );
	//total_specular    = BandVec3( total_specular, 5.0f );


//Clamp and add  
	total_diffuse = clamp( total_diffuse, vec3(0.0f), vec3(1.0f) );
	//total_specular    = clamp( total_diffuse, vec3(0.0f), vec3(1.0f) );
	final_color += (total_diffuse * diffuseTexel.rgb * passColor.rgb) + (total_specular * specular);


//Toon Shading
	//vec3 toon_shading = ComputeToonShading(normalInWorldSpace);
	//final_color = toon_shading;


//Fog
	//float fogFactor = (gFogEnd - passDistToCamera)/(gFogEnd - gFogStart);
	//fogFactor = clamp( fogFactor, 0.0, 1.0 );
	//final_color = mix(gFogColor, final_color, fogFactor); 


//Outputting color
	final_color = clamp(final_color, 0.0f, 1.0f);




//Return final
	outColor = vec4( final_color, final_alpha );


//Debugging
	//outColor = BandVec3( final_color, 2.0f );
	//outColor = vec4((passNormal+vec3(1.0)) * .5, 1);
	//outColor = vec4((passTangent+vec3(1.0)) * .5, 1);
	//outColor = vec4((passBiTangnet+vec3(1.0)) * .5, 1);
//Debugging

	//outColor = diffuseTexel;
	//outColor = EncodeDirectionAsRgba( normalInWorldSpace );
}


	//vec3 normalInTangentSpace = normalTexel * vec3(2.0f, 2.0f, 2.0f) - vec3(1.0f, 1.0f, 1.0f);
	//vec3 normalizedTangent = normalize( passTangent );
	//vec3 normalizedBitangent = normalize( passBiTangent );
	//mat3 TBN = mat3(normalizedTangent, normalizedBitangent, passNormal);
	//vec3 normalInWorldSpace = TBN * normalInTangentSpace;
	//normalInWorldSpace = normalize(normalInWorldSpace);