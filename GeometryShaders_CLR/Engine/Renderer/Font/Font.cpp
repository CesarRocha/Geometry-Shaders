//================================================================
//                     Font.cpp
//================================================================
#include "Engine/Renderer/Font/Font.hpp"
#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using std::string;

//===================================================================================================
//               class FaceData                                                                    ==
//===================================================================================================
FaceData::FaceData()
{
}

//===================================================================================================
//               class Font                                                                        ==
//===================================================================================================
Font::Font()
{
}


//----------------------------------------------------------------------------------------------
Font::Font(const std::string& fontFileName)
	:m_cursorPosition(Vector2(5.0f, 15.0f))
	,m_cursorHeight(0.0f)
	,m_riseY(0.0f)
	,m_cursorBlink(1.4f)
{
	ReadFontFileAndLoadToList(fontFileName);
}

//----------------------------------------------------------------------------------------------
void	Font::ReadFontFileAndLoadToList(const std::string& FontFileName)
{
	std::ifstream fontInfoFile;
	fontInfoFile.open(FontFileName); 
	if (!fontInfoFile) 
		MessageBoxA ( NULL, "Font File Not Found!", "FontFileError", MB_OK );



	unsigned int charcount = 0;
	if (fontInfoFile)  
	{
		std::string params;
		int i = 1;
		while (getline( fontInfoFile, params ))
		{
			if(i == 4)
			{
				params.erase( 0, params.find( "chars count=" ) + 12 );
				charcount = stoi( params.substr( 0, params.find_first_of( " " ) ) );
			}
			if( i > 4 &&  m_glyphInfoSheet.size() !=  charcount)
			{
				FaceData* faceData = new FaceData();
				int character;

				float x;
				float y;
				float height;
				float width;
				float xoffset;
				float yoffset;
				float xadvance;

				params.erase( 0, params.find( "id=" ) + 3 );
				character = stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "x=" ) + 2 );
				x = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "y=" ) + 2 );
				y = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "width=" ) + 6 );
				width = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "height=" ) + 7 );
				height = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "xoffset=" ) + 8 );
				xoffset = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "yoffset=" ) + 8 );
				yoffset = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				params.erase( 0, params.find( "xadvance=" ) + 9 );
				xadvance = (float)stoi( params.substr( 0, params.find_first_of( " " ) ) );

				

				faceData->character = (char)character;
				faceData->x = x;
				faceData->y = y;
				faceData->width = width;
				faceData->height = height;
				faceData->xoffset = xoffset;
				faceData->yoffset = yoffset;
				faceData->xadvance = xadvance;

				m_glyphInfoSheet[character] = faceData;

				if(height > m_cursorHeight)
					m_cursorHeight = height;
			}
			else
				++i;
		}
		fontInfoFile.close();
	}

}


//----------------------------------------------------------------------------------------------
vert_t* Font::CreateFontVertsPerChar(const std::string& text, const Vector2& position, const Rgba& color, int& bufferSize, vert_t* fontVerticies)
{

	//Loop through string and find the data per char
	size_t inputLength = text.length();
	if(fontVerticies == NULL)
		fontVerticies = new vert_t[inputLength * 6 ];

	m_cursorPosition = position;

	for(unsigned int i = 0; i < text.size(); i++)
	{
		char findThisChar = text[i]; 

		float x;
		float y;
		float width;
		float height;
		float xoffset;
		float yoffset;
		float xadvance;
		float scale = 1.0f;

		std::map< int, FaceData* >::iterator found = m_glyphInfoSheet.find(findThisChar);
		if(found->first == findThisChar)
		{
			x = found->second->x/256;
			y = found->second->y/256;
			width = found->second->width/256;
			height = found->second->height/256;
			xoffset = found->second->xoffset;
			yoffset = found->second->yoffset;
			xadvance = found->second->xadvance;
			float glyphW = found->second->width;
			float glyphH = found->second->height;

			
			//================================================================
			Vector2 mins(  m_cursorPosition.x + xoffset * scale   ,      m_cursorPosition.y + (32 - yoffset - glyphH) * scale   );
			Vector2 maxs(  (mins.x + glyphW) * scale              ,                               (mins.y + glyphH) * scale     );

			fontVerticies[i*6+0] = vert_t( Vector3(mins.x, mins.y + m_riseY, 0.0f),          Vector2( x        , y + height ),         color);
			fontVerticies[i*6+1] = vert_t( Vector3(maxs.x, mins.y + m_riseY, 0.0f),          Vector2( x + width, y + height ),         color);
			fontVerticies[i*6+2] = vert_t( Vector3(maxs.x, maxs.y + m_riseY, 0.0f),          Vector2( x + width,          y ),         color);
			///										    				           
			fontVerticies[i*6+3] = vert_t( Vector3(maxs.x, maxs.y + m_riseY, 0.0f),          Vector2( x + width,          y ),         color);
			fontVerticies[i*6+4] = vert_t( Vector3(mins.x, maxs.y + m_riseY, 0.0f),          Vector2( x        ,          y ),         color);
			fontVerticies[i*6+5] = vert_t( Vector3(mins.x, mins.y + m_riseY, 0.0f),          Vector2( x        ,  y + height),         color);
			//================================================================

			m_cursorPosition.x += xadvance*scale;
		}
	}
	bufferSize = inputLength * 6 * sizeof(vert_t);
	m_vertCount = inputLength * 6;
	return fontVerticies;
}


//----------------------------------------------------------------------------------------------
bool	Font::UpdateTextString()
{
	if(g_displayConsole)
	{
		//Detect space bar
		if(s_theInputSystem->wasKeyReleased(VK_SPACE))
		{
			m_myText += ' ';
			return true;
		}
		//Detect backspace
		if(s_theInputSystem->wasKeyReleased(VK_BACK))
		{
			if(m_myText.length() != 0)
			{
				m_myText.erase(m_myText.size() - 1);
				return true;
			}
		}



		//Detect A-Z/0-9
		for(int i = 0; i < NUMBER_OF_VIRTUAL_KEYS; i++ )
		{
			//UpperCase
			if( s_theInputSystem->isKeyDown(VK_SHIFT) && s_theInputSystem->wasKeyReleased(i)) 
			{	
				if( i >= 65 && i <= 90)
				{
					m_myText += (char)i;
					return true;
				}

				if( i == 57 ) // (
				{
					m_myText += (char)i - 17;
					return true;
				}

				if ( i == 48 ) // )
				{
					m_myText += (char)i - 7;
					return true;
				}
				if (i == 0xDE) // "
				{
					m_myText += 34;
					return true;
				}

				if (i == 0xBD) // _
				{
					m_myText += 95;
					return true;
				}
			}

			//Lowercase
			else if(s_theInputSystem->wasKeyReleased(i))
			{		
				if( i >= 65 && i <= 90)
				{
					m_myText += (char)(i + 32);
					return true;
				}
				if( i >= 188 &&  i<= 191)
				{
					m_myText += (char)(i - 144);
					return true;
				}
				if( i == 186 )
				{ 
					m_myText += 59;
					return true;
				}
				//Numbers
				if ( i >= 48 && i <= 57)
				{
					m_myText += (char)i;
					return true;
				}

				if (i == 0xDE) // '
				{
					m_myText += 39;
					return true;
				}
				//Special Chars

			}
		} 	
	}
	return false;
}


//----------------------------------------------------------------------------------------------
void	Font::CursorBlink(double deltaSeconds)
{
	if(m_cursorBlink > 0.7f)
		m_renderCursor = true;
	if(m_cursorBlink <= 0.7f)
		m_renderCursor = false;
	if(m_cursorBlink <= 0.0f)
		m_cursorBlink = 1.4f;

	m_cursorBlink -= (float)deltaSeconds;
}


//----------------------------------------------------------------------------------------------
void	Font::RenderCursor(OpenGLRenderer* renderer)
{
	if(m_renderCursor)
	{
		renderer->pushMatrix();
		renderer->SetOrthoGraphicView();
		renderer->SetModelColor(Rgba::GREEN);
		glDisable( GL_TEXTURE_2D );
		glBegin(GL_LINES);
		{
			glVertex3f(m_cursorPosition.x,  m_cursorPosition.y, 0.00f);
			glVertex3f(m_cursorPosition.x,  m_cursorPosition.y + m_cursorHeight, 0.00f);
		}
		glEnd();
		renderer->popMatrix();
	}
}