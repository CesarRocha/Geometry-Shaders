#version 330 core

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 24) out;    
   
uniform mat4	gView;
uniform mat4	gProj;
uniform mat4	gModel;  

////////////////////////////////////////////////////////////////
//

//childVertex
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
	float particleSize = 1.0;
	vec3 childVertex; 

	//passPosition = gl_in[0].gl_Position.xyz;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	childVertex = point.xyz + vec3(-0.5, -0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 0.0);
	EmitVertex();  
	
	childVertex = point.xyz + vec3(-0.5, 0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 1.0);
	EmitVertex();  

	childVertex = point.xyz + vec3(0.5, -0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 0.0);
	EmitVertex();  
	
	childVertex = point.xyz + vec3(0.5, 0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 1.0);
	EmitVertex();  
	EndPrimitive();  
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	childVertex = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 0.0);
	EmitVertex();  
	
	childVertex = point.xyz + vec3(-0.5, 0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 1.0);
	EmitVertex();  

	childVertex = point.xyz + vec3(0.5, -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 0.0);
	EmitVertex();  
	
	childVertex = point.xyz + vec3(0.5, 0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 1.0);
	EmitVertex();    
	EndPrimitive();  
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///

	childVertex = point.xyz + vec3(-0.5, 0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 1.0);
	EmitVertex();  
	  
	childVertex = point.xyz + vec3(-0.5,  0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 0.0);
	EmitVertex();  

	childVertex = point.xyz + vec3( -0.5, -0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 1.0);
	EmitVertex();  

	childVertex = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 0.0);	
	EmitVertex();  
	
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	childVertex = point.xyz + vec3(0.5, -0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 1.0);	
	EmitVertex();  
	  
	childVertex = point.xyz + vec3(0.5,  -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 0.0);	
	EmitVertex();  

	childVertex = point.xyz + vec3(0.5, 0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 1.0);	
	EmitVertex();  
	
	childVertex = point.xyz + vec3(0.5, 0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 0.0);	
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	childVertex = point.xyz + vec3(0.5, 0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 1.0);	
	EmitVertex();  
	  
	childVertex = point.xyz + vec3(0.5,  0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 0.0);	
	EmitVertex();  

	childVertex = point.xyz + vec3(-0.5, 0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 1.0);	
	EmitVertex();  
	
	childVertex = point.xyz + vec3(-0.5, 0.5,  -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 0.0);	
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	childVertex = point.xyz + vec3(-0.5, -0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 1.0);	
	EmitVertex();  
	  
	childVertex = point.xyz + vec3(-0.5,  -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(0.0, 0.0);	
	EmitVertex();  

	childVertex = point.xyz + vec3(0.5, -0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 1.0);	
	EmitVertex();  
	
	childVertex = point.xyz + vec3(0.5, -0.5,  -0.5) * particleSize;
	gl_Position = gProj * gView * gModel * vec4(childVertex, point.w);
	passPosition = childVertex;
	passUV0 = vec2(1.0, 0.0);	
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	EndPrimitive();    
}   