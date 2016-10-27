#include "Engine/Renderer/Shader/Material.hpp"
#include "Engine\Utility\Utility.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

//===================================================================================================
//               class Material	                                                                   ==
//===================================================================================================
Material::Material()
{
}
Material::Material(Shader& shader, Sampler& sampler)
	:m_shader(shader)
	,m_sampler(sampler)
	,m_light()
	,m_lightArray()
	,m_lightCount(0)
	,m_materialAmbientLight(Vector4(1.0f, 1.0f, 1.0f, 1.0f))
	,m_shine(256.f)
{
}


//===================================================================================================
void Material::SetTexture(const char* name, Texture* texture, GLuint tex_index )
{
	ProgramBindSamplerIndex( m_sampler.m_samplerID, name, tex_index);
	GLCheckError( __FILE__,  __LINE__ -1);
	glActiveTexture( GL_TEXTURE0 + tex_index );

	glBindTexture( GL_TEXTURE_2D, texture->GetPlatformHandle());
	GLCheckError( __FILE__,  __LINE__ -1);

	glBindSampler( tex_index, m_sampler.m_samplerID);
	GLCheckError( __FILE__,  __LINE__ -1);
}
void Material::SetMatrix(const char* name, const Matrix4x4 matrix)
{
	ProgramBindMatrix( m_shader.m_programID, name, matrix);

}


//===================================================================================================
bool	Material::ProgramBindMatrix( GLuint program_ID, const char* name, const Matrix4x4& matrix)
{
	GLint loc = glGetUniformLocation( program_ID, name );
	if( loc < 0 ) 
		return false;

	GLuint index;
	glGetUniformIndices( program_ID, 1, &name, &index );
	if( index >= 0 )
	{
		GLint count;
		GLenum type;
		glGetActiveUniform( program_ID, index, 0, NULL, &count, &type, NULL);
		assert( type == GL_FLOAT_MAT4 );
	}

	glUniformMatrix4fv( loc, 1, GL_FALSE, (GLfloat*)&matrix);////
	return true;
}
bool	Material::ProgramBindSamplerIndex( GLuint program_ID, const char* name, GLint index)
{
	GLint loc = ProgramFindAndCheck( program_ID, name, GL_SAMPLER_2D );
	if(loc < 0 )
		return false;

	glUniform1iv( loc, 1, (GLint*)&index);

	return true;
}
void	Material::GLCheckError(const std::string& file, int line)
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
GLuint	Material::ProgramFindAndCheck( GLuint program_ID, const char* name, GLenum type)
{
	GLint loc = glGetUniformLocation( program_ID, name);
	if(loc < 0)
		return loc;

	GLuint index; 
	glGetUniformIndices( program_ID, 1, &name, &index );
	if(index >= 0)
	{
		GLint count;
		GLenum check_type;
		glGetActiveUniform( program_ID, index, 0, NULL, &count, &check_type, NULL);
		assert(type == check_type);
		if(type == check_type)
			return loc;
	}
	GLint i = -1;
	return  i;
}




