#version 330 core

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;    
   
uniform mat4	gView;
uniform mat4	gProj;
uniform mat4	gModel;
uniform float	gTime;  

////////////////////////////////////////////////////////////////
//
in Vertex
{
	vec3  VPosition;
	vec2  VUV0;
	vec3  VNormal;
	vec3  VTangent;
	vec3  VBiTangent;
	float VDistToCamera;
	vec4  VColor;
}vertex[];
//
////////////////////////////////////////////////////////////////
//
out vec3		passPosition;
out vec2		passUV0;
out vec4		passColor;
out vec3		passNormal;
out vec3		passTangent;
out vec3		passBiTangent;
//
////////////////////////////////////////////////////////////////
void main()
{
	vec3 P0 = vertex[0].VPosition.xyz;
	vec3 P1 = vertex[1].VPosition.xyz;
	vec3 P2 = vertex[2].VPosition.xyz;
  
	vec3 V0 = P0 - P1;
	vec3 V1 = P2 - P1;

	vec3 diff = V1 - V0;
	float diff_len = length(diff);
  
	vec3 N = normalize(cross(V1, V0));

	for(int i = 0; i < 3; i++) 
	{ 
		vec4 pulledVertex = vec4(vertex[i].VPosition, 1.0);

		vec3 normalVector = normalize(cross(V1, V0));
		pulledVertex =  vec4(pulledVertex.xyz + (normalVector * .01 * gTime) + \
		      (normalVector * vec3(0.00, 0.00, 0.00)), 1.0);

		
		gl_Position = gProj * gView * gModel * pulledVertex;
		passUV0			= vertex[i].VUV0;
		passNormal		= vertex[i].VNormal;
		passTangent		= vertex[i].VTangent;
		passBiTangent	= vertex[i].VBiTangent;
		passColor		= vertex[i].VColor;
		EmitVertex();
	}
  EndPrimitive();
}   