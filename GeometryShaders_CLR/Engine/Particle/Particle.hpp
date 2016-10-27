//================================================================
//                     Particle.hpp
//================================================================
#pragma once
#ifndef __INCLUDE_PARTICLE_
#define __INCLUDE_PARTICLE_
#include "Engine/Math/3D/Vector3.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Renderer/RGBA.hpp"
#include "Engine/Renderer/Camera3D.hpp"
#include <list>

class Particle
{
public:
	Particle();
	~Particle();
	 
	void Update(const double& deltaSeconds);
	void Render(OpenGLRenderer* renderer);
	Rgba SetRandomColor() {return Rgba(GetRandomFloatZeroToOne(), GetRandomFloatZeroToOne(), GetRandomFloatZeroToOne());}

	Vector3 GetPosition()	{return m_position;}
	Rgba	GetColor()		{return m_color;}

private:	
	friend class Emitter;

	Vector3 m_position; 
	Vector3 m_velocity; 
	Rgba	m_color;
	Vector3 m_acceleration; 

	float	m_lifeSpan;
	float	m_startTime;
	Vector3 m_wind;

};

//================================================================
//                     Emitter
//================================================================
enum EmitterType
{
	EXPLOSION,
	CLEANEXPLOSION,
	FIREWORK,
	FOUNTIAN,
	SMOKE,
	RAIN,
};
class Emitter
{
public:



	Emitter(const Vector3& position, const int numOfParticles, EmitterType type, bool fade);
	~Emitter();
	void Update(const double deltaSeconds);
	void Render(OpenGLRenderer* renderer);
	void Render();
	void CreateExplosion();
	void CreateCleanExplosion();
	void CreateFirework();
	void CreateFountian();
	void CreateSmoke();
	void CreateRain();

private:
	friend class EmitterManager;
	Vector3		m_emitterPosition;
	float		m_newLifeSpan;
	int			m_numOfParticles;
	Particle*	m_particles;
	bool		m_hasWind;
	Vector3		m_emitterWind;
	bool		m_fade;
	//Not Needed. Makes useless object
	Emitter();
};
//================================================================
//                     EmitterManager
//================================================================
class EmitterManager
{
public:
	EmitterManager();
	~EmitterManager();


	void		Update(const double deltaSeconds);
	void		Render(OpenGLRenderer* renderer);
	Emitter*	AddEmitter(const Vector3& position, const int numOfParticles, EmitterType type, bool fade = true);
	void		DestroyEmitter( Emitter& pt);
	void		GetParticlePositionsFromEmitter(vert_t verts[], Emitter* emitter);
	void GetParticlePositionsFromEmitter(vert_t verts[], Emitter* emitter, int start, int end);
	void		GetParticleColorsFromEmitter(vert_t verts[], Emitter* emitter);
	
	typedef std::vector<Emitter*> EmitterList;
	EmitterList m_Emitters;
	Vector3 m_emitterManagerWind;
private:

};

#endif