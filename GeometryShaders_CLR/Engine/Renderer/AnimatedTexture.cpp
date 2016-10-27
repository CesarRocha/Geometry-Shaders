//================================================================
//                     AnimatedTexture.cpp
//================================================================
#include "AnimatedTexture.hpp"
#define UNUSED(x) (void)(x) 

std::map< std::string, AnimatedTexture* >	AnimatedTexture::s_AnimatedTextureMap ; //Collection of all known animations loaded so far.  

AnimatedTexture::AnimatedTexture( const std::string& animatedTexturePath, int numberOfFrames, int cellsWide, int cellsHigh )
	: Texture(animatedTexturePath)
	, m_numOfFrames(numberOfFrames)
	, m_cellsHigh (cellsHigh)
	, m_cellsWide (cellsWide)
{
}

AnimatedTexture* AnimatedTexture::CreateOrGetAnimatedTexture(const std::string& animatedTexturePath, int numberOfFrames, int cellsWide, int cellsHigh) 
{
	AnimatedTextureMap::iterator textureIter = s_AnimatedTextureMap.find( animatedTexturePath );
	if ( textureIter != s_AnimatedTextureMap.end() )
		return textureIter->second ;

	AnimatedTexture*	newTexture			= new AnimatedTexture( animatedTexturePath, numberOfFrames, cellsWide, cellsHigh );
	s_AnimatedTextureMap[ animatedTexturePath ]	= newTexture ;
	return newTexture ;
}

void AnimatedTexture::CalcTextureCoordinatesAtPercentComplete(double percentComplete, Vector2& minCoodinates_out, Vector2& maxCoordinates_out)
{
	float percentPerFrame = 1.0f / m_numOfFrames;
	int currentFrame = (int) floor(percentComplete/percentPerFrame);
	UNUSED(currentFrame);
	int rowIndex = m_numOfFrames / m_cellsWide; //Frames per row
	int colIndex = m_numOfFrames % m_cellsWide; //Frames per col 
	float minX = (float)colIndex / (float)m_cellsHigh; //Base MinX coord 
	float minY = (float)rowIndex / (float)m_cellsWide; //base MinY coord
	float maxX = (float)(colIndex+1) / (float)m_cellsHigh;
	float maxY = (float)(rowIndex+1) / (float)m_cellsWide;

	minCoodinates_out = Vector2 (minX , minY);
	maxCoordinates_out = Vector2 (maxX, maxY);	
}

double AnimatedTexture::CalcPercentCompleteTimeAndDuration(double animationAge, double durationSeconds)
{
	return animationAge / durationSeconds;
}



