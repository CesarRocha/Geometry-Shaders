//================================================================
//                     AnimatedTexture.hpp
//================================================================

#pragma once
#ifndef  __included_AnimatedTexture__
#define  __included_AnimatedTexture__
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Math/Vector2.hpp"
#include <string>
#include <map>

class AnimatedTexture ;
typedef std::map< std::string, AnimatedTexture* >	AnimatedTextureMap ;

class AnimatedTexture : public Texture
{
public:
	//constructors
	virtual ~AnimatedTexture() {}
	AnimatedTexture(const std::string& animatedTexturePath, int numberOfFrames, int cellsWide, int cellsHigh);

	//Functions
	static AnimatedTexture* CreateOrGetAnimatedTexture(const std::string& animatedTexturePath, int numOfSprites, int cellWidth, int cellHeight);
	void CalcTextureCoordinatesAtPercentComplete(double percentComplete, Vector2& minCoodinates_out, Vector2& maxCoordinates_out);
	double CalcPercentCompleteTimeAndDuration(double animationAge, double durationSeconds);


private:
	static AnimatedTextureMap	s_AnimatedTextureMap;
	int m_numOfFrames;
	int m_cellsHigh;
	int m_cellsWide;
	
protected:
		AnimatedTexture( const std::string& animatedTexturePath );
};

#endif