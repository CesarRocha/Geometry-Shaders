//================================================================
//                     RGBA.hpp
//================================================================
#pragma once
#ifndef __INCLUDE_RGBA__
#define __INCLUDE_RGBA__

class Vector4;
class Rgba
{
public:
	Rgba()
	: r(255)
	, g(255)
	, b(255)
	, a(255)
	{};

	Rgba(float r, float g, float b)									
		: r((unsigned char)(r * 255.0f))
		, g((unsigned char)(g * 255.0f))
		, b((unsigned char)(b * 255.0f))
		, a(255) 
	{}; 
	Rgba(unsigned char r, unsigned char g, unsigned char  b, unsigned char a )	: r(r), g(g), b(b), a(a){}
	Rgba(unsigned char r, unsigned char g, unsigned char  b )					: r(r), g(g), b(b), a(255){}

	static Vector4 RgbaToVector4(Rgba vector4);
	void operator *= (float scale);
	unsigned char r; 
	unsigned char g;
	unsigned char b;
	unsigned char a;

	static const Rgba RED;
	static const Rgba GREEN;
	static const Rgba BLUE;
	static const Rgba YELLOW;
	static const Rgba WHITE;
	static const Rgba BLACK;
	static const Rgba ORANGE;

	static const Rgba DEFAULT_TEXTURE_COLOR;

	static const Rgba GREY;

	static const Rgba PINK;

	//Red
	static const Rgba BLOODRED;
	static const Rgba HALFRED;
	static const Rgba QUARTERRED;
	static const Rgba LIGHTBLOODRED;

	//Blue
	static const Rgba BRIGHTBLUE;
	static const Rgba HEALINGBLUE;
	static const Rgba DARKBLUE;

	
	static const Rgba LIGHTBROWN;
	static const Rgba BROWN;

	//Green
	static const Rgba HALFGREEN;
	//Needs accessors to get these as floats.
};

#endif
