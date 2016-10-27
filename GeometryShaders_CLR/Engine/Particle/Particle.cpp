//================================================================
//                     Particle.cpp
//================================================================
#pragma warning( disable: 4244 ) // '-=' : conversion from 'float' to 'unsigned char', possible loss of data
#include "Engine/Particle/Particle.hpp"
#include <algorithm>

Particle::Particle()
	: m_wind(Vector3(0.0f, 0.0f, 0.0f))
	, m_startTime(0.0f)
	, m_lifeSpan(0.0f)
{
}
Particle::~Particle()
{
}
void Particle::Update(const double& deltaSeconds)
{
	m_velocity += (m_acceleration  + m_wind )* (float)deltaSeconds;
	m_position += m_velocity * (float)deltaSeconds;
	if(m_lifeSpan > 0.0f)
		m_lifeSpan -= (float)deltaSeconds;		
}
void Particle::Render(OpenGLRenderer* renderer)
{
	renderer->pushMatrix();
	renderer->SetModelColor(m_color);
	renderer->SetModelViewTranslation(m_position.x, m_position.y, m_position.z);
	//renderer->DrawCircularPolygon(.02f, 4);
	glBegin(GL_LINES);
	glVertex3f(-0.005f, 0.0f, 0.0f);
	glVertex3f( 0.005f, 0.0f, 0.0f);

	glVertex3f(0.0f, 0.005f, 0.0f);
	glVertex3f(0.0f,-0.005f, 0.0f);

	glVertex3f(0.0f, 0.0f,  0.005f);
	glVertex3f(0.0f, 0.0f, -0.005f);

	glVertex3f( 0.005f, 0.005f,  0.005f);
	glVertex3f(-0.005f,-0.005f, -0.005f);

	glVertex3f(-0.005f, 0.005f,  0.005f);
	glVertex3f( 0.005f,-0.005f, -0.005f);

	glVertex3f(-0.005f,-0.005f,  0.005f);
	glVertex3f( 0.005f, 0.005f, -0.005f);

	glVertex3f( 0.005f, -0.005f,  0.005f);
	glVertex3f(-0.005f,  0.005f, -0.005f);
	glEnd();
	renderer->popMatrix();
}

//################################################################################################//
//##                        Emitter                                                             ##//
//################################################################################################//
Emitter::Emitter()
{

}
Emitter::Emitter(const Vector3& position, const int numOfParticles, EmitterType type, bool fade)
	: m_emitterPosition(position)
	, m_numOfParticles(numOfParticles)
	, m_particles( new Particle[m_numOfParticles])
	, m_fade(fade)
{
	if(type == EXPLOSION)
		CreateExplosion();
	if(type == CLEANEXPLOSION)
		CreateCleanExplosion();
	if(type == FIREWORK)
		CreateFirework();
	if(type == FOUNTIAN)
		CreateFountian();
	if(type == SMOKE)
		CreateSmoke();
	if(type == RAIN)
		CreateRain();
}
Emitter::~Emitter()
{
	//delete this;
}
void Emitter::Update(const double deltaSeconds)
{
// 	for(std::vector<Particle*>::iterator iter = m_particles.begin(); iter < m_particles.end(); iter++)
// 	{
// 		Particle* particle = (*iter);
// 		if(particle->m_startTime <= 0.0f)
// 		{
// 			if(particle->m_lifeSpan <= 0.0f) 
// 			{
// 				particle->m_color.a -= (float)deltaSeconds * 2.0f;
// 				if( particle->m_color.a <= 0.0f)
// 				{
// 					
// 					iter = m_particles.erase(iter);
// 					continue;
// 				}
// 			}
// 			else
// 				particle->m_lifeSpan -= (float)deltaSeconds;
// 		
// 			//
// 			particle->m_wind = m_emitterWind;
// 			//
// 		
// 			particle->Update(deltaSeconds);
// 		}
// 		else
// 			particle->m_startTime -= (float)deltaSeconds;
// 	}


	for( int i = 0; i < m_numOfParticles; ++i )
	{ 
		if(m_particles[i].m_startTime <= 0.0f)
		{
			if(m_particles[i].m_lifeSpan <= 0.0f && m_fade) 
			{
				m_particles[i].m_color.a -= (float)deltaSeconds * 30.0f;
				if( m_particles[i].m_color.a <= 0.0f)
				{
					m_particles[i] = m_particles[m_numOfParticles -1];
					m_numOfParticles--;		 
				}
			}
			else
				m_particles[i].m_lifeSpan -= (float)deltaSeconds;

			//
			m_particles[i].m_wind = m_emitterWind;
			//

			m_particles[i].Update(deltaSeconds);
		}
		else
			m_particles[i].m_startTime -= (float)deltaSeconds;
	}
}
void Emitter::Render(OpenGLRenderer* renderer)
{
// 	for(std::vector<Particle*>::iterator iter = m_particles.begin(); iter < m_particles.end(); iter++)
// 	{
// 		Particle* particle = (*iter);
// 		particle->Render(renderer);
// 	}
	for( int i = 0; i < m_numOfParticles; ++i)
		if(m_particles[i].m_startTime <= 0.0f)
			m_particles[i].Render(renderer);

}
void Emitter::CreateExplosion()
{
	for(int i = 0; i < m_numOfParticles; ++i)
	{
		Vector3 k;
		k.GetRandomPointOnSphere();
		k.Normalize();
		float speed = GetRandomFloatInRange(.7f, 2.0f);
		//Particle* particle = new Particle();
		m_particles[i].m_position = m_emitterPosition;
		m_particles[i].m_velocity = Vector3(k.x * speed, k.y * speed, k.z * speed);
		m_particles[i].m_lifeSpan = 30.0f;
		m_particles[i].m_color = Rgba::WHITE;
		//m_particles[i] = particle;
	}
}
void Emitter::CreateCleanExplosion()
{
	for(int i = 0; i < m_numOfParticles; ++i)
	{
		Vector3 k;
		k.GetRandomPointOnSphere();
		k.Normalize();
		float speed = 2.0f;
		//Particle* particle = new Particle();
		m_particles[i].m_position = m_emitterPosition;
		m_particles[i].m_velocity = Vector3(k.x * speed, k.y * speed, k.z * speed);
		m_particles[i].m_lifeSpan = 10.0f;
		m_particles[i].m_color = Rgba::WHITE;
		//m_particles.push_back(particle);
	}
}
void Emitter::CreateFirework()
{
	int rand = GetRandomIntInRange(0, 2);
	Rgba colorin;
	if(rand == 0)
		colorin = Rgba::RED;
	if(rand == 1)
		colorin = Rgba::WHITE;
	if(rand == 2)
		colorin = Rgba::BLUE;
	for(int i = 0; i < m_numOfParticles; ++i)
	{
		Vector3 k;
		k.GetRandomPointOnSphere();
		k.Normalize();
		float speed = GetRandomFloatZeroToOne();
		//Particle* particle = new Particle();
		m_particles[i].m_position = m_emitterPosition;
		m_particles[i].m_velocity = Vector3(k.x * speed, k.y * speed, (k.z) * speed);
		m_particles[i].m_acceleration = Vector3(0.0f, 0.0f, -1.0f);
		m_particles[i].m_lifeSpan = 10.0f;
		m_particles[i].m_color = colorin;
		//m_particles.push_back(particle);
	}
}
void Emitter::CreateFountian()
{
	for(int i = 0; i < m_numOfParticles; ++i )
	{
		float openingRadius = GetRandomFloatInRange(-.3f, .3f);
		Vector3 k;
		k.GetRandomPointOnSphere();
		k.Normalize();
		//Particle* particle = new Particle();
 		m_particles[i].m_velocity = Vector3(k.x * openingRadius, k.y * openingRadius, GetRandomFloatInRange(2.8f, 3.2f));
		m_particles[i].m_acceleration = Vector3(0.0f, 0.0f, -1.0f);
		m_particles[i].m_lifeSpan = 10.0f;
		m_particles[i].m_color = Rgba(Rgba::BLUE);
		m_particles[i].m_startTime = (i * .001f);//timeInterval;
		//m_particles.push_back(particle);
	}
}
void Emitter::CreateSmoke()
{
	for(int i = 0; i < m_numOfParticles; ++i )
	{
		float openingRadius = GetRandomFloatInRange(-.2f, .2f);
		float topRadius = GetRandomFloatInRange(-.25f, .25f);
		Vector3 k;
		k.GetRandomPointOnSphere();
		k.Normalize();
		//Particle* particle = new Particle();
		m_particles[i].m_position = Vector3(k.x * openingRadius, k.y * openingRadius, 0.0f);
		m_particles[i].m_velocity = Vector3(k.x * topRadius, k.y * topRadius, GetRandomFloatInRange(1.0f, 1.2f));
		m_particles[i].m_lifeSpan = 0.10f;
		m_particles[i].m_color = Rgba(Rgba::ORANGE);
		m_particles[i].m_startTime = (i * .001f);//timeInterval;
		//m_particles.push_back(particle);
	}
}
void Emitter::CreateRain()
{
	for(int i = 0; i < m_numOfParticles; ++i )
	{
		Vector3 k;
		k.GetRandomPointOnSphere();
		k.Normalize();
		//Particle* particle = new Particle();
		m_particles[i].m_position = Vector3(GetRandomFloatInRange(-30.0f, 30.0f), GetRandomFloatInRange(-30.0f, 30.0f), 100.0f);
		m_particles[i].m_velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_particles[i].m_acceleration = Vector3(0.0f, 0.0f, -2.0f);
		m_particles[i].m_lifeSpan = 15.0f;
		m_particles[i].m_color = Rgba(Rgba::BRIGHTBLUE);
		m_particles[i].m_startTime = (i * .0005f);//timeInterval;
		//m_particles.push_back(particle);
	}
}

//================================================================
//                     Particle.cpp
//================================================================
EmitterManager::EmitterManager()
	: m_emitterManagerWind(Vector3(0.0f, 0.0f, 0.0f))
{
}
EmitterManager::~EmitterManager()
{
}
void EmitterManager::Update(const double deltaSeconds)
{
	if(m_Emitters.size() != 0)
	{
		for( EmitterList::iterator i =  m_Emitters.begin(); i != m_Emitters.end(); )
		{
			Emitter& emitter = **i;

			if(emitter.m_numOfParticles == 0)
			{
				i = m_Emitters.erase(i);
				break;
			}
			else
			{
				emitter.m_emitterWind = m_emitterManagerWind;
				emitter.Update(deltaSeconds);
				i++;
			}
		}	
	}
}
void EmitterManager::Render(OpenGLRenderer* renderer)
{
	for( EmitterList::iterator i =  m_Emitters.begin(); i != m_Emitters.end(); i++)
	{
		Emitter& emitter = **i;
		emitter.Render(renderer);
	}
}
Emitter* EmitterManager::AddEmitter(const Vector3& position, const int numOfParticles, EmitterType type, bool fade)
{
	Emitter* newEmitter =	 new Emitter(position, numOfParticles, type, fade);
	m_Emitters.push_back(newEmitter);
	return newEmitter;
}
void EmitterManager::DestroyEmitter(Emitter& pt)
{
	EmitterList::iterator i = std::find(m_Emitters.begin(), m_Emitters.end(), &pt);
	if( i != m_Emitters.end())
		i = m_Emitters.erase(i);
}

void EmitterManager::GetParticlePositionsFromEmitter(vert_t verts[], Emitter* emitter)
{
	if(m_Emitters.size() != 0)
	{
		const int size = emitter->m_numOfParticles;
		Vector3 position;

		for(int index = 0; index < size; index++)
			verts[index].m_position = emitter->m_particles[index].GetPosition();
	}
}
void EmitterManager::GetParticlePositionsFromEmitter(vert_t verts[], Emitter* emitter, int start, int end)
{
	if(m_Emitters.size() != 0)
	{
		Vector3 position;
		if(end > emitter->m_numOfParticles)
			end = emitter->m_numOfParticles;

		for(int index = start-1; index < end; index++)
			verts[index].m_position = emitter->m_particles[index].GetPosition();
	}
}
void EmitterManager::GetParticleColorsFromEmitter(vert_t verts[], Emitter* emitter)
{
	if(m_Emitters.size() != 0)
	{
		const int size = emitter->m_numOfParticles;
		Vector3 position;

		for(int index = 0; index < size; index++)
			verts[index].m_color = emitter->m_particles[index].GetColor();
	}
}
