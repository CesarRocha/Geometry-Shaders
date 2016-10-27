//================================================================
//                     RGBA.cpp
//================================================================
#include "RGBA.hpp"
#include "Engine\Math\3D\Matrix4x4.hpp"

const Rgba Rgba::RED	((unsigned char)255,  0,  0,255);
const Rgba Rgba::GREEN	((unsigned char)  0,255,  0,255);
const Rgba Rgba::BLUE	((unsigned char)  0,  0,255,255);
const Rgba Rgba::YELLOW	((unsigned char)255,255,  0,255);
const Rgba Rgba::WHITE	((unsigned char)255,255,255,255);
const Rgba Rgba::BLACK	((unsigned char)  0,  0,  0,255);
const Rgba Rgba::ORANGE((unsigned char)255, 140, 0, 255);

const Rgba Rgba::DEFAULT_TEXTURE_COLOR((unsigned char)255,255,255,255);
const Rgba Rgba::GREY((unsigned char)64,64,64,255);
const Rgba Rgba::PINK((unsigned char)255,111,193,255);
const Rgba Rgba::BLOODRED((unsigned char)255,40,40,255);
const Rgba Rgba::HALFRED((unsigned char)128,  0,  0,255);
const Rgba Rgba::QUARTERRED((unsigned char)64,  0,  0,255);
const Rgba Rgba::LIGHTBLOODRED((unsigned char)255,128,128,255);
const Rgba Rgba::BRIGHTBLUE((unsigned char)123, 168, 255, 255);
const Rgba Rgba::HEALINGBLUE((unsigned char)0, 233, 218, 255);
const Rgba Rgba::LIGHTBROWN((unsigned char)160, 122, 92, 255);
const Rgba Rgba::BROWN((unsigned char)106, 66, 44, 255);
const Rgba Rgba::HALFGREEN((unsigned char)  0,128,  0,255);
const Rgba Rgba::DARKBLUE((unsigned char) 0, 70, 165, 255);

Vector4 Rgba::RgbaToVector4(Rgba vector4)
{
	unsigned char outR = 255 * vector4.r;
	unsigned char outG = 255 * vector4.g;
	unsigned char outB = 255 * vector4.b;
	unsigned char outA = 255 * vector4.a;

	return Vector4(outR, outG, outB, outA);
}

void Rgba::operator *= (float scale)
{
	float rr = (float)r;
	float gg = (float)g;
	float bb = (float)b;
	float aa = (float)a;
	rr = (rr * (scale));
	gg = (gg * (scale));
	bb = (bb * (scale));
	aa = (aa * (scale));
	r = (unsigned char)(rr);
	g = (unsigned char)(gg);
	b = (unsigned char)(bb);
	a = (unsigned char)(aa);
}

