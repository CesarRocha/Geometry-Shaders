#pragma once
#ifndef _INCLUDE_MESHRENDERER_
#define _INCLUDE_MESHRENDERER_
#include "Engine/Renderer/Shader/Material.hpp"
#include "Engine/Renderer/Shader/Mesh.hpp"


//===================================================================================================
//               class MeshRenderer                                                                ==
//===================================================================================================
class MeshRenderer
{
public:
	MeshRenderer();
	MeshRenderer(Mesh mesh, Material material, BufferType bufferType = VBO);

	GLuint		CreateVAO(GLuint buffer_ID);
	void		DestroyVAO(GLuint vao_ID);

	GLuint		CreateIBO(GLuint buffer_ID);
	void		DestroyIBO(GLuint ibo_ID);

	bool		ProgramBindAttribute( GLuint program_ID, const char* inName, GLint count, GLenum shader_type, GLboolean normalize, GLsizei stride, GLsizei offset );
	void		ProgramBind( GLuint program_ID );
	bool		ProgramBindFloat( GLuint program_ID, const char* name, const float& val);
	bool		ProgramBindVec3( GLuint program_ID, const char* name, const Vector3& val);
	bool		ProgramBindVec4( GLuint program_ID, const char* name, const Vector4& val);
	bool		ProgramBindMatrix( GLuint program_ID, const char* name, const Matrix4x4& matrix);
	bool		ProgramBindSamplerIndex( GLuint program_ID, const char* name, GLint index);
	void		GLCheckError(const std::string& file, int line);
	GLuint		ProgramFindAndCheck( GLuint program_ID, const char* name, GLenum type);


	void		Render(const Matrix4x4& view, const Matrix4x4& projection, const Matrix4x4& model, const Vector3& cameraPosition = Vector3(), const double& deltaSeconds = 0);
	void		BindLights();
	void		BindDiffuse();
	void		BindNormal();
	void		BindSpecular();

	Mesh		m_mesh;
	Material	m_material;
	float		m_fogStartDistance;
	float		m_fogEndDistance;
	Vector3		m_fogColorAndIntensity;
	BufferType  m_bufferType;
	float		m_startTime;
private:
	GLuint		m_VBO;
	GLuint		m_IBO;
};



#endif
