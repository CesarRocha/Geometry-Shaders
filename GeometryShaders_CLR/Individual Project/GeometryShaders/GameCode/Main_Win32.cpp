//================================================================
//                     Main_Win32.cpp
//================================================================
#pragma once 
#include <Windows.h>
#include "TheApp.hpp"
#include "Engine/Input/InputSystem.hpp"
#define DISCARD_PARAMETER(p) (void)p
TheApp* TheApp::s_theApp = NULL;

//################################################################################################//
//################################################################################################//
//################################################################################################//
LRESULT __stdcall GameMessageProcessingFunction(HWND windowHandle, UINT messageID, WPARAM wParam, LPARAM lParam)
{
//	bool wasHandled = false;
// 	switch ( messageID )
// 	{
// 	case WM_KEYDOWN:
// 		wasHandled = TheApp::s_theApp->ProcessKeyDown((int)wParam);
// 		if (wasHandled)
// 		{
// 			return 0;
// 		}
// 	default: 	
// 	}
	return DefWindowProc( windowHandle, messageID, wParam, lParam);
}

//################################################################################################//
//################################################################################################//
//################################################################################################//
HWND CreateAppWindow( HINSTANCE thisAppInstance, int showCommand )
{   
	WNDCLASSEXW windowDescription ;
	memset( &windowDescription, 0, sizeof( WNDCLASSEXW ));

	windowDescription.hbrBackground ;
	windowDescription.cbSize		=	sizeof( WNDCLASSEXW ) ;
	windowDescription.hInstance		=	thisAppInstance ;
	windowDescription.lpszClassName =	TEXT("Geometry Shaders") ;
	windowDescription.lpfnWndProc	=	GameMessageProcessingFunction ;
	windowDescription.style			=	CS_HREDRAW | CS_OWNDC | CS_VREDRAW ;

	ATOM returnValue	=	RegisterClassEx( &windowDescription ) ; 
	DISCARD_PARAMETER (returnValue);

	DWORD	style	= WS_OVERLAPPEDWINDOW ;
	int		x		= CW_USEDEFAULT ;
	int		y		= 0 ;
	int		width	= CW_USEDEFAULT ;
	int		height	= 0;
	

	DISCARD_PARAMETER (style);
	DISCARD_PARAMETER (x		);
	DISCARD_PARAMETER (y		);
	DISCARD_PARAMETER (width    );
	DISCARD_PARAMETER (height   );

	RECT desktopWindowRect;
	HWND desktopWindow = GetDesktopWindow();
	GetClientRect(desktopWindow, &desktopWindowRect);
	RECT windowRect;
	windowRect.left = 190;
	windowRect.right = 1600;
	windowRect.top = 90;
	windowRect.bottom = 900;

	DWORD windowsStyleFlags = WS_OVERLAPPEDWINDOW;
	DWORD windowsStyleFlagsEx = WS_EX_APPWINDOW;

	AdjustWindowRectEx(&windowRect, windowsStyleFlags, false, windowsStyleFlagsEx);

	HWND WindowHandle = CreateWindow( 
		TEXT("Geometry Shaders"), 
		TEXT("Geometry Shaders"), 
		WS_OVERLAPPEDWINDOW, 
		windowRect.left, 
		windowRect.top, 
		windowRect.right, 
		windowRect.bottom, 
		NULL, 
		NULL, 
		thisAppInstance, 
		NULL);

	if (WindowHandle)
	{
		ShowWindow( WindowHandle, showCommand);
		UpdateWindow(WindowHandle);
	}
	return WindowHandle ;
}


//################################################################################################//
//################################################################################################//
//################################################################################################//

int __stdcall WinMain( HINSTANCE thisAppInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DISCARD_PARAMETER(hPrevInstance);
	DISCARD_PARAMETER(lpCmdLine);
	HWND myWindowHandle = CreateAppWindow( thisAppInstance, nShowCmd ) ;

		TheApp::s_theApp = new TheApp();
		TheApp::s_theApp->Startup( myWindowHandle );
		TheApp::s_theApp->Run();
		TheApp::s_theApp->Shutdown();
}

