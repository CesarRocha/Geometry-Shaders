#include "World.hpp"
vert_t* particleVerts    = new vert_t[g_numOfParticles];
vert_t  debugTileVerts[] = 
{
	vert_t( Vector3( -1.0f, -1.0f, 0.0f    ), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f )), 
	vert_t( Vector3( -1.0f,  1.0f, 0.0f    ), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f )), 
	vert_t( Vector3(  1.0f, -1.0f, 0.0f    ), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f )), 
	vert_t( Vector3(  1.0f, -1.0f, 0.0f    ), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f )), 
	vert_t( Vector3( -1.0f,  1.0f, 0.0f    ), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f )), 
	vert_t( Vector3(  1.0f,  1.0f, 0.0f    ), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f )), 
};



//===================================================================================================
//					class World																	   ==
//===================================================================================================
World::World(const Vector2& displaySize)
	: m_displaySize(displaySize)
	, m_time(0.0)
	, m_explode(false)
	, m_direction(true)
	, m_woman(nullptr)
	, m_emitterManager(new EmitterManager())
{	
}
World::~World()
{
}



//===================================================================================================
void World::StartUp()	
{
	CreateParticleSystem();
	CreateDebugTile();
}
void World::Input(InputSystem* m_inputSystem)
{

	//Emit Particle

	if (m_inputSystem->wasKeyReleased('1'))
		m_emitterManager->AddEmitter(Vector3(0.0f, 0.0f, 0.0f), g_numOfParticles, EXPLOSION, false);
	if (m_inputSystem->wasKeyReleased('2'))
		m_emitterManager->AddEmitter(Vector3(0.0f, 0.0f, 0.0f), g_numOfParticles, CLEANEXPLOSION, false);
	if (m_inputSystem->wasKeyReleased('3'))
		m_emitterManager->AddEmitter(Vector3(0.0f, 0.0f, 0.0f), g_numOfParticles, RAIN, false);

	


	//Change Particle Type
	if (m_inputSystem->wasKeyReleased(VK_NUMPAD1))
	{
		g_geoType = BILLBOARD;
		m_particleRendererMesh.m_material.m_shader = Shader("../Run_Win32/shaders/particleBillboard", "../Run_Win32/shaders/particleBillboard", "../Run_Win32/shaders/particleBillboard");
	}
	if (m_inputSystem->wasKeyReleased(VK_NUMPAD2))
	{
		g_geoType = CUBE;
		m_particleRendererMesh.m_material.m_shader = Shader("../Run_Win32/shaders/particleCube", "../Run_Win32/shaders/particleCube", "../Run_Win32/shaders/particleCube");
	}
	if (m_inputSystem->wasKeyReleased(VK_NUMPAD3))
	{
		g_geoType = ORBIT;
		m_particleRendererMesh.m_material.m_shader = Shader("../Run_Win32/shaders/particleCubeOrbit", "../Run_Win32/shaders/particleCubeOrbit", "../Run_Win32/shaders/particleCubeOrbit");
	}


	//Make Model Explode
	if(m_inputSystem->wasKeyReleased('T'))
	{
		m_explode = !m_explode;
		if(!m_explode)
		{
			m_woman->m_modelRenderer.m_startTime = 0.0f;
			m_time = 0.0;
			m_explode = false;
		}
	}

	//Reverse Model Explosion
	if(m_inputSystem->wasKeyReleased('R'))
		m_direction = !m_direction;

	//Create Model
	//Reset Model
	if(m_inputSystem->wasKeyReleased('M') && !g_renderModel )
	{
		CreateModel();
		g_renderModel = true;
	}
	else if(m_inputSystem->wasKeyReleased('M') && g_renderModel )
		g_renderModel = false;
	
}
void World::Update(double deltaSeconds)
{
	if(g_renderModel)
		UpdateModel(deltaSeconds);

	UpdateParticleSystem(deltaSeconds);
	UpdateDebugTile();
}      
void World::Render(OpenGLRenderer* renderer)
{
	if(g_renderModel)
		RenderModel(renderer);

	RenderParticleSystem(renderer);
	RenderDebugTile();	
}
void World::ShutDown()
{
}



//===================================================================================================
void World::CreateParticleSystem()
{
	m_particleMesh = Mesh(particleVerts, g_numOfParticles);

	m_particleSampler.SetDiffuse(Texture::CreateOrGetTexture("../Run_Win32/maps/test.png"));
	
	switch (g_geoType)	
	{
		case CUBE: 
			m_particleShader = Shader("../Run_Win32/shaders/particleCube", "../Run_Win32/shaders/particleCube", "../Run_Win32/shaders/particleCube"); break;
		case BILLBOARD: 
			m_particleShader = Shader("../Run_Win32/shaders/particleBillboard", "../Run_Win32/shaders/particleBillboard", "../Run_Win32/shaders/particleBillboard"); break;
		case ORBIT: 
			m_particleShader =  Shader("../Run_Win32/shaders/particleCubeOrbit", "../Run_Win32/shaders/particleCubeOrbit", "../Run_Win32/shaders/particleCubeOrbit"); break;
	}

	m_particleMaterial		= Material(m_particleShader, m_particleSampler);
	m_particleRendererMesh	= MeshRenderer(m_particleMesh, m_particleMaterial, GEOPOINT);
}			
void World::UpdateParticleSystem(double deltaSeconds)
{
 	if(MasterClock::GetMasterClock()->IsPaused() == false)
 		m_emitterManager->Update(deltaSeconds);
}
void World::RenderParticleSystem(OpenGLRenderer* renderer)
{
	if(m_emitterManager->m_Emitters.size() != 0 )
	{		
		for(int index = 0; index < (int)m_emitterManager->m_Emitters.size(); index++)
		{
			m_emitterManager->GetParticlePositionsFromEmitter(particleVerts, m_emitterManager->m_Emitters[index]);
			m_particleMesh.CopyToBufferVBO(m_particleMesh.m_vboID, particleVerts, g_numOfParticles);
			m_particleRendererMesh.Render(g_masterCamera->m_viewMatrix, g_masterCamera->m_projPersMatrix, Matrix4x4(), g_masterCamera->m_worldPosition, MasterClock::GetMasterClock()->GetClockDeltaSeconds());
		}
	}
}



//===================================================================================================
void World::CreateModel()
{
	//Create Model
	m_woman = new ModelLoader("woman", "modelExplode");	
	m_woman->m_modelRenderer.m_material.m_materialAmbientLight.w = 0.1f;
	m_woman->m_modelRenderer.m_material.m_lightCount = 1;

	//Set Fog Value
	m_woman->m_modelRenderer.m_fogStartDistance		= 2.0f;
	m_woman->m_modelRenderer.m_fogEndDistance		= 5.0f;
	m_woman->m_modelRenderer.m_fogColorAndIntensity = Vector3( 0.1f, 0.1f, 0.1f);
}
void World::UpdateModel(double deltaSeconds)
{
	//Explosion Direction
	if(m_explode && m_direction)
		m_time += deltaSeconds;
	else if(m_explode && !m_direction)
		m_time -= deltaSeconds;


	m_woman->m_modelRenderer.m_material.m_lightArray[0].m_lightPosition = Vector3( cos(MasterClock::GetMasterClock()->GetClockCurrentSeconds())*(2),       sin(MasterClock::GetMasterClock()->GetClockCurrentSeconds())*(2), +1.5f );
}
void World::RenderModel(OpenGLRenderer* renderer)
{
	//Shows location of light source
	renderer->DrawDebugPoint(m_woman->m_modelRenderer.m_material.m_lightArray[0].m_lightPosition, 0.1f, Rgba::GREEN);

	//Render model
	m_woman->m_modelRenderer.Render(g_masterCamera->m_viewMatrix, g_masterCamera->m_projPersMatrix, Matrix4x4(), g_masterCamera->m_worldPosition, m_time); 
}



//===================================================================================================
void World::CreateDebugTile()
{
	m_testTileMesh		= Mesh(debugTileVerts, 6 ); 
	m_testTileSampler.SetDiffuse(Texture::CreateOrGetTexture("../Run_Win32/maps/test.png"));
	m_testTileShader	= Shader("../Run_Win32/shaders/advanced_light", "../Run_Win32/shaders/advanced_light");

	m_testTileMaterial		= Material(m_testTileShader, m_testTileSampler);
	m_testTileMaterial.m_materialAmbientLight.w = .1f;
	m_testTileMaterial.m_lightCount = 1;
	m_testTileMaterial.m_lightArray[0].m_lightColor = Rgba(1.0f, 1.0f, 1.0f, .5f);

	m_testTileMeshRenderer = MeshRenderer(m_testTileMesh, m_testTileMaterial);
}
void World::UpdateDebugTile()
{
	m_testTileMeshRenderer.m_material.m_lightArray[0].m_lightPosition = g_masterCamera->m_worldPosition;
}
void World::RenderDebugTile()
{
	if (g_debugTile)
		m_testTileMeshRenderer.Render(g_masterCamera->m_viewMatrix, g_masterCamera->m_projPersMatrix, Matrix4x4(), g_masterCamera->m_worldPosition);
}