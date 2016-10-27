#pragma once
#ifndef _INCLUDE_MESH_
#define	_INCLUDE_MESH_
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Console/Console.hpp"


enum BufferType
{
	VBO,
	IBO,
	GEOPOINT,
	GEOTRIANGLE
};
//===================================================================================================
//               class Mesh		                                                                   ==
//===================================================================================================
class Mesh
{
public:
	Mesh();
	Mesh(const void* vboBuffer, size_t vboSize, const void* iboBuffer = 0, size_t iboSize = 0);
	Mesh(const void* vboBuffer, size_t vboSize, const void* iboBuffer, size_t iboSize, size_t boneCount, Matrix4x4 boneTransforms[] );

	GLuint	CreateBuffer(const void* buffer, size_t size, const BufferType&  bufferType);
	void	DestroyBuffer( GLuint buffer );
	void	CopyToBufferVBO( GLuint buffer_ID, const void* data, size_t numVerts);
	void	CopyToBufferIBO( GLuint buffer_ID, const void* data, size_t size);

	void	GLCheckError(const std::string& file, int line);
	bool	ProgramBindAttribute(GLuint program_ID, const char* inName, GLint count, GLenum shader_type, GLboolean normalize, GLsizei stride, GLsizei offset);

	GLuint		m_vboID;
	size_t		m_vboVertCount;

	GLuint		m_iboID;
	size_t		m_iboIndexCount;

	size_t		m_boneCount;
	Matrix4x4	m_boneTransforms;

private:
};

#endif

