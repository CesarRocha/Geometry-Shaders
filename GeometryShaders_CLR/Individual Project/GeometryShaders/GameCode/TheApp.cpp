#include "TheApp.hpp"
#include <iomanip>
#include <Windows.h>
#include <gl/GL.h>



//===================================================================================================
//                     class TheApp								                                   ==
//===================================================================================================
TheApp::TheApp()
	: m_inputSystem(NULL)
	, m_renderer(NULL)
	, m_windowHandle(NULL)
{
}
TheApp::~TheApp()
{
}



//===================================================================================================
void TheApp::Startup(void* windowHandle)
{
	LogClearf();

	m_windowHandle = windowHandle;
	m_renderer = new OpenGLRenderer();

	//New Renderer
	if (m_renderer)
		m_renderer->startup((HWND)windowHandle);

	float x = m_renderer->GetDisplayWidth();
	float y = m_renderer->GetDisplayHeight();
	Vector2 displaySize(x, y);


	DeveloperLog::CreateConsoleLogAndFPS();
	CreateDebugText();
	m_renderer->CreateDebugGridShader();
	m_renderer->CreateDebugCoordinateShader();

	//New Input
	m_inputSystem = new InputSystem();
	if (m_inputSystem)
		m_inputSystem->Startup(windowHandle);


	//Setup Camera
	g_masterCamera->InitializeCamera(0.0f, 0.0f, 0.0f, m_inputSystem);
	g_masterCamera->CreateOrthoMatrix(displaySize.x, displaySize.y, 1.0f, -1.0f);


	//New world
	m_world = new World(displaySize);
	if (m_world)
		m_world->StartUp();
}
void TheApp::Run()
{
	while (g_appIsRunning)
	{
		ProcessInput();
		UpdateWorld();
		RenderWorld();
	}
}
void TheApp::Shutdown()
{
	if (m_renderer)
		m_renderer->shutdown();

	if (m_inputSystem)
		m_inputSystem->Shutdown();
}



//===================================================================================================
void TheApp::ProcessInput()
{
	if (m_inputSystem)
	{
		m_inputSystem->Update();

		//Pause App
		if (m_inputSystem->wasKeyReleased('P'))
			MasterClock::GetMasterClock()->SetPaused(!MasterClock::GetMasterClock()->IsPaused());

		//Render App
		if (m_inputSystem->isKeyDown(VK_CONTROL) && m_inputSystem->wasKeyReleased('X'))
			g_renderWorld = !g_renderWorld;

		//Show/Hide FPS
		if (m_inputSystem->isKeyDown(VK_CONTROL) && m_inputSystem->wasKeyReleased('F'))
			g_displayFPS = !g_displayFPS;

		//Show/Hide Console
		if (m_inputSystem->isKeyDown(VK_CONTROL) && m_inputSystem->wasKeyReleased(VK_SHIFT))
			DeveloperLog::GetDeveloperConsole()->ToggleConsoleVisibility();

		//Toggle Window-to-mouse Lock
		if (m_inputSystem->isKeyDown(VK_CONTROL) && m_inputSystem->wasKeyReleased('C'))
		{
			g_use3DCamera = !g_use3DCamera;
			ShowCursor(!g_use3DCamera);
		}

		//End App
		if (m_inputSystem->isKeyDown(VK_ESCAPE))
			g_appIsRunning = false;
		else if (m_inputSystem->isReadyToQuit())
			g_appIsRunning = false;
	}

	if (m_world)
		m_world->Input(m_inputSystem);
}



//===================================================================================================
void TheApp::UpdateGameTime()
{
	static double lastTimeSeconds = MasterClock::GetMasterClock()->GetAbsoluteTimeSeconds();
	double currentTimeSeconds = MasterClock::GetMasterClock()->GetAbsoluteTimeSeconds();
	m_deltaSeconds = currentTimeSeconds - lastTimeSeconds;
	while (m_deltaSeconds < g_mininumSecondsPerFrame)
	{
		currentTimeSeconds = MasterClock::GetMasterClock()->GetAbsoluteTimeSeconds();
		m_deltaSeconds = currentTimeSeconds - lastTimeSeconds;
		double timeRemaining = g_mininumSecondsPerFrame - m_deltaSeconds;
		if (timeRemaining > .002)
			Sleep(1);
	}
	if (m_deltaSeconds > g_maximumSecondsPerFrame)
		m_deltaSeconds = g_maximumSecondsPerFrame;
	lastTimeSeconds = currentTimeSeconds;

	MasterClock::GetMasterClock()->UpdateClock(m_deltaSeconds);



	std::stringstream text;
	text << "FPS: " << std::fixed << std::setprecision(2) << (1.0 / m_deltaSeconds);
	std::string fpsString = text.str();
	DeveloperLog::GetFPSFont()->m_myText = fpsString;

}
void TheApp::UpdateWorld()
{
	UpdateGameTime();
	UpdateDebugText();

	
	if (!g_displayConsole)
	{
		if (g_use3DCamera)
			g_masterCamera->UpdateCamera(m_deltaSeconds);
	}
	else
	{
		DeveloperLog::GetDeveloperLog()->CursorBlink(m_deltaSeconds);
		DeveloperLog::DetectInputForConsole();
	}

	if (g_displayFPS)
		DeveloperLog::UpdateDeveloperLogShader(DeveloperLog::GetFPSShader(), DeveloperLog::GetFPSFont(), Vector2(5.0f, m_renderer->GetDisplayHeight() * .96f), Rgba::HEALINGBLUE);

	g_masterCamera->CreateProjPers(g_masterCamera->m_projPersMatrix, 60.0f, (16.0f / 9.0f), 0.1f, 10000.0f);
	g_masterCamera->CreateViewMatrix(g_masterCamera->m_viewMatrix);

	if (m_world)
		m_world->Update(m_deltaSeconds);
}



//===================================================================================================
void TheApp::RenderWorld()
{

	m_renderer->RenderBasicRenderingFunctions3D(g_clearBufferColor);

	//Render Game World
	if (g_renderWorld)
		m_world->Render(m_renderer);

	//Draw Debug Lines
	if (g_drawAxes)
	{
		m_renderer->DrawDebugGridShader();
		m_renderer->DrawDebugCoordinateShader();
	}


	//Show Console
	if (g_displayConsole)
	{
		DeveloperLog::GetDeveloperConsole()->RenderCursor(m_renderer);
		DeveloperLog::GetDeveloperConsoleShader()->RenderBasicShader(Matrix4x4(), g_masterCamera->m_orthoMatrix, DeveloperLog::GetDeveloperConsole()->m_vertCount);
		DeveloperLog::GetDeveloperLogShader()->RenderBasicShader(Matrix4x4(), g_masterCamera->m_orthoMatrix, DeveloperLog::GetDeveloperLog()->m_vertCount);
	}


	//Show FPS Counter
	if (g_displayFPS)
		DeveloperLog::GetFPSShader()->RenderBasicShader(Matrix4x4(), g_masterCamera->m_orthoMatrix, DeveloperLog::GetFPSFont()->m_vertCount);


	//Show PolygonLines
	if (g_polygonLines)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//Informational Text
	m_debugLineShader->RenderBasicShader(Matrix4x4(), g_masterCamera->m_orthoMatrix, m_debugFont.m_vertCount);


	m_renderer->SwapBuffers();
}
void TheApp::CreateDebugText()
{
	m_debugFont = Font("../Run_Win32/text.txt");
	m_debugLineShader = new BasicShader("../Run_Win32/shaders/font", "../Run_Win32/shaders/text.png");

	int bufferSize = 0;
	vert_t* verts =  DeveloperLog::GetFPSFont()->CreateFontVertsPerChar(m_debugFont.m_myText, m_debugFont.m_cursorPosition, Rgba::YELLOW, bufferSize);
	m_debugLineShader->m_myVerts	= verts;
	m_debugLineShader->m_buffer	= m_debugLineShader->CreateBuffer( m_debugLineShader->m_myVerts, bufferSize );
	m_debugLineShader->m_VAO		= m_debugLineShader->CreateVAO( m_debugLineShader->m_buffer);
}
void TheApp::UpdateDebugText()
{
	int bufferSize = 0;
	static std::vector<vert_t> temp;
	temp.resize(m_debugFont.m_myText.length() * 6);

	std::stringstream text;
	text << "Particles: " << g_numOfParticles << "    ::    "
	<< GetGeoTypeName() << "    ::    "
	<< "Direction: ";
	if(m_world->m_direction)
		text << "Outward";
	else
		text << "Inward";
	m_debugFont.m_myText = text.str();

	m_debugLineShader->m_myVerts	=	m_debugFont.CreateFontVertsPerChar(m_debugFont.m_myText, Vector2(5.0f, m_renderer->GetDisplayHeight() * .04f), Rgba::GREEN, bufferSize);
	m_debugLineShader->CopyToBuffer( m_debugLineShader->m_buffer, m_debugLineShader->m_myVerts, bufferSize );
};