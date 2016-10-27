#version 330 core

uniform mat4 gView;
uniform mat4 gProj;
uniform mat4 gModel;  
////////////////////////////////////////////////////////////////
in vec3 inPosition;
in vec2 inUV0;
in vec3 inNormal;
in vec3 inTangent;
in vec3 inBiTangent;
////////////////////////////////////////////////////////////////
out vec3 passPosition;
out vec2 passUV0;
out vec3 passNormal;
out vec3 passTangent;
out vec3 passBiTangent;
out float passDistToCamera;
void main()
{

    passPosition   = inPosition;
    passUV0		   = inUV0;
    passNormal     = (gModel * vec4(inNormal, 0.0)).xyz;
    passTangent    = (gModel * vec4(inTangent, 0.0)).xyz;
	passBiTangent  = (gModel * vec4(inBiTangent, 0.0)).xyz;

	gl_Position   = gProj * gView * gModel * vec4(inPosition, 1.0 );
	passDistToCamera = gl_Position.w;
}


