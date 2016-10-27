//================================================================
//                     EngineCommon.cpp
//================================================================
#include "Engine/EngineCommon/EngineCommon.hpp"
#include <string>
bool	g_displayConsole = false;
bool	g_programIsRunning = true;
bool	g_renderWorld = true;
double	g_secondsPerTick; 
float	g_currentSeconds;
bool	g_debugMode = false;
bool	g_drawAxes = true;
bool	g_displayFPS = true;
bool	g_appIsRunning = true;
bool	g_polygonLines = false;
bool	g_use3DCamera = true;
bool	g_displayMousePosition = false;
std::string  g_globalUtilityString;
std::string  g_globalUtilityString2;


const double g_maxFramesPerSecond = 60.0;
const double g_minFramesPerSecond = 5.0;
const double g_mininumSecondsPerFrame = 1.0 / g_maxFramesPerSecond;
const double g_maximumSecondsPerFrame = 1.0 / g_minFramesPerSecond;

const std::string g_masterFont		 = "./data/fontInfo/ariel.txt";
const std::string g_masterFontShader = "./data/fontInfo/font";
const std::string g_masterFontImage	 = "./data/fontInfo/text.png";
