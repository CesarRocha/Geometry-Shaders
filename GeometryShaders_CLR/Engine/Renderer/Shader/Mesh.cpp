//================================================================
//                     Mesh.cpp
//================================================================
#pragma warning (disable: 4458) //declaration of 'm_boneTransforms' hides class member

#include "Engine/Renderer/Shader/Mesh.hpp"
Mesh::Mesh()
{

}
Mesh::Mesh(const void* vboBuffer, size_t vboSize, const void* iboBuffer, size_t iboSize)
	:m_iboID(0)
	,m_vboID(0)
	,m_boneCount(0)
{
	GLCheckError(__FILE__,  __LINE__ -1);
	m_vboVertCount = vboSize;
	m_iboIndexCount = iboSize;
	m_vboID = 	CreateBuffer(vboBuffer, vboSize, VBO);
	GLCheckError(__FILE__,  __LINE__ -1);

	if(iboBuffer != nullptr)
		m_iboID = CreateBuffer(iboBuffer, iboSize, IBO);
	GLCheckError(__FILE__,  __LINE__ -1);
}
Mesh::Mesh(const void* vboBuffer, size_t vboSize, const void* iboBuffer, size_t iboSize, size_t boneCount, Matrix4x4 boneTransforms[] )
	:m_iboID(0)
	,m_vboID(0)
	,m_boneCount(0)
{
	GLCheckError(__FILE__,  __LINE__ -1);
	m_vboVertCount = vboSize;
	m_iboIndexCount = iboSize;
	//===================================================================================================
	m_boneCount = boneCount;
	Matrix4x4* m_boneTransforms = new Matrix4x4[boneCount];
	m_boneTransforms = boneTransforms;
	//===================================================================================================
	m_vboID = 	CreateBuffer(vboBuffer, vboSize, VBO);
	GLCheckError(__FILE__,  __LINE__ -1);

	if(iboBuffer != nullptr)
		m_iboID = CreateBuffer(iboBuffer, iboSize, IBO);
	GLCheckError(__FILE__,  __LINE__ -1);
}



GLuint	Mesh::CreateBuffer(const void* buffer, size_t size, const BufferType&  bufferType)
{
	GLCheckError(__FILE__,  __LINE__ -1);
	GLuint buffer_ID;
	glGenBuffers( 1, &buffer_ID );
	GLCheckError(__FILE__,  __LINE__ -1);
	if(buffer_ID == NULL)
		return NULL;

	if( buffer != nullptr )	{
		if(bufferType == VBO)
			CopyToBufferVBO( buffer_ID, buffer, size);
		if(bufferType == IBO)
			CopyToBufferIBO( buffer_ID, buffer, size);
	}


	return buffer_ID;
}
void	Mesh::DestroyBuffer( GLuint buffer )
{
	glDeleteBuffers( 1, &buffer );
}
void	Mesh::CopyToBufferVBO( GLuint buffer_ID, const void* data, size_t numVerts)
{
	size_t numBytes = sizeof(vert_t) * numVerts;
	glBindBuffer( GL_ARRAY_BUFFER, buffer_ID );
	GLCheckError(__FILE__,  __LINE__ -1);

	glBufferData( GL_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW );
	GLCheckError(__FILE__,  __LINE__ -1);
}
void	Mesh::CopyToBufferIBO( GLuint buffer_ID, const void* data, size_t numIndexes)
{
	size_t numBytes = sizeof(unsigned int) * numIndexes;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffer_ID );
	GLCheckError(__FILE__,  __LINE__ -1);

	glBufferData( GL_ELEMENT_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW );
	GLCheckError(__FILE__,  __LINE__ -1);
}


bool	Mesh::ProgramBindAttribute(GLuint program_ID, const char* inName, GLint count, GLenum shader_type, GLboolean normalize, GLsizei stride, GLsizei offset)
{
	GLint loc = glGetAttribLocation( program_ID, inName );
	GLCheckError(__FILE__,  __LINE__ -1);

	if( loc < 0 )
		return false;

	glEnableVertexAttribArray( loc );
	GLCheckError(__FILE__,  __LINE__ -1);

	glVertexAttribPointer( loc, count, shader_type, normalize, stride, (GLvoid*) offset );
	GLCheckError(__FILE__,  __LINE__ -1);

	return true;
}
void	Mesh::GLCheckError(const std::string& file, int line)
{
#if defined(OPENGL_CHECK_ERRORS)
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{

		std::stringstream out;
		out << line;
		std::string header = "Error: " + ConsolePrintf("0x%04x\n" , error) + " at " + out.str();
		std::string message1 = file;
		std::string message3 = message1;
		MessageBoxA ( NULL, message3.c_str(), header.c_str(), MB_OK );
	}
#endif
}


