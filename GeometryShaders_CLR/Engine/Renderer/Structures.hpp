//================================================================
//                     Structures.hpp
//================================================================
#pragma once
#ifndef _included_Structures_
#define _included_Structures_
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/3D/Vector3.hpp"

//################################################################################################//
//##                       Vertex                                                               ##//
//################################################################################################//
struct vert_t
{
	vert_t()
		: m_position(Vector3(0.0f, 0.0f, 0.0f))
	{}
	vert_t(const Vector3& position, const Vector2& uv)
		: m_position(position)
		, m_uv(uv)
	{}
	vert_t(const Vector3& position, const Rgba& color)
		: m_position(position)
		, m_color(color)
	{}
	vert_t(const Vector3& position, const Vector2& uv, const Rgba& color)
		: m_position(position)
		, m_uv(uv)
		, m_color(color)
	{}
	vert_t(const Vector3& position, const Vector2& uv , const Vector3& normal)
		: m_position(position)
		, m_uv(uv)
		, m_norm(normal)
	{}
	vert_t(const Vector3& position, const Vector2& uv , const Vector3& normal, const Vector3& tangent, const Vector3& biTangent, const Rgba color)
		: m_position(position)
		, m_uv(uv)
		, m_norm(normal)
		, m_tang(tangent)
		, m_bitang(biTangent)
		, m_color(color)
	{}

	Vector3		m_position;
	Vector2		m_uv;
	Vector3		m_norm;
	Vector3		m_tang;
	Vector3		m_bitang;
	Rgba		m_color;	
};

struct vert_s
{
	vert_s();
	vert_s(const Vector3& position, const Vector2& uv, const Rgba& color)
		: m_position(position)
		, m_uv(uv)
		, m_color(color)
	{}
	vert_s(const Vector3& position, const Vector2& uv)
		: m_position(position)
		, m_uv(uv)
	{}
	vert_s(const Vector3& position, const Vector2& uv , const Vector3& normal)
		: m_position(position)
		, m_uv(uv)
		, m_normal(normal)
	{}
	vert_s(const Vector3& position, const Vector2& uv , const Vector3& normal, const Vector3& tangent, const Vector3& biTangent, const Rgba color)
		: m_position(position)
		, m_uv(uv)
		, m_normal(normal)
		, m_tangent(tangent)
		, m_bitangent(biTangent)
		, m_color(color)
	{}

	Vector3		m_position;
	Vector2		m_uv;
	Vector3		m_normal;
	Vector3		m_tangent;
	Vector3		m_bitangent;
	Rgba		m_color;



	unsigned char m_boneIndexs[4];
	Vector3		m_boneWeights;
};

#endif