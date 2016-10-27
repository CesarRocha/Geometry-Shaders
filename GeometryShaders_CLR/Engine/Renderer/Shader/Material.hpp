#pragma once
#ifndef _INCLUDED_MATERIAL_
#define _INCLUDED_MATERIAL_
#include "Engine/Renderer/Lighting/LightingProperties.hpp"
#include "MaterialDependants/Shader.hpp"
#include "MaterialDependants/Sampler.hpp"



//===================================================================================================
//               class Material	                                                                   ==
//===================================================================================================
class Material
{
public:
	Material();
	Material(Shader& shaderID, Sampler& samplerID);


	void	SetTexture(const char* name, Texture* texture, GLuint tex_index );
	void	SetMatrix(const char* name, const Matrix4x4 matrix);
	bool	ProgramBindMatrix( GLuint program_ID, const char* name, const Matrix4x4& matrix);
	bool	ProgramBindSamplerIndex( GLuint program_ID, const char* name, GLint index);
	void	GLCheckError(const std::string& file, int line);
	GLuint	ProgramFindAndCheck( GLuint program_ID, const char* name, GLenum type);
	
	void	SetAmbientLight(const Vector4& ambient) {m_materialAmbientLight = ambient;} 
	void	SetAmbientLightPower(const float& power) {m_materialAmbientLight.w = power;} 
	Vector4 GetAmbientLight() {return m_materialAmbientLight;}


	Shader				m_shader;
	Sampler				m_sampler;
	LightProperties		m_light;
	LightProperties		m_lightArray[16];
	int					m_lightCount;
	Vector4				m_materialAmbientLight;
	float				m_shine;
private:
};

#endif