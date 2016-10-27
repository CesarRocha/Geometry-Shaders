#pragma once
#ifndef _INCLUDE_LIGHT_PROPERTIES_
#define _INCLUDE_LIGHT_PROPERTIES_
#include "Engine\Math\3D\Vector3.hpp"
#include "Engine\Renderer\RGBA.hpp"


//===================================================================================================
//               class LightProperties                                                             ==
//===================================================================================================
class LightProperties
{
public:
	LightProperties()
		:m_lightAmbient(0.0f)
		, m_lightPosition(Vector3(0.0f, 0.0f, 0.0f))
		, m_lightDirection(Vector3(0.0f, 0.0f, 0.0f))
		, m_lightColor(Rgba::WHITE)
		, m_lightIntensity(10000.0f)
		, m_lightWeight( 1.0f)
		, m_lightAngle( -2.0f)
		, m_lightSpotPower( 1.0f)
		, m_lightPower( 5.0f)
		, m_lightMinSf( 1.0f)
		, m_lightMinIntensity( 0.0f)
		, m_lightMaxIntensity( 1.0f)
	{}

	float	m_lightAmbient;
	Vector3 m_lightPosition;
	Vector3 m_lightDirection;
	Rgba	m_lightColor;
	float	m_lightIntensity;
	float	m_lightWeight;
	float	m_lightAngle;
	float	m_lightSpotPower;
	float	m_lightPower;
	float	m_lightMinSf;
	float	m_lightMinIntensity;
	float	m_lightMaxIntensity;
private:
};
#endif // !_INCLUDE_LIGHT_PROPERTIES_