#version 330 core

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 128) out;    
   
uniform mat4	gView;
uniform mat4	gProj;
uniform mat4	gModel;  
uniform float	gTime;

////////////////////////////////////////////////////////////////
//
in Vertex
{
	vec3 position;
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
vec4 point = gl_in[0].gl_Position;
float particleSize = .1;

void CalcMoons(vec4 point, float speedAndDirection, float dist, float moonsize)
{
	vec3 vertexTop;
	vec3 vertexBottom; 
	vec3 vertexFront;
	vec3 vertexBack;
	vec3 vertexLeft;
	vec3 vertexRight;
	point.x += cos(gTime * speedAndDirection) * dist;
	point.y += sin(gTime * speedAndDirection) * dist;
	vertexTop = point.xyz + vec3(-0.5, -0.5, 0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexTop.x, vertexTop.y, vertexTop.z, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexTop = point.xyz + vec3(-0.5, 0.5, 0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexTop.x, vertexTop.y, vertexTop.z, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexTop = point.xyz + vec3(+ 0.5, -0.5, 0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexTop.x, vertexTop.y, vertexTop.z, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexTop = point.xyz + vec3(+ 0.5, 0.5, 0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexTop.x, vertexTop.y, vertexTop.z, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();  
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexBottom = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBottom.x, vertexBottom.y, vertexBottom.z, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexBottom = point.xyz + vec3(-0.5, 0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBottom.x, vertexBottom.y, vertexBottom.z, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexBottom = point.xyz + vec3(0.5, -0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBottom.x, vertexBottom.y, vertexBottom.z, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexBottom = point.xyz + vec3(0.5, 0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBottom.x, vertexBottom.y, vertexBottom.z, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();    
	EndPrimitive();  
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexFront = point.xyz + vec3(-0.5, 0.5,  0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexFront = point.xyz + vec3(-0.5,  0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexFront = point.xyz + vec3(-0.5, -0.5,  0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexFront = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexBack = point.xyz + vec3(0.5, -0.5,  0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexBack = point.xyz + vec3(0.5,  -0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexBack = point.xyz + vec3(0.5, 0.5,  0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexBack = point.xyz + vec3(0.5, 0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexLeft = point.xyz + vec3(0.5, 0.5,  0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexLeft = point.xyz + vec3(0.5,  0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexLeft = point.xyz + vec3(-0.5, 0.5, 0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexLeft = point.xyz + vec3(-0.5, 0.5,  -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexRight = point.xyz + vec3(-0.5, -0.5,  0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexRight = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexRight = point.xyz + vec3(0.5, -0.5, 0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexRight = point.xyz + vec3(0.5, -0.5,  -0.5) * particleSize*moonsize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();	

}
void main()
{
	vec3 vertexTop; 
	vec3 vertexBottom; 
	vec3 vertexFront;
	vec3 vertexBack;
	vec3 vertexLeft;
	vec3 vertexRight;
	passPosition = vertex[0].position;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	CalcMoons(point, .7, .2, .3);
	CalcMoons(point,  1, .5, .2);

	//rotation * point + ( - rotation * origin + origin )

	vertexTop = point.xyz + vec3(-0.5, -0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexTop, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexTop = point.xyz + vec3(-0.5, 0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexTop, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexTop = point.xyz + vec3(0.5, -0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexTop, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexTop = point.xyz + vec3(0.5, 0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexTop, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();  
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexBottom = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBottom, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexBottom = point.xyz + vec3(-0.5, 0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBottom, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexBottom = point.xyz + vec3(0.5, -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBottom, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexBottom = point.xyz + vec3(0.5, 0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBottom, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();    
	EndPrimitive();  
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexFront = point.xyz + vec3(-0.5, 0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexFront = point.xyz + vec3(-0.5,  0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexFront = point.xyz + vec3( -0.5, -0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexFront = point.xyz + vec3(-0.5, -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexFront, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexBack = point.xyz + vec3(0.5, -0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexBack = point.xyz + vec3(0.5,  -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexBack = point.xyz + vec3(0.5, 0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexBack = point.xyz + vec3(0.5, 0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexBack, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexLeft = point.xyz + vec3(0.5, 0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexLeft = point.xyz + vec3(0.5,  0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexLeft = point.xyz + vec3(-0.5, 0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexLeft = point.xyz + vec3(-0.5, 0.5,  -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexLeft, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	vertexRight = point.xyz + vec3(-0.5, -0.5,  0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(0.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	  
	vertexRight = point.xyz + vec3(-0.5,  -0.5, -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(0.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  

	vertexRight = point.xyz + vec3(0.5, -0.5, 0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(1.0, 1.0);
	passColor = vertex[0].color;
	EmitVertex();  
	
	vertexRight = point.xyz + vec3(0.5, -0.5,  -0.5) * particleSize;
	gl_Position = gProj * gView * vec4(vertexRight, point.w);
	passUV0 = vec2(1.0, 0.0);
	passColor = vertex[0].color;
	EmitVertex();  
	EndPrimitive();
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///
	EndPrimitive();    
}   