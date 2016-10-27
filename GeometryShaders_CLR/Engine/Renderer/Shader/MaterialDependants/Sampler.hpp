#pragma once
#ifndef _INCLUDE_SAMPLER_
#define _INCLUDE_SAMPLER_
#include "Engine/Renderer/OpenGLRenderer.hpp"


//===================================================================================================
//               class Sampler	                                                                   ==
//===================================================================================================
class Sampler
{
public:
	Sampler();

	GLuint		CreateSampler(GLenum min_filter, GLenum mag_filter, GLenum u_wrap, GLenum v_wrap);
	void		DestroySampler(GLuint sampler_id);

	void		SetDiffuse(Texture* diffuse) { m_diffuseMap = diffuse; }
	void		SetNormal(Texture* normal) { m_normalMap = normal; }
	void		SetSpecular(Texture* specular) { m_specMap = specular; }
	void		SetEmissive(Texture* emissive) { m_emissiveMap = emissive; }
	void		SetDepth(Texture* depth) { m_depthMap = depth; }
	void		SetSpecularGlossEmisiveMap(Texture* SpecularGlossEmisive) { m_specularGlossEmisiveMap = SpecularGlossEmisive; }

	Texture*	GetDiffuse() { return m_diffuseMap; }
	Texture*	GetNormal() { return m_normalMap; }
	Texture*	GetSpecular() { return m_specMap; }
	Texture*	GetEmissive() { return m_emissiveMap; }
	Texture*	GetDepth() { return m_depthMap; }
	Texture*	GetSpecularGlossEmisiveMap() { return m_specularGlossEmisiveMap; }

	Texture*	m_diffuseMap;
	GLuint		m_samplerID;
	Texture*	m_normalMap;
	Texture*	m_specMap;
	Texture*    m_emissiveMap;
private:
	Texture*	m_depthMap;
	Texture*	m_specularGlossEmisiveMap;
};


#endif // !_INCLUDE_SAMPLER_