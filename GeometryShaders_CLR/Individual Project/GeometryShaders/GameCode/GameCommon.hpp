//================================================================
//                     GameCommon.hpp
//================================================================
#pragma once
#ifndef __INCLUDE_GAMECOMMON__
#define __INCLUDE_GAMECOMMON__
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Console/Console.hpp"
#pragma warning( disable: 4127 ) // conditional expression is constant
#pragma warning( disable: 4244 ) //conversion from 'time_t' to 'unsigned int', possible loss of data
#pragma warning( disable: 4996 ) //'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead.
#define UNUSED(x) (void)(x)

static Rgba g_clearBufferColor = Rgba::BLACK;
extern int g_numOfParticles;
enum GeoType
{
	BILLBOARD,
	CUBE,
	ORBIT
};


extern GeoType g_geoType; 

static inline std::string GetGeoTypeName()
{
	if(g_geoType == BILLBOARD)
		return "Billboard";
	if(g_geoType == CUBE)
		return "Cube";
	if(g_geoType == ORBIT)
		return "Orbit";
	return "NULL";
};



extern bool g_debugTile;
extern bool g_renderModel;


#endif