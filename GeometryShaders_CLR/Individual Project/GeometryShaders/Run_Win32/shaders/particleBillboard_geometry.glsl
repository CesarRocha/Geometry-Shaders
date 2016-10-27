#version 330 core

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;    
   
uniform mat4	gView;
uniform mat4	gProj;
uniform mat4	gModel;  

////////////////////////////////////////////////////////////////
//
in Vertex
{
	vec4 color;
}   vertex[];
//
////////////////////////////////////////////////////////////////
//
out vec3		passPosition;
out vec2		passUV0;
out vec4		passColor;
//
////////////////////////////////////////////////////////////////
void main()
{
	vec4 point = gl_in[0].gl_Position;
	float particleSize = .1;

	
	 
	//vertex[0].color = vec4(0.0, 1.0, 0.0, 1.0);

	vec2 vertexFront = point.xy + vec2(-0.5, -0.5) * particleSize;
	gl_Position = gProj * vec4(vertexFront, point.zw);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexFront = point.xy + vec2(-0.5, 0.5) * particleSize;
	gl_Position = gProj * vec4(vertexFront, point.zw);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	

	vertexFront = point.xy + vec2(0.5, -0.5) * particleSize;
	gl_Position = gProj * vec4(vertexFront, point.zw);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexFront = point.xy + vec2(0.5, 0.5) * particleSize;
	gl_Position = gProj * vec4(vertexFront, point.zw);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  

	EndPrimitive();    
}   