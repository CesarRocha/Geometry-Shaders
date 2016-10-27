#pragma once
#ifndef _INCLUDED_SHADER_
#define _INCLUDED_SHADER_
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include <string>


//===================================================================================================
//               class Shader	                                                                   ==
//===================================================================================================
class Shader
{
public:
	Shader();
	Shader(const std::string& shaderFileName);
	Shader(const std::string& vertFileName, const std::string& fragFileName);
	Shader(const std::string& vertFileName, const std::string& geoFileName, const std::string& fragFileName);
	GLuint		CreateShader( const std::string& fileName, GLenum shader_type );

	void		GLCheckError(const std::string& file, int line);
	bool		CheckShaderStatus( GLuint shader_id, const std::string& filename);
	bool		CheckProgramStatus( GLuint program_ID, const std::string& fileName );


	char*		ReadFile(const std::string& fileName);
	void		FormatAndPrintLog(const std::string& fileName, const char* log);
	GLuint		ProgramFindAndCheck( GLuint program_ID, const char* name, GLenum type);

	GLuint		m_programID;
	std::string m_fileName;
private:
};

//###################################################################################################
//##                                                                                               ##
//###################################################################################################
enum SpecialShader
{
	MODEL_EXPLODE,
	NONE
};
#endif