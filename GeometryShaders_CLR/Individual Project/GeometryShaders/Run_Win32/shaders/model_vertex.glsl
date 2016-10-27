#version 330 core

uniform mat4 gView;
uniform mat4 gProj;
uniform mat4 gModel;  

////////////////////////////////////////////////////////////////
// Inputs: per-vertex attributes, from the VBO data
//
in vec3 inPosition; // model space
in vec2 inUV0;
in vec3 inNormal; // model space
in vec3 inTangent; // model space
in vec3 inBiTangent; // model space
in vec4 inColor;

////////////////////////////////////////////////////////////////
out vec3 passPosition;
out vec2 passUV0;
out vec3 passNormal;
out vec3 passTangent;
out vec3 passBiTangent;
out float passDistToCamera;
out vec4 passColor;

out Vertex
{
	vec3  VPosition;
	vec2  VUV0;
	vec3  VNormal;
	vec3  VTangent;
	vec3  VBiTangent;
	float VDistToCamera;
	vec4  VColor;
}vertex;

void main()
{
	//Per Vertex (No Geometry Shader)
    passPosition	= inPosition;
    passUV0			= inUV0;
    passNormal		= (gModel * vec4(inNormal, 0.0)).xyz;
    passTangent		= (gModel * vec4(inTangent, 0.0)).xyz;
	passBiTangent	= (gModel * vec4(inBiTangent, 0.0)).xyz;
	passColor		= inColor;


	//For Geometry Shader
	vertex.VPosition	= inPosition;
    vertex.VUV0			= inUV0;
    vertex.VNormal		= (gModel * vec4(inNormal, 0.0)).xyz;
    vertex.VTangent		= (gModel * vec4(inTangent, 0.0)).xyz;
	vertex.VBiTangent	= (gModel * vec4(inBiTangent, 0.0)).xyz;
	vertex.VColor		= inColor;
	
	gl_Position		= gProj * gView * gModel * vec4(inPosition, 1.0 );
	passDistToCamera = gl_Position.w;
}


