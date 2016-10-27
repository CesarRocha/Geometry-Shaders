//================================================================
//                     TheApp.hpp
//================================================================
#pragma once
#include "GameCommon.hpp"
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Renderer/AnimatedTexture.hpp"
#include "Engine/Renderer/OpenGLRenderer.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Engine/Console/Console.hpp"
#include "Engine/Renderer/Camera3D.hpp"
#include "Engine/Renderer/Font/BasicShader/BasicShader.hpp"
#include "World.hpp"

class TheApp
{
public:
	TheApp();
	~TheApp();
	static TheApp* s_theApp;	

	void	Startup(void* windowHandle);
	void	Run();
	void	Shutdown();

	void	ProcessInput();
	void	UpdateGameTime();

	void	UpdateWorld();
	void	RenderWorld();

	double	GetDeltaSeconds() {return m_deltaSeconds;}

private:
	void*					m_windowHandle;
	OpenGLRenderer*			m_renderer;	
	World*					m_world;
	InputSystem*			m_inputSystem;
	double					m_deltaSeconds;


	BasicShader*			m_debugLineShader;
	Font					m_debugFont;
	void CreateDebugText();
	void UpdateDebugText();
};

