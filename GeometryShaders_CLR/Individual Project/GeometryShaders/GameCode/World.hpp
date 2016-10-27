#pragma once
#ifndef __INCLUDE_WORLD__
#define __INCLUDE_WORLD__
#include "GameCommon.hpp"
#include "Engine/Renderer/ModelLoader/ModelLoader.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Particle/Particle.hpp"
#include "Engine/Utility/Utility.hpp"



//===================================================================================================
//					class World																	   ==
//===================================================================================================
class World
{
public:
	
	//Constructors
	World(const Vector2& displaySize);
	~World();

	//Systems
	void	StartUp();
	void	ShutDown();
	void	Input(InputSystem* m_inputSystem);
	void	Update(double deltaSeconds);
	void	Render(OpenGLRenderer* renderer);

	//Model
	void CreateModel();
	void UpdateModel(double deltaSeconds);
	void RenderModel(OpenGLRenderer* renderer);

	//Particles
	void CreateParticleSystem();
	void UpdateParticleSystem(double deltaSeconds);
	void RenderParticleSystem(OpenGLRenderer* renderer);

	//Debug
	void CreateDebugTile();
	void UpdateDebugTile();
	void RenderDebugTile();


private:
	friend class TheApp;
	Vector2			m_displaySize;

	ModelLoader*	m_woman;
	MeshRenderer	m_modelMeshRenderer;

	EmitterManager* m_emitterManager;

	Mesh			m_particleMesh;
	Shader			m_particleShader;
	Sampler			m_particleSampler;
	Material		m_particleMaterial;
	MeshRenderer	m_particleRendererMesh;

	Mesh			m_testTileMesh;
	Shader			m_testTileShader;
	Sampler			m_testTileSampler;
	Material		m_testTileMaterial;
	MeshRenderer	m_testTileMeshRenderer;

	bool			m_explode;
	double			m_time;
	bool			m_direction;
};

#endif